/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 01:57:55 by lprates           #+#    #+#             */
/*   Updated: 2020/12/26 02:10:24 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!s || !tmp)
		return (NULL);
	while (s[++i] != 0)
		tmp[i] = f(i, s[i]);
	tmp[i] = 0;
	return (tmp);
}
