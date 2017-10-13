/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenamer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 22:00:47 by lbenamer          #+#    #+#             */
/*   Updated: 2016/11/21 19:16:31 by lbenamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	ft_strncat(dst, src, ft_strlen_p(dst) - size - 1);
	return (ft_strlen_p(dst) + ft_strlen_p(src));
}
