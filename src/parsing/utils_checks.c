/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:42:55 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/02 12:45:36 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//I left this one with a return (0) in case of TRUE, because i'm calling 
//it to increment an int that needs to remain equal to 0 to be considered 
//valid. Otherwise, as a map can be valid even if the function cannot 
//enter in some conditions, i couldnt properly check if my designated int 
//has a correct value.

int	space_or_one(char c)
{
	if (ft_isspace(c) || c == '1')
		return (0);
	return (1);
}

int	ft_is_player_pos(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	ft_isnum(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' \
		|| c == '\v' || c == '\f');
}

int	ft_is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (!ft_isspace(line[i++]))
			return (0);
	}
	return (1);
}
