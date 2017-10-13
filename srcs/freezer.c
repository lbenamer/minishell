/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freezer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 11:58:35 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/13 11:58:39 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_elem(t_env *elem)
{
	free(elem->name);
	free(elem->value);
	free(elem);
}

void	del_elem(t_env *elem)
{
	t_env *tmp;

	tmp = elem->next;
	elem->next = elem->next->next;
	free_elem(tmp);
}

void	free_path(t_path *path)
{
	t_path *tmp;

	tmp = NULL;
	if (path)
	{
		tmp = path->next;
		free(path->path);
		free(path);
	}
	while (tmp)
	{
		path = tmp->next;
		free(tmp->path);
		free(tmp);
		tmp = path;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
}
