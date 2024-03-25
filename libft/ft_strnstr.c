/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <taospa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:24:47 by taospa            #+#    #+#             */
/*   Updated: 2023/05/04 20:15:17 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned long int	i;
	unsigned long int	little_len;
	int					j;

	i = 0;
	little_len = ft_strlen(little);
	if (!little_len)
		return ((char *)big);
	if (!len)
		return (0);
	while (i <= len - little_len && big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && little[j])
			j++;
		if (!little[j])
			return ((char *)&(big[i]));
		i++;
	}
	return (0x0);
}
