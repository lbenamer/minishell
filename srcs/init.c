/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:21:54 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/12 14:21:55 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_env(t_msh *sh, char **env)
{
	if (!env[0])
		env = create_env();
	sh->env_lst = get_env(env);
	sh->env = dup_env(env);
}

t_path	*init_path(char *path)
{
	t_path *new;

	new = (t_path*)ft_memalloc(sizeof(t_env));
	new->path = ft_strdup(path);
	new->next = NULL;
	return (new);
}

t_env	*init_env(char *env_line)
{
	char	**tmp;
	t_env	*new;

	new = (t_env*)ft_memalloc(sizeof(t_env));
	tmp = ft_strsplit(env_line, '=');
	new->name = ft_strdup(tmp[0]);
	new->value = ft_strdup(tmp[1]);
	new->next = NULL;
	free_tab(tmp);
	return (new);
}

int		path_bin(char *line)
{
	if (!ft_strncmp("./", line, 2) || line[0] == '/')
		return (1);
	return (0);
}

char	*add_slash(char *s1, char *s2)
{
	char *ret;

	s1 = ft_strjoinf(s1, "/", 1);
	ret = ft_strjoin(s1, s2);
	return (ret);
}
