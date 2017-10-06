#include "libft.h"
#include <stdio.h>
#include <sys/wait.h>
#include "minishell.h"

char	**get_args(char *buf)
{
	char 	**args;
	int 	i;

	i = -1;
	args = ft_strsplit_space(buf);
	// ft_printstab(args);
	return (args);
}

char	**dup_env(char	**env)
{
	int 	i;
	int		size;
	char	**ret;

	size = ft_size_tab(env);
	i = -1;
	ret = (char**)ft_memalloc(sizeof(char*) * (size + 1));
	while(++i < size)
		ret[i] = ft_strdup(env[i]);
	return (ret);
}

int exec_args(t_msh sh)
{
	pid_t pid;
	struct stat buf;

	pid = fork();
	if(!pid)
	{
		if(!stat(sh.args[0], &buf))
		{
			// printf("ok\n");
			execve(sh.args[0], sh.args, sh.env);
			exit(1);
		}
		else
		{
			// printf("else\n");
			exit(0);
			return (0);
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (1);

}

void	launch(t_msh sh)
{
	pid_t 	pid;
	char 	*tmp;
	struct 	stat buf;

	// printf("launch\n");
	pid  = fork();
	if(!pid)
	{
		while(sh.path)
		{
			sh.path->path = ft_strjoinf(sh.path->path, "/", 1);
			tmp = ft_strjoin(sh.path->path, sh.args[0]);
			if(!stat(tmp, &buf))
			{
				execve(tmp, sh.args, sh.env);
				free(tmp);
				exit(1);
			}
			free(tmp);
			sh.path = sh.path->next;
		}
		printf("unknow command\n");
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void print_pmt(char *pmt)
{
	ft_printf(GREEN);
	write(1, "(", 1);
	write(1, pmt, ft_strlen(pmt));
	write(1, ") msh$> ", 8);
	ft_printf(STOP);
}

int main(int ac, char **av ,char **env)
{
 	char 	*buf;
 	t_msh	sh;
 	t_cmd *cmd_lst;

	ac = 1;
	av = NULL;
	buf = NULL;
	sh.pmt = NULL;
	cmd_lst = NULL;
	//env = NULL;
	if(!env[0])
		env = create_env();
	sh.env_lst = get_env(env);
	sh.env = dup_env(env);
	while(get_pmt(&sh))
	{
		//free la liste path avant reinit // 
		sh.path = get_path(sh.env_lst);
		print_pmt(sh.pmt);
		// free(sh.pmt);
		get_next_line(0, &buf);
		if(ft_strlen(buf))
		{
			sh.args = get_args(buf);
			free(buf);
			cmd_lst = add_cmd(cmd_lst, sh.args[0]);
			exec_args(sh);
			// printf("no exec\n");
			if(!is_built(sh.args[0]))
				launch(sh);
			else
				built(&sh);
			free_tab(sh.args);
		}
		else
			free(buf);
	}
	return 0;
}