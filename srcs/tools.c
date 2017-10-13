/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:22:17 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/12 14:22:22 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_no(int n, char *s)
{
	if (n == 1)
		ft_printf("cd: no such file or directory: %s\n", s);
	if (n == 2)
		ft_printf("cd: permission denied: %s\n", s);
	if (n == 3)
		ft_printf("msh: command not found: %s\n", s);
	if (n == 4)
		ft_printf("KEYS : %s : does not exist\n", s);
	if (n == 5)
		ft_printf("setenv: Too many arguments.\n");
	if (n == 6)
		ft_printf("cd: not a directory: %s\n", s);
	if (n == 7)
	{
		ft_printf("setenv: ");
		ft_printf("Variable name must contain alphanumeric characters.\n");
	}
}

int		size_env(t_env *env)
{
	int ret;

	ret = 0;
	while (env && ++ret)
		env = env->next;
	return (ret);
}

char	*find_env(t_env *env, char *name)
{
	while (env)
	{
		if (env->name && !ft_strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int		mod_value(t_env *env, char *name, char *value)
{
	while (env)
	{
		if (env->name && !ft_strcmp(name, env->name))
		{
			free(env->value);
			env->value = value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int		syntax_set(char **args)
{
	int i;

	i = -1;
	if (args && args[1])
	{
		while (args[1][++i])
			if (!ft_isalnum(args[1][i]))
			{
				err_no(7, NULL);
				return (0);
			}
	}
	return (1);
}
