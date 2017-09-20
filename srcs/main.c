#include "libft.h"
#include <stdio.h>
#include <sys/wait.h>
#include "minishell.h"

char	**get_args(char *buf)
{
	char **args;
	int i;

	i = -1;
	args = ft_strsplit_space(buf);
	ft_printstab(args);
	return (args);
}

void	launch(char **args, char **env, t_path *lst)
{
	pid_t 	pid;
	char 	*tmp;
	struct stat buf;

	// if(!ft_strcmp(args[0], "cd"))
	// 	return (0);
	printf("launch\n");
	pid  = fork();
	if(!pid)
	{
		while(lst)
		{
			lst->path = ft_strjoinf(lst->path, "/", 1);
			tmp = ft_strjoin(lst->path, args[0]);
			if(!stat(tmp, &buf))
			{
				execve(tmp, args, env);
				exit(1);
		//		return (1);
			}
			lst = lst->next;
		}
		printf("unknow command\n");
		exit(0);
		// return (0);
	}
	else
		waitpid(pid, NULL, 0);
	// return (1);
}

int main(int ac, char **av ,char **env)
{
	char 	**args;
 	char 	*buf;
 	t_env 	*e_lst;
 	t_path 	*p_lst;

	ac = 1;
	av = NULL;
	buf = NULL;
	e_lst = get_env(env);
	p_lst = get_path(e_lst);
	while(1)
	{
		write(1, "msh$>", 5);
		get_next_line(0, &buf);
		args = get_args(buf);
		if(!is_built(args[0]))
			launch(args, env, p_lst);
		else
			built(args, env);
	}
	return 0;
}