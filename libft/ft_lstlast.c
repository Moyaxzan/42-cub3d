/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <tsaint-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 22:24:25 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/04/13 22:34:51 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current_cell;

	current_cell = lst;
	if (!current_cell)
		return (NULL);
	while (current_cell->next)
		current_cell = current_cell->next;
	return (current_cell);
}
