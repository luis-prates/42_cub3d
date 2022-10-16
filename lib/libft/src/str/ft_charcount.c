/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:48:58 by tosilva           #+#    #+#             */
/*   Updated: 2022/10/16 11:53:56 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Counts the number of times a character appears in a string.
 * @param	str [const char *] the string to where to find
 * @param	c [char const] the character to be counted
 * @returns	[size_t] the number of times 'c' appears in 'str'
**/
size_t	ft_charcount(const char *str, char const c)
{
	size_t	char_count;
	size_t	idx;

	idx = 0;
	char_count = 0;
	while (str[idx])
	{
		if (str[idx] == c)
			char_count++;
		idx++;
	}
	return (char_count);
}
