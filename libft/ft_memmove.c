/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 00:20:36 by marvin            #+#    #+#             */
/*   Updated: 2023/05/04 18:11:36 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned long	i;

	if (!dest)
		return (0x0);
	i = n;
	if (src > dest)
		ft_memcpy(dest, src, n);
	else
		while (--i + 1)
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
	return (dest);
}
