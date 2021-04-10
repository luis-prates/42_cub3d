/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:46:55 by lprates           #+#    #+#             */
/*   Updated: 2020/12/26 03:47:44 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*loc_realloc(char *str)
{
	char	*tm;

	tm = malloc(ft_strlen(str) + 1);
	ft_strlcpy(tm, str, ft_strlen(str) + 1);
	free(str);
	return (tm);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(ft_strlen(s1) + 1);
	if (!s1 || !tmp)
		return (NULL);
	while (set[j] != 0)
		if (s1[i] == set[j++] && (++i))
			j = 0;
	j = 0;
	while (s1[i] != 0)
		tmp[j++] = s1[i++];
	j -= 1;
	i = 0;
	while (set[i] != 0)
		if (tmp[j] == set[i++] && --j)
			i = 0;
	tmp[j + 1] = 0;
	return (loc_realloc(tmp));
}
