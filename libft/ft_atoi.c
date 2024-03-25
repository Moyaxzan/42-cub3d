/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <tsaint-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 23:08:10 by taospa            #+#    #+#             */
/*   Updated: 2023/05/04 18:58:40 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_num(const char *nptr)
{
	int	i;

	i = 0;
	if (nptr != 0x0)
	{
		while (nptr[i] >= '0' && nptr[i] <= '9')
			i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	unsigned long		i;
	int					sign;
	int					nbr;
	unsigned long int	end_num;

	i = 0;
	sign = 1;
	nbr = 0;
	while (nptr[i] == 32 || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	end_num = i + size_num(&nptr[i]);
	while (i < end_num)
	{
		nbr = nbr * 10;
		nbr += (nptr[i] - '0');
		i++;
	}
	return (nbr * sign);
}
