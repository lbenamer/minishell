/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 12:05:16 by lbenamer          #+#    #+#             */
/*   Updated: 2017/10/13 12:05:18 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pmt(char *pmt)
{
	ft_printf(GREEN);
	write(1, "(", 1);
	write(1, pmt, ft_strlen(pmt));
	write(1, ") msh$> ", 8);
	ft_printf(STOP);
}

int		is_x(size_t n)
{
	if (S_IXOTH & n || S_IXGRP & n || S_IXUSR & n)
		return (1);
	return (0);
}

int		is_path_c(char c)
{
	if (c == '.' || c == '/')
		return (1);
	return (0);
}

int		check_arg(char *arg)
{
	int i;

	i = -1;
	while (arg[++i])
		if (!is_path_c(arg[i]))
			return (1);
	return (0);
}

char	**level_up(char **env, int lvl)
{
	int		i;
	char	**new;
	int		size;

	i = -1;
	size = ft_size_tab(env);
	new = ft_memalloc(sizeof(char*) * (size + 1));
	while (++i < size)
	{
		if (ft_strncmp(env[i], "SHLVL", 5))
			new[i] = ft_strdup(env[i]);
		else
			new[i] = ft_strjoinf("SHLVL=", ft_itoa(lvl), 2);
	}
	return (new);
}
