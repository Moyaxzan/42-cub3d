/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:22:15 by marvin            #+#    #+#             */
/*   Updated: 2023/05/05 13:00:36 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			len_src;
	size_t			len_dst;
	unsigned long	i;

	i = 0;
	if (!dst || !src)
		return (0);
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (size <= len_dst)
		return (size + len_src);
	while (i < len_src && len_dst + i < size - 1)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = 0;
	return (len_dst + len_src);
}
