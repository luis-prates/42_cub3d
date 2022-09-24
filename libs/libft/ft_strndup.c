/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 04:16:24 by lprates           #+#    #+#             */
/*   Updated: 2020/12/26 04:36:20 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, int n)
{
	int		i;
	char	*target;

	i = 0;
	while (src[i] != '\0')
		i++;
	target = malloc((n + 1) * sizeof(char));
	if (!target)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && i < n)
	{
		target[i] = src[i];
		i++;
	}
	target[i] = '\0';
	return (target);
}
