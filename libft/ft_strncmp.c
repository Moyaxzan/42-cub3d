/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <tsaint-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:23:46 by taospa            #+#    #+#             */
/*   Updated: 2023/05/04 19:13:05 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s2 && *s1 && *s1 == *s2 && n)
	{
		s2++;
		s1++;
		n--;
	}
	if (!n)
		return (0);
	return (*(unsigned char *) s1 - *(unsigned char *) s2);
}
