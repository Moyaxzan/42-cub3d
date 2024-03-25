/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:20:41 by taospa            #+#    #+#             */
/*   Updated: 2023/04/09 00:30:34 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current_cell;

	current_cell = lst;
	i = 0;
	while (current_cell)
	{
		current_cell = current_cell->next;
		i++;
	}
	return (i);
}
