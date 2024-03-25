/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:28:02 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/25 18:49:50 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->file_path = NULL;
	map->map = NULL;
	map->walls[NORTH] = NULL;
	map->walls[SOUTH] = NULL;
	map->walls[WEST] = NULL;
	map->walls[EAST] = NULL;
	map->ceiling = 0;
	map->floor = 0;
	return (map);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->map = init_map();
	if (!data->map)
		return (free(data), NULL);
	// data->player = malloc(sizeof(t_player));
	// if (!data->player)
	// 	return (free(data->map), free(data), NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	data = init_data();
	if (!data)
		return (-1);
	parsing(data);
	return (0);
}
