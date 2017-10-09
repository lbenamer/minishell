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

char **fork_env(t_msh sh)
{
	int lvl;
	char *tmp;
	char **ret;

	ret = NULL;
	lvl = 0;
	tmp = find_env(sh.env_lst, "SHLVL");
	if(tmp)
		lvl = ft_atoi(tmp);
	ret = level_up(sh.env, ++lvl);
	return (ret);
}

int exec_args(t_msh sh, int *f, char **env_f)
{
	pid_t 	pid;
	struct 	stat buf;

	pid = 1;
	if(!stat(sh.args[0], &buf))
	{
		++*f;
		pid = fork();
	}
	if(!pid)	
	{
		if(!stat(sh.args[0], &buf))
			execve(sh.args[0], sh.args, env_f);
		else
			exit(0);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

void	launch(t_msh sh)
{
	pid_t 	pid;
	char 	*tmp;
	struct 	stat buf;

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
		err_no(3, sh.args[0]);
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
 	char 	**env_f;
 	t_msh	sh;
 	t_cmd *cmd_lst;

	ac = 1;
	av = NULL;
	buf = NULL;
	sh.pmt = NULL;
	cmd_lst = NULL;
	if(!env[0])
		env = create_env();
	sh.env_lst = get_env(env);
	sh.env = dup_env(env);
	while(get_pmt(&sh))
	{
		f = 0;
		sh.path = get_path(sh.env_lst);
		print_pmt(sh.pmt);
		get_next_line(0, &buf);
		if(ft_strlen(buf))
		{	
			env_f = fork_env(sh);
			 printf("fork env ok\n");
			sh.args = get_args(buf);
			free(buf);
			cmd_lst = add_cmd(cmd_lst, sh.args[0]);
			exec_args(sh , &f, env_f);
			if(!f)
			{
				if(!is_built(sh.args[0]))
					launch(sh);
				else
					built(&sh);
			}
			free_tab(sh.args);
			free_tab(env_f);
		}
		else
			free(buf);
	 	free_path(sh.path);
	}
	return (0);
}