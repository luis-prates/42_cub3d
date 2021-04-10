/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:12:57 by lprates           #+#    #+#             */
/*   Updated: 2021/02/15 21:21:28 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	w_cnt(char *s, char c)
{
	long long	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != c)
		{
			++cnt;
			while (*s && *s != c)
				++s;
		}
		if (*s != 0)
			s++;
	}
	return (cnt);
}

static void	loc_strcpy(char *dst, char *from, char *until)
{
	while (from < until)
		*(dst++) = *(from++);
	*dst = 0;
}

char	**ft_split(char const *s, char c)
{
	char		**ret;
	long long	idx;
	char		*from;

	ret = (char **)malloc(sizeof(char *) * w_cnt((char *)s, c) + 1);
	if (!s || !ret)
		return (NULL);
	idx = 0;
	while (*s)
	{
		if (*s != c)
		{
			from = (char *)s;
			while (*s && *s != c)
				++s;
			ret[idx] = (char *)malloc(s - from + 1);
			loc_strcpy(ret[idx++], from, (char *)s);
		}
		if (*s != 0)
			++s;
	}
	ret[idx] = 0;
	return (ret);
}
