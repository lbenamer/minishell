#include "minishell.h"

void	err_no(int n, char *s)
{
	if(n == 1)
		ft_printf("cd: no such file or directory: %s\n", s);
	if(n == 2)
		ft_printf("cd: permission denied: %s\n", s);
}


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
	if(tab)
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

char *find_env(t_env *env, char *name)
{
	while(env)
	{
		if(env->name && !ft_strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int 	mod_value(t_env *env, char *name, char *value)
{
	while(env)
	{
		if(env->name && !ft_strcmp(name, env->name))
		{
			free(env->value);
			env->value = value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}


int syntax_set(char **args)
{
	int i;

	i = -1;
	if(args && args[1])
	{
		while(args[1][++i])
			if(!ft_isalnum(args[1][i]))
			{
				ft_printf("setenv: Variable name must contain alphanumeric characters.\n");
				return (0);
			}
	}
	return (1);
}