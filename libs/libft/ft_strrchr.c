/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 19:11:00 by lprates           #+#    #+#             */
/*   Updated: 2021/02/15 19:43:03 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = 0;
	if (s[i] == 0 && c == 0)
		return ((char *)&s[i]);
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
			tmp = (char *)&s[i];
		i++;
		if (s[i] == 0 && c == 0)
			return ((char *)&s[i]);
	}
	if (tmp != 0)
		return (tmp);
	return (0);
}
