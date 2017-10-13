/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 15:58:08 by lbenamer          #+#    #+#             */
/*   Updated: 2016/11/20 15:58:10 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	count_arg(const char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != 32 && (s[i] < 9 || s[i] > 13))
		{
			j++;
			while (s[i] != 32 && (s[i] < 9 || s[i] > 13) && s[i])
				i++;
			--i;
		}
		i++;
	}
	return (j);
}

char		**ft_strsplit_space(char *s)
{
	size_t	i;
	size_t	start;
	char	**tab;
	size_t	n;

	n = 0;
	i = 0;
	tab = (char**)ft_memalloc(sizeof(char*) * (count_arg(s) + 1));
	while (s[i])
	{
		if (s[i] != 32 && (s[i] < 9 || s[i] > 13))
		{
			start = i;
			while (s[i] != 32 && (s[i] < 9 || s[i] > 13) && s[i])
				i++;
			if (!(tab[n++] = ft_strsub(s, start, i - start)))
				return (NULL);
			--i;
		}
		i++;
	}
	tab[n] = 0;
	return (tab);
}
