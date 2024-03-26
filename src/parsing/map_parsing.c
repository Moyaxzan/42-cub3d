/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:49:26 by jdufour           #+#    #+#             */
/*   Updated: 2024/03/26 19:37:18 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**ft_strjoin_map(char **tab, char *line)
{
	char	**new_tab;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while ((tab[count]))
		count++;
	count++;
	new_tab = malloc(sizeof(char *) * (count + 1));
	if (!new_tab)
		return (NULL);
	while (tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = line;
	i++;
	new_tab[i] = NULL;
	return (new_tab);	
}

int	get_player_pos(t_data *data, char c, int y, int x)
{
	if (data->player->orient)
		return (PARSING_ERROR); //More than one player on the map
	data->player->orient = c;
	data->player->pos_x = x;
	data->player->pos_y = y;
	return (SUCCESS);
}

int	ft_is_player_pos(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

// checks if the line contains only 1, 0, whitespaces or player pos. 
// if the player pos is encountered, it is stored within the t_player struct.
// the N/S/W/E char is the orientation; the i (navigates through one line) is the 
// x (abscissa) (position; the y (i from next function, navigates through all lines)
// would be the position on the ordinate axis.

int	ft_valid_map_line(t_data *data, char **line, int y)
{
	int		i;
	
	i = 0;
	while ((*line) && (*line)[i])
	{
		if (ft_is_player_pos((*line)[i]))
		{
			if (get_player_pos(data, (*line)[i], y, i))
				return (PARSING_ERROR); //more than one player on the map
			(*line)[i] = '0'; //replace the player pos by 0 (if the players on it we know its an empty space)
		}
		else if ((*line)[i] != '0' && (*line)[i] != '1' \
		&& !ft_isspace((*line)[i]))
			return (-1);
		i++;
	}
	return (SUCCESS);
}

int	store_map(t_data *data, char *line)
{
	int	height;
	int	length;
	
	height = 0;
	length = 0;
	while (!ft_valid_map_line(data, &line, height) && !ft_is_empty_line(line))
	{
		if (!data->map->map_tab[0])
			data->map->map_tab[0] = line;
		else
		{
			data->map->map_tab = ft_strjoin_map(data->map->map_tab, line);
			if (!data->map->map_tab)
				return (PARSING_ERROR); // Error failed malloc in the join
		}
		length = ft_strlen(line);
		if (length > data->map->map_width)
			data->map->map_width = length;
		height++;
		line = get_next_line(data->map->fd);
	}
	data->map->map_height = height;
	return (SUCCESS);
}

int	parse_map(t_data *data)
{
	char	*line;
	
	line = get_next_line(data->map->fd);
	while (ft_is_empty_line(line))
		line = get_next_line(data->map->fd);
	data->map->map_tab = malloc(sizeof(char *));
	if (!data->map->map_tab)
		return (PARSING_ERROR); //error malloc on map tab
	data->map->map_tab[0] = NULL;
	store_map(data, line);
	if (data->player->pos_x == -1 || data->player->pos_y == -1 \
	|| !data->player->orient)
		return (PARSING_ERROR); // No player in map
	while (line) //reads until EOF, gets an error if anything else than whitespaces is encountered
	{
		if (!ft_is_empty_line(line))
		{
			// error unknown characters on file + free map
			return (PARSING_ERROR);
		}
		line = get_next_line(data->map->fd);
	}
	return (SUCCESS);
}