/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <tsaint-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:59:24 by marvin            #+#    #+#             */
/*   Updated: 2023/05/05 11:31:44 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destination;
	const unsigned char	*source;

	destination = (unsigned char *)dest;
	source = (const unsigned char *)src;
	if (!dest)
		return (0x0);
	if (!src)
		return (dest);
	while (n--)
		*destination++ = *source++;
	return (dest);
}
