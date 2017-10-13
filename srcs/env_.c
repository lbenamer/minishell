/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 11:57:47 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/13 11:57:48 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fork_env(t_msh sh)
{
	int		lvl;
	char	*tmp;
	char	**ret;

	ret = NULL;
	lvl = 0;
	tmp = find_env(sh.env_lst, "SHLVL");
	if (tmp)
		lvl = ft_atoi(tmp);
	ret = level_up(sh.env, ++lvl);
	return (ret);
}

char	**dup_env(char **env)
{
	int		i;
	int		size;
	char	**ret;

	size = ft_size_tab(env);
	i = -1;
	ret = (char**)ft_memalloc(sizeof(char*) * (size + 1));
	while (++i < size)
		ret[i] = ft_strdup(env[i]);
	return (ret);
}
