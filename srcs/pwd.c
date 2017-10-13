/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 11:53:26 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/13 11:53:27 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	maj_pwd(t_msh *sh)
{
	char	*pwd;
	t_env	*tmp;

	pwd = NULL;
	tmp = sh->env_lst;
	if ((pwd = find_env(tmp, "PWD")))
		mod_value(tmp, "PWD", getcwd(NULL, 0));
	if (find_env(tmp, "OLDPWD"))
		mod_value(tmp, "OLDPWD", ft_strdup(pwd));
	maj_env(sh);
}

char	*get_old_pwd(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "OLDPWD"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	check_pwds(t_msh *sh)
{
	char *tmp;

	if (sh->env_lst && !find_env(sh->env_lst, "PWD"))
	{
		tmp = getcwd(NULL, 0);
		add_env(sh->env_lst, "PWD", tmp);
		free(tmp);
		maj_pwd(sh);
	}
	if (sh->env_lst && !find_env(sh->env_lst, "OLDPWD"))
	{
		tmp = getcwd(NULL, 0);
		add_env(sh->env_lst, "OLDPWD", tmp);
		free(tmp);
		maj_pwd(sh);
	}
	if (!sh->env_lst)
	{
		free_tab(sh->env);
		sh->env = create_env();
		sh->env_lst = get_env(sh->env);
	}
}
