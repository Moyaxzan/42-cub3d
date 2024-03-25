/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:09:16 by tsaint-p          #+#    #+#             */
/*   Updated: 2023/05/05 13:02:05 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned long	i;
	char			*res;

	if (!s)
		return (0x0);
	i = ft_strlen(s) + 1;
	res = malloc(sizeof(char) * i);
	if (!res)
		return (0x0);
	ft_memcpy(res, s, i);
	return (res);
}
