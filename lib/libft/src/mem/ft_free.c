/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:29:19 by tosilva           #+#    #+#             */
/*   Updated: 2021/11/07 01:48:45 by tosilva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Frees the memory pointed by '*pt' and, if exists, sets it to NULL.
 * @param	pt [void **] pointer to a pointer to the memory to be freed
**/
void	ft_free(void **pt)
{
	if (pt && *pt)
		free(*pt);
	*pt = NULL;
}
