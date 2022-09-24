/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:07:16 by lprates           #+#    #+#             */
/*   Updated: 2020/12/08 15:39:29 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*memory;
	unsigned char	value;

	i = 0;
	memory = s;
	value = c;
	while (i < n)
	{
		memory[i] = value;
		i++;
	}
	return (memory);
}
