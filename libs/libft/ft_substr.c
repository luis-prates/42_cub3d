/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:48:01 by lprates           #+#    #+#             */
/*   Updated: 2021/02/15 20:32:08 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*loc_malloc(char *s, size_t start, size_t len)
{
	char	*sub;

	if ((size_t)ft_strlen(s) < start)
	{
		sub = malloc(sizeof(char) * 1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	else if (len > (size_t)ft_strlen(s))
	{
		sub = malloc(sizeof(char) * (size_t)ft_strlen(s) + 1);
		if (!sub)
			return (NULL);
	}
	else
	{
		sub = malloc(sizeof(char) * len + 1);
		if (!sub)
			return (NULL);
	}
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	sub = loc_malloc((char *)s, start, len);
	if (!sub)
		return (NULL);
	if (len > ft_strlen(s) && start == 0)
	{
		ft_strlcpy(sub, (char *)s, len);
		return (sub);
	}
	while ((size_t)i < len && start < ft_strlen(s) + 1)
	{
		sub[i] = s[start++];
		if ((sub[i++]) == '\0')
			return (sub);
	}
	sub[i] = 0;
	return (sub);
}
