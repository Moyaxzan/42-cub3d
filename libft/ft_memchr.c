/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <tsaint-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:31:40 by taospa            #+#    #+#             */
/*   Updated: 2023/05/04 19:51:05 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char				*mem_block;

	mem_block = (unsigned char *) s;
	while (n--)
	{
		if (*mem_block == (unsigned char)c)
			return (mem_block);
		mem_block++;
	}
	return (0x0);
}
