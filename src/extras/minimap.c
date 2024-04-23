/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:50:55 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/23 13:30:22 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_minimap_values(t_data *data)
{
	data->map->minimap->width = data->map->width * 10;
	data->map->minimap->height = data->map->height * 10;
	if (data->map->minimap->width > WIN_WIDTH / 4 || data->map->minimap->height \
	> WIN_HEIGHT / 4)
	{
		while (data->map->minimap->width > WIN_WIDTH / 4 || \
		data->map->minimap->height > WIN_HEIGHT / 4)
		{
			data->map->minimap->width = floor(data->map->minimap->width / 1.1);
			data->map->minimap->height = \
			floor(data->map->minimap->height / 1.1);
		}
	}
	data->map->minimap->pix_factor = (int)(data->map->minimap->width \
	/ (data->map->width));
}

int	init_minimap(t_data *data)
{
	data->map->minimap = malloc(sizeof(t_minimap));
	if (!data->map->minimap)
		return (ENOMEM);
	get_minimap_values(data);
	data->map->minimap->img = malloc(sizeof(t_img));
	if (!data->map->minimap->img)
		return (ENOMEM);
	data->map->minimap->img->mlx_img = mlx_new_image(data->window->mlx_ptr, \
	data->map->minimap->width, data->map->minimap->height);
	if (!data->map->minimap->img->mlx_img)
		return (MLX_ERROR);
	data->map->minimap->img->addr = \
	mlx_get_data_addr(data->map->minimap->img->mlx_img, \
	&data->map->minimap->img->bpp, &data->map->minimap->img->line_len, \
	&data->map->minimap->img->endian);
	if (!data->map->minimap->img->addr)
		return (MLX_ERROR);
	data->map->minimap->display = 1;
	return (SUCCESS);
}

int	draw_tile(t_minimap *minimap, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < minimap->pix_factor)
	{
		j = 0;
		while (j < minimap->pix_factor)
		{
			img_pix_put(minimap->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

void	minimap_loop(t_data *data, int i, int j)
{
	if (data->map->map_tab[i][j] == '1')
		draw_tile(data->map->minimap, \
		j * data->map->minimap->pix_factor, \
		i * data->map->minimap->pix_factor, 0x2F4F4F);
	else if (j == (int)data->player->pos.x && \
	i == (int)data->player->pos.y)
		draw_tile(data->map->minimap, \
		j * data->map->minimap->pix_factor, \
		i * data->map->minimap->pix_factor, 0xFF0000);
	else if (data->map->map_tab[i][j] == '0')
		draw_tile(data->map->minimap, \
		j * data->map->minimap->pix_factor, \
		i * data->map->minimap->pix_factor, data->map->floor);
	else
		draw_tile(data->map->minimap, \
		j * data->map->minimap->pix_factor, \
		i * data->map->minimap->pix_factor, 0x000000);
}

void	minimap_center_loop(t_data *data, int i, int j)
{
	t_vect	map;
	
	map.x = j - (data->map->minimap->center.x - (data->map->minimap->width / (2 * data->map->minimap->pix_factor)));
	map.y = i - (data->map->minimap->center.y - (data->map->minimap->height / (2 * data->map->minimap->pix_factor)));
	if (map.x >= 0 && map.x < data->map->minimap->width / data->map->minimap->pix_factor &&  map.y >= 0 && map.y < data->map->minimap->height / data->map->minimap->pix_factor)
	{
		if (data->map->map_tab[i][j] == '1')
			draw_tile(data->map->minimap, \
			map.x * data->map->minimap->pix_factor, \
			map.y * data->map->minimap->pix_factor, 0x2F4F4F);
		else if (j == (int)data->player->pos.x && \
		i == (int)data->player->pos.y)
			draw_tile(data->map->minimap, \
			map.x * data->map->minimap->pix_factor, \
			map.y * data->map->minimap->pix_factor, 0xFF0000);
		else if (data->map->map_tab[i][j] == '0')
			draw_tile(data->map->minimap, \
			map.x * data->map->minimap->pix_factor, \
			map.y * data->map->minimap->pix_factor, data->map->floor);
		else
			draw_tile(data->map->minimap, \
			map.x * data->map->minimap->pix_factor, \
			map.y * data->map->minimap->pix_factor, 0x000000);
	}
}

int	minimap(t_data *data)
{
	int			i;
	int			j;

	if (!data->map->minimap->display)
		return (0);
	i = 0;
	while (data->map->map_tab[i])
	{
		j = 0;
		while (data->map->map_tab[i][j])
		{
			minimap_loop(data, i, j);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	minimap_center(t_data *data)
{
	int			i;
	int			j;

	if (!data->map->minimap->display)
		return (0);
	ft_memset(data->map->minimap->img->addr, 0, data->map->minimap->height * data->map->minimap->img->line_len);
	data->map->minimap->v_i.x = fmax(data->map->minimap->center.y - (data->map->minimap->height / (2 * data->map->minimap->pix_factor)), 0);
    data->map->minimap->v_i.y = fmin(data->map->minimap->center.y + (data->map->minimap->height / (2 * data->map->minimap->pix_factor)), data->map->height - 1);
    data->map->minimap->v_j.x = fmax(data->map->minimap->center.x - (data->map->minimap->width / (2 * data->map->minimap->pix_factor)), 0);
    data->map->minimap->v_j.y = fmin(data->map->minimap->center.x + (data->map->minimap->width / (2 * data->map->minimap->pix_factor)), data->map->width - 1);	
	data->map->minimap->center.x = (int)data->player->pos.x;
	data->map->minimap->center.y = (int)data->player->pos.y;
	i = data->map->minimap->v_i.x;
	while (i <= data->map->minimap->v_i.y)
	{
		j = data->map->minimap->v_j.x;
		while (j <= data->map->minimap->v_j.y)
		{
			minimap_center_loop(data, i, j);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
