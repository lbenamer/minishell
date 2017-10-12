/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:21:48 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/12 14:21:50 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *new_cmd(char *line)
{
	t_cmd *new;
	new = (t_cmd*)ft_memalloc(sizeof(t_cmd));
	if (line)
		new->line = ft_strdup(line);
	new->next = NULL;
	return (new);
}

t_cmd	*add_cmd(t_cmd *lst, char *line)
{
	t_cmd *tmp;

	if (!lst)
		lst = new_cmd(line);
	else
	{
		tmp = lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd(line);
	} 
	return (lst);		
}
