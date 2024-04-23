/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <tsaint-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:31:27 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/23 12:19:41 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_textures(t_data *data)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		data->map->walls[i]->mlx_img = \
		mlx_xpm_file_to_image(data->window->mlx_ptr, \
		data->map->walls[i]->path, &data->map->walls[i]->width, \
		&data->map->walls[i]->height);
		if (!data->map->walls[i]->mlx_img)
			return (cherr_code(data, UNKNOWN_ERROR));
		i++;
	}
	return (SUCCESS);
}

int	get_texture_color(t_img *texture, int x, int y)
{
	texture->addr = mlx_get_data_addr(texture->mlx_img, &(texture->bpp), \
	&(texture->line_len), &(texture->endian));
	return (*(int *)(texture->addr + (y * texture->line_len + x * \
	(texture->bpp / 8))));
}

t_img	*get_texture(t_data *data, t_ray *ray)
{
	t_img	*texture;

	if (ray->dir.y < 0 && data->map->side)
		return (texture = data->map->walls[SOUTH]);
	else if (ray->dir.y > 0 && data->map->side)
		return (texture = data->map->walls[NORTH]);
	else if (ray->dir.x < 0 && !data->map->side)
		return (texture = data->map->walls[WEST]);
	else if (ray->dir.x > 0 && !data->map->side)
		return (texture = data->map->walls[EAST]);
	return (NULL);
}

int	place_texture(t_data *data, t_ray *ray)
{
	int	line_height;
	int	start;

	line_height = WIN_HEIGHT / ray->dist;
	start = -line_height / 2 + WIN_HEIGHT / 2;
	if (start < 0)
		start = 0;
	if (!data->map->side)
		data->map->wall_x = data->player->pos.y + ray->dist * ray->dir.y;
	else
		data->map->wall_x = data->player->pos.x + ray->dist * ray->dir.x;
	data->map->wall_x -= floor(data->map->wall_x);
	data->map->texture.x = data->map->wall_x * 128;
	if (!data->map->side && ray->dir.x > 0)
		data->map->texture.x = 128 - data->map->texture.x - 1;
	if (data->map->side && ray->dir.y < 0)
		data->map->texture.x = 128 - data->map->texture.x - 1;
	data->map->step = 1.0 * 128 / line_height;
	data->map->text_pos = (start - WIN_HEIGHT / 2 + line_height / 2) * \
	data->map->step;
	return (SUCCESS);
}
