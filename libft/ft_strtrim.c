/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <taospa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:34:49 by taospa            #+#    #+#             */
/*   Updated: 2023/08/07 12:26:05 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_trim(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

static char	*fill_trim(char const *s1, size_t len_res, int beg_cpy)
{
	unsigned long	i;
	char			*res;

	res = malloc(sizeof(char) * (len_res + 1));
	if (!res)
		return (0x0);
	i = 0;
	while (s1[beg_cpy + i] && i < len_res)
	{
		res[i] = s1[beg_cpy + i];
		++i;
	}
	res[i] = 0;
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_res;
	size_t	len_s1;
	int		i;

	if (!s1 || !set)
		return (0x0);
	i = 0;
	len_s1 = ft_strlen(s1);
	while (len_s1 - i - 1 && to_trim(s1[len_s1 - i - 1], set))
		++i;
	if ((unsigned long)i >= len_s1 - 1)
		return (fill_trim(s1, 0, 0));
	len_res = len_s1 - i;
	i = 0;
	while (s1[i] && to_trim(s1[i], set))
		++i;
	len_res = len_res - i;
	return (fill_trim(s1, len_res, i));
}
