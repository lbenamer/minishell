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

int exec_args(t_msh sh, int *f, int *shlvl)
{
	pid_t pid;
	struct stat buf;

	++*shlvl;
	printf("f = %d\n", *f);
	if(!stat(sh.args[0], &buf))
		++*f;
	printf("f = %d\n", *f);
	pid = fork();
	printf("pid = %d\n", pid);
	level_up(sh.env_lst);
	
	if(!pid)
	{
		printf("pid ok\n");
		ft_printstab(sh.env);
		if(!stat(sh.args[0], &buf))
		{
			printf("stat ok\n");
			++*f;
			execve(sh.args[0], sh.args, sh.env);
			// printf("shlvl fils = %d\n", *shlvl);
			// --*shlvl;
			// exit(1);
		}
		else
		{

		 	printf("stat K.O.\n");
			exit(0);
			--*shlvl;
			return (0);
		}
	}
	else
	{
		printf("waitpid\n");
		waitpid(pid, NULL, 0);
		// --*shlvl;
		// --shlvl;
	}
	// printf("shlvl = %d\n", *shlvl);
	return (0);

}

void	launch(t_msh sh)
{
	pid_t 	pid;
	char 	*tmp;
	struct 	stat buf;

	// printf("launch\n");
	pid  = fork();
	// printf("pid = %d", pid);
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
 	int 	f;
 	int  	shlvl = 1;
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

		f = 0;
		sh.path = get_path(sh.env_lst);
		// printf("getpath ok\n");
		print_pmt(sh.pmt);
		get_next_line(0, &buf);
		if(ft_strlen(buf))
		{
			sh.args = get_args(buf);
			free(buf);
			cmd_lst = add_cmd(cmd_lst, sh.args[0]);
			exec_args(sh , &f, &shlvl);
			// printf("t = %d\n", t);
			if(!f)
			{
				// printf("f = %d\n", f);
				if(!is_built(sh.args[0]))
					launch(sh);
				else
					built(&sh);
			}
			free_tab(sh.args);
		}
		else
			free(buf);
	 	free_path(sh.path);
	 	printf("shlvl = %d\n", shlvl);
	 	printf("one turn finish\n");
	}
	return 0;
}