/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:14:04 by lprates           #+#    #+#             */
/*   Updated: 2021/01/13 20:54:55 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int			i;
	size_t		d;
	size_t		s;

	i = 0;
	d = ft_strlen(dst);
	s = ft_strlen(src);
	if (size == 0)
		return (s);
	if (size < d)
		return (s + size);
	while (src[i] && d + 1 + i < size)
	{
		dst[d + i] = src[i];
		i++;
	}
	dst[d + i] = '\0';
	return (d + s);
}
