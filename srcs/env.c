/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:21:35 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/12 14:21:37 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_env(void)
{
	char	*tmp;
	char	**ret;

	ret = (char**)ft_memalloc(sizeof(char*) * 3);
	tmp = getcwd(NULL, 0);
	ret[0] = ft_strjoin("PWD=", tmp);
	ret[1] = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	return (ret);
}

void	unset_env(t_msh *sh)
{
	t_env *tmp;
	t_env *env;

	env = sh->env_lst;
	if (!sh->args[1])
		return ;
	if (env && !ft_strcmp(env->name, sh->args[1]))
	{
		tmp = env->next;
		free_elem(env);
		sh->env_lst = tmp;
		return (maj_env(sh));
	}
	while (env && env->next)
	{
		if (!ft_strcmp(env->next->name, sh->args[1]))
		{
			del_elem(env);
			return (maj_env(sh));
		}
		env = env->next;
	}
	err_no(4, sh->args[1]);
}

void	add_env(t_env *env, char *name, char *value)
{
	t_env *new;

	new = (t_env*)ft_memalloc(sizeof(t_env));
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strnew(0);
	while (env && env->next)
		env = env->next;
	env->next = new;
}

t_env	*new_env(char *name, char *value)
{
	t_env *new;

	new = (t_env*)ft_memalloc(sizeof(t_env));
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = ft_strnew(0);
	new->next = NULL;
	return (new);
}

void	set_env(t_msh *sh)
{
	t_env *tmp;

	if (ft_size_tab(sh->args) > 3)
		return (err_no(5, "setenv"));
	if (!syntax_set(sh->args))
		return ;
	tmp = sh->env_lst;
	if (!sh->args[1])
		return (ft_printstab(sh->env));
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, sh->args[1]))
		{
			free(tmp->value);
			if (sh->args[2])
				tmp->value = ft_strdup(sh->args[2]);
			else
				tmp->value = ft_strnew(0);
			return (maj_env(sh));
		}
		tmp = tmp->next;
	}
	!sh->env_lst ? sh->env_lst = new_env(sh->args[1], sh->args[2]) :
	add_env(sh->env_lst, sh->args[1], sh->args[2]);
	maj_env(sh);
}
