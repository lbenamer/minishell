#include "minishell.h"

char  **level_up(char **env, int lvl)
{
	int i;
	char **new;
	int size;

	i = -1;
	size = ft_size_tab(env);
	new =  ft_memalloc(sizeof(char*) * (size + 1));
	while(++i < size)
	{
		if(ft_strncmp(env[i], "SHLVL", 5))
			new[i] = ft_strdup(env[i]);
		else
			new[i] = ft_strjoinf("SHLVL=", ft_itoa(lvl), 2);
	}
	return (new);
}

void	err_no(int n, char *s)
{
	if(n == 1)
		ft_printf("cd: no such file or directory: %s\n", s);
	if(n == 2)
		ft_printf("cd: permission denied: %s\n", s);
	if(n == 3)
		ft_printf("msh: command not found: %s\n", s);
	if(n == 4)
		ft_printf("KEYS : %s : does not exist\n", s);
	if(n == 5)
		ft_printf("setenv: Too many arguments.\n");
}

void disp_path(t_path *path)
{
	int i = 1;
	while(path)
	{
		printf("path = %s n = %d\n", path->path, i);
		path = path->next;
		++i;
	}
}


void free_path(t_path *path)
{
	t_path *tmp;

	tmp = NULL;
	if(path)
	{
		tmp = path->next;
		free(path->path);
		free(path);
	}
	while(tmp)
	{
		path = tmp->next;
		free(tmp->path);
		free(tmp);
		tmp = path;
	}
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