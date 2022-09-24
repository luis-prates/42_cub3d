/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 16:24:38 by lprates           #+#    #+#             */
/*   Updated: 2020/12/13 21:58:37 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int		i;
	const unsigned char	*smemory;
	unsigned char		*dmemory;
	unsigned char		stop;
	unsigned char		*tmp;

	i = 0;
	stop = c;
	smemory = src;
	dmemory = dest;
	while (i < n)
	{
		dmemory[i] = smemory[i];
		if (smemory[i] == stop)
		{
			tmp = &dmemory[i + 1];
			return (tmp);
		}
		i++;
	}
	return (NULL);
}
