/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:42:24 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/05/04 18:06:32 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_res;
	t_list	*new_node;

	lst_res = 0x0;
	if (!f || !del)
		return (0x0);
	while (lst)
	{
		new_node = ft_lstnew((*f)(lst->content));
		if (!new_node)
		{
			ft_lstclear(&lst_res, del);
			return (0x0);
		}
		ft_lstadd_back(&lst_res, new_node);
		lst = lst->next;
	}
	return (lst_res);
}
