/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:47:52 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/18 01:52:54 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	null_init(t_map *map)
{
	map->file_path = NULL;
	map->map_tab = NULL;
	map->walls[NORTH]->path = NULL;
	map->walls[SOUTH]->path = NULL;
	map->walls[WEST]->path = NULL;
	map->walls[EAST]->path = NULL;
	map->ceiling = 0;
	map->floor = 0;
	map->fd = 0;
	map->height = 0;
	map->width = 0;
	map->line = NULL;
	map->line_nb = 0;
	map->minimap = NULL;
	return (SUCCESS);
}

t_map	*init_map(void)
{
	t_map	*map;
	int		i;

	i = 0;
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	while (i < 4)
	{
		map->walls[i] = malloc(sizeof(t_img));
		if (!map->walls[i])
			return (NULL);
		map->walls[i]->mlx_img = NULL;
		i++;
	}
	null_init(map);
	return (map);
}

t_player	*init_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pressed_keys = 0;
	player->pos = (t_vect){-1, -1};
	player->dir = (t_vect){-1, -1};
	player->plane = (t_vect){-1, -1};
	return (player);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->err_code = 0;
	data->map = init_map();
	if (!data->map)
		return (free(data), NULL);
	data->player = init_player();
	if (!data->player)
		return (free(data->map), free(data), NULL);
	data->window = malloc(sizeof(t_window));
	if (!data->window)
		return (NULL);
	data->window->mlx_ptr = 0x0;
	data->window->win_ptr = 0x0;
	return (data);
}
