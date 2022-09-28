/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 00:35:29 by lprates           #+#    #+#             */
/*   Updated: 2020/12/21 13:52:49 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c < -1)
		return ((unsigned char)c);
	if (c >= 48 && c <= 57)
		return (c);
	return (0);
}
