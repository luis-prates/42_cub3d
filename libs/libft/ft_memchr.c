/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 10:11:06 by lprates           #+#    #+#             */
/*   Updated: 2020/12/21 13:53:10 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*smemory;
	unsigned char		stop;
	unsigned char		bytes;
	unsigned char		i;

	smemory = s;
	stop = c;
	bytes = n;
	i = 0;
	while (i < bytes)
	{
		if (*smemory == stop)
			return ((unsigned char *)smemory);
		smemory++;
		if (*smemory == 0 && stop != 0)
			break ;
		i++;
	}
	return (NULL);
}
