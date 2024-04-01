/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:32:06 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/01 20:34:21 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*replace_line(t_data *data, char *line)
{
	int		i;
	char	*new_line;

	i = 0;
	new_line = NULL;
	new_line = malloc(sizeof(char) * (data->map->map_width + 1));
	if (!new_line)
		return (strerror(ENOMEM), NULL);
	while (line[i] != '\0' && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	free(line);
	while (i < data->map->map_width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i - 1] = '\n';
	new_line[i] = '\0';
	return (new_line);	
}

int	fill_map(t_data *data)
{
	int	i;
	int	size;

	i = 0;
	while (data->map->map_tab[i])
	{
		size = ft_strlen(data->map->map_tab[i]);
		if (size < data->map->map_width)
		{
			data->map->map_tab[i] = replace_line(data, data->map->map_tab[i]);
			if (!data->map->map_tab[i])
				return (strerror(ENOMEM), UNKNOWN_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	space_or_one(char c)
{
	if (ft_isspace(c) || c == '1')
		return (0);
	return (1);
}

int	check_borders(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map->map_width)
	{
		if (space_or_one(data->map->map_tab[0][i]) || space_or_one(data->map->map_tab[data->map->map_height - 1][i]))
			return (PARSING_ERROR);
		i++;
	}
	i = 0;
	while (i < data->map->map_height)
	{
		if (space_or_one(data->map->map_tab[i][0]) || space_or_one(data->map->map_tab[i][data->map->map_width - 2]))
			return (PARSING_ERROR);
		i++;
	}
	return (SUCCESS);
}

int	invalid_block_around(t_data *data, int i, int j)
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	check;

	up = i - 1;
	down = i + 1;
	left = j - 1;
	right = j + 1;
	check = 0;
	if (up >= 0)
		check += space_or_one(data->map->map_tab[up][j]);
	if (down < data->map->map_height)
		check += space_or_one(data->map->map_tab[down][j]);
	if (left >= 0)
		check += space_or_one(data->map->map_tab[i][left]);
	if (right < data->map->map_width)
		check += space_or_one(data->map->map_tab[i][right]);
	return (check);
}

int	map_checks(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (fill_map(data))
		return (PARSING_ERROR);
	if (check_borders(data))
		return (PARSING_ERROR);
	while (data->map->map_tab[i])
	{
		j = 0;
		while (data->map->map_tab[i][j])
		{
			if (ft_isspace(data->map->map_tab[i][j]) && data->map->map_tab[i][j] != '\n')
			{
				if (invalid_block_around(data, i, j))
					return (PARSING_ERROR);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}