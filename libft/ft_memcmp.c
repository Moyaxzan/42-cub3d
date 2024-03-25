/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <tsaint-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:51:27 by taospa            #+#    #+#             */
/*   Updated: 2023/05/04 19:53:57 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char				*p1;
	unsigned char				*p2;

	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	if (!n)
		return (0);
	while (--n && *p1 == *p2)
	{
		p1++;
		p2++;
	}
	return (*p1 - *p2);
}
