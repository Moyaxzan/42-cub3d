/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:49:26 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/21 17:14:45 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// check if cast is working
int	get_player_pos(t_data *data, char c, int y, int x)
{
	if (data->player->pos.x != data->player->pos.y)
		return (PARSING_ERROR);
	if (c == 'N')
		ch_plr_dir(data->player, (t_vect){0, -1}, (t_vect){0.66, 0.0});
	else if (c == 'S')
		ch_plr_dir(data->player, (t_vect){0, 1}, (t_vect){(double) -0.66, 0.0});
	else if (c == 'E')
		ch_plr_dir(data->player, (t_vect){1, 0}, (t_vect){(double) 0.0, 0.66});
	else if (c == 'W')
		ch_plr_dir(data->player, (t_vect){-1, 0}, (t_vect){0.0, -0.66});
	data->player->pos = (t_vect){(double)x, (double)y};
	return (SUCCESS);
}

// checks if the line contains only 1, 0, whitespaces or player pos. 
// if the player pos is encountered, it is stored within the t_player struct.
// the N/S/W/E char is the orientation; the i (navigates through one line) 
// is the x (abscissa) (position; the y (i from next function, 
// navigates through all lines) would be the position on the ordinate axis.

int	ft_valid_map_line(t_data *data, char **line, int y)
{
	int		i;

	i = 0;
	while ((*line) && (*line)[i])
	{
		if (ft_is_player_pos((*line)[i]))
		{
			if (get_player_pos(data, (*line)[i], y, i))
				return (cherr_code(data, PARSING_ERROR), 0);
			(*line)[i] = '0';
		}
		else if ((*line)[i] != '0' && (*line)[i] != '1' \
		&& !ft_isspace((*line)[i]))
			return (cherr_code(data, PARSING_ERROR), 0);
		i++;
	}
	return (1);
}

int	store_map(t_data *data)
{
	int	length;
	int	valid;

	data->map->height = 0;
	length = 0;
	data->map->map_tab[0] = NULL;
	valid = ft_valid_map_line(data, &data->map->line, data->map->height);
	while (data->map->line && valid && !ft_is_empty_line(data->map->line))
	{
		data->map->map_tab = ft_strjoin_map(data->map->map_tab, \
		data->map->line);
		if (!data->map->map_tab)
			return (strerror(ENOMEM), cherr_code(data, ENOMEM));
		length = ft_strlen(data->map->line);
		if (length > data->map->width)
			data->map->width = length;
		data->map->height++;
		data->map->line = get_next_line(data->map->fd);
		data->map->line_nb++;
		valid = ft_valid_map_line(data, &data->map->line, data->map->height);
		if (!valid)
			return (cherr_code(data, data->err_code));
	}
	return (SUCCESS);
}

int	finish_gnl(t_data *data)
{
	int	error;

	error = 0;
	if (!data->map->line)
		data->map->line = get_next_line(data->map->fd);
	while (data->map->line)
	{
		if (data->map->line && !ft_is_empty_line(data->map->line))
			error = 1;
		free_n_gnl(data);
	}
	free(data->map->line);
	data->map->line = NULL;
	return (error);
}

int	parse_map(t_data *data)
{
	data->map->line = get_next_line(data->map->fd);
	data->map->line_nb++;
	while (data->map->line && ft_is_empty_line(data->map->line))
		free_n_gnl(data);
	if (!ft_is_empty_line(data->map->line) && \
	!ft_valid_map_line(data, &data->map->line, 0))
		return (file_parserr(data));
	if (!data->map->line)
		return (file_parserr(data));
	data->map->map_tab = malloc(sizeof(char *));
	if (!data->map->map_tab)
		return (strerror(ENOMEM), cherr_code(data, ENOMEM));
	if (store_map(data))
		return (file_parserr(data));
	if (data->player->pos.x == -1 || data->player->pos.y == -1)
		return (file_parserr(data));
	if (data->map->line)
	{
		if (finish_gnl(data))
			return (file_parserr(data));
	}
	return (SUCCESS);
}
