/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:04:52 by lprates           #+#    #+#             */
/*   Updated: 2020/12/19 13:50:29 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	const char		*s;
	unsigned int	n;

	s = src;
	n = size;
	if (!src)
		return (0);
	if (n != 0)
	{
		while (--n != 0)
		{
			*dest = *s++;
			if (*dest++ == '\0')
				break ;
		}
	}
	if (n == 0)
	{
		if (size != 0)
			*dest = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}
