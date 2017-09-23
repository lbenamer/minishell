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
void	launch(t_msh sh)
{
	pid_t 	pid;
	char 	*tmp;
	struct 	stat buf;

	printf("launch\n");
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

int main(int ac, char **av ,char **env)
{
	// char 	**args;
 	char 	*buf;
 	// t_env 	*e_lst;
 	// t_path 	*p_lst;
 	t_msh	sh;

	ac = 1;
	av = NULL;
	buf = NULL;
	sh.env_lst = get_env(env);
	sh.path = get_path(sh.env_lst);
	sh.env = dup_env(env);
	while(1)
	{
		get_pmt(&sh);
		ft_printf(GREEN);
		// write(1, "msh$>", 6);
		ft_printf("(%s) msh$> ", sh.pmt);
		ft_printf(STOP);
		free(sh.pmt);
		get_next_line(0, &buf);
		sh.args = get_args(buf);
		free(buf);
		if(!is_built(sh.args[0]))
			launch(sh);
		else
			built(&sh);
		free_tab(sh.args);
	}
	return 0;
}