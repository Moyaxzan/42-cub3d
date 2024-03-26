/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:28:02 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/26 17:28:51 by tsaint-p         ###   ########.fr       */
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
	map->fd = 0;
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

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	clean_exit(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
	{
		ft_free(data->map->file_path);
		ft_free(data->map->file_path); //never changed before
		ft_free(data->map->walls[0]);
		ft_free(data->map->walls[1]);
		ft_free(data->map->walls[2]);
		ft_free(data->map->walls[3]);
		if (data->map->fd > 0)
			close(data->map->fd);
		ft_free(data->map);
	}
	free(data);
}

void	print_map(t_map *map)
{
	printf("map : %p\n", map);
	printf("map->file_path = %s\n", map->file_path);
	printf("map->fd = %d\n", map->fd);
	printf("map->walls[0] = %s\n", map->walls[0]);
	printf("map->walls[1] = %s\n", map->walls[1]);
	printf("map->walls[2] = %s\n", map->walls[2]);
	printf("map->walls[3] = %s\n", map->walls[3]);
	printf("map->ceiling = %x\n", map->ceiling);
	printf("map->floor = %x\n", map->floor);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	data = init_data();
	if (!data)
		return (-1);
	parsing(argc, argv, data);
	// print_map(data->map);
	clean_exit(data);
	return (0);
}
