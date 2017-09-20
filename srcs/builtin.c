#include "minishell.h"

int 	is_built(char *cmd)
{
	char *built[6] = {"cd", "setenv", "unsetenv", "exit", "echo", "env"};
	int 	i;

	i = -1;
	while(++i < 6)
		if(!ft_strcmp(cmd, built[i]))
			return (1);
	return (0);
}

void	built(char **args, char **env)
{
	printf("built\n");
	env = NULL;
	if(!ft_strcmp(args[0], "cd"))
	{
		chdir(args[1]);
	}
	else if(!ft_strcmp(args[0], "exit"))
		exit(1);

}