/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:28:02 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/17 12:12:45 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

int	clean_exit(t_data *data)
{
	int	ret_val;

	if (!data)
		return (ENOMEM);
	if (data->map)
	{
		ft_free(data->map->file_path);
		ft_free(data->map->file_path);
		ft_free(data->map->walls[0]->path);
		ft_free(data->map->walls[1]->path);
		ft_free(data->map->walls[2]->path);
		ft_free(data->map->walls[3]->path);
		if (data->map->fd > 0)
			close(data->map->fd);
		free_dchartab(data->map->map_tab);
		free_texturesnminimap(data);
		ft_free(data->map);
	}
	ft_free(data->player);
	ret_val = data->err_code;
	exit_mlx(data->window);
	free(data);
	exit(ret_val);
}

void	help(void)
{
	printf("Cub3d program usage:\n");
	printf("  ./cub3D file_path.cub\n\n");
	printf("The file.cub should contain the following mandatory elements:\n");
	printf("  - NO north_texture_path (Example: NO \
./path_to_the_north_texture)\n");
	printf("  - SO south_texture_path\n");
	printf("  - WE west_texture_path\n");
	printf("  - EA east_texture_path\n");
	printf("  - F XXX,XXX,XXX (RGB format, for the Floor)\n");
	printf("  - C XXX,XXX,XXX (RGB format, for the Ceiling)\n");
	printf("  - A map\n\n");
	printf("The map must fulfill the following specifications:\n");
	printf("  - The map must be composed of only 6 possible characters: \n");
	printf("    • 0 for an empty space\n    • 1 for a wall\n");
	printf("    • N, S, E, or W for the player’s start position \
and orientation.\n");
	printf("  - The map must be closed/surrounded by walls.\n");
	printf("  - The map content always has to be the last element \
of the file.\n");
}

int	cherr_code(t_data *data, int err_code)
{
	data->err_code = err_code;
	return (err_code);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = init_data();
	if (!data)
		return (clean_exit(data), ENOMEM);
	if (parsing(argc, argv, data))
		return (clean_exit(data));
	init_mlx(data->window);
	init_minimap(data);
	init_textures(data);
	ft_render(data);
	minimap(data);
	hook_n_loop(data);
	return (clean_exit(data));
}
