/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:47:52 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/12 18:49:29 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->file_path = NULL;
	map->map_tab = NULL;
	map->walls[NORTH] = NULL;
	map->walls[SOUTH] = NULL;
	map->walls[WEST] = NULL;
	map->walls[EAST] = NULL;
	map->ceiling = 0;
	map->floor = 0;
	map->fd = 0;
	map->height = 0;
	map->width = 0;
	map->line = NULL;
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
