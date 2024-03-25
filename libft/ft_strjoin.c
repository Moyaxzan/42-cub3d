/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <taospa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 19:36:06 by taospa            #+#    #+#             */
/*   Updated: 2023/05/03 15:56:20 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0x0);
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0x0);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}
