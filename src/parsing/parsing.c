/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:27:21 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/01 15:50:39 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_errornl(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
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

void	free_dchartab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
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

int	parsing(int argc, char **argv, t_data *data)
{
	int	line_nb;
	int	ret_val;

	ret_val = arg_parsing(argc, argv, data);
	if (ret_val)
		return (ret_val);
	line_nb = 1;
	ret_val = file_parsing(data, &line_nb);
	return (ret_val);
}
