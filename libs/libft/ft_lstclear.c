/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:23:34 by lprates           #+#    #+#             */
/*   Updated: 2021/01/14 08:37:03 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*first;

	while (*lst)
	{
		del((*lst)->content);
		first = *lst;
		*lst = first->next;
		free(first);
	}
	*lst = NULL;
	return ;
}
