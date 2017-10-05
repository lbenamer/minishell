#include "minishell.h"

void	disp_env(t_env *lst)
{
	while(lst)
	{
		printf("name = %s | value = %s\n", lst->name, lst->value);
		lst = lst->next;
	}
}

void	free_tab(char **tab)
{
	int 	i;

	i = -1;
	while(tab[++i])
		free(tab[i]);
	free(tab);
}

int	size_env(t_env *env)
{
	int ret;

	ret = 0;
	while(env && ++ret)
		env = env->next;
	return (ret);
}

int syntax_set(char **args)
{
	if(args && args[1])
		if(ft_strchr(args[1], '='))
		{
			ft_printf("setenv: Variable name must contain alphanumeric characters.\n");
			return (0);
		}
	return (1);
}