/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:46:22 by taospa            #+#    #+#             */
/*   Updated: 2024/04/23 14:56:07 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	dda(t_data *data, t_ray *ray)
{
	int	curr_x;
	int	curr_y;

	curr_x = (int) data->player->pos.x;
	curr_y = (int) data->player->pos.y;
	while (data->map->map_tab[curr_y][curr_x] != '1')
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			curr_x += ray->step.x;
			data->map->side = 0;
		}
		else
		{
			ray->side.y += ray->delta.y;
			curr_y += ray->step.y;
			data->map->side = 1;
		}
	}
	if (!data->map->side)
		return (ray->side.x - ray->delta.x);
	return (ray->side.y - ray->delta.y);
}

int	init_col(int *start_wall, int *end_wall, t_ray *ray)
{
	*start_wall = WIN_HEIGHT / 2 - (int)(WIN_HEIGHT / ray->dist) / 2;
	*end_wall = WIN_HEIGHT / 2 + (int)(WIN_HEIGHT / ray->dist) / 2;
	if (*start_wall < 0)
		*start_wall = 0;
	return (SUCCESS);
}

int	draw_col(t_data *data, t_ray *ray, t_img *texture, int x)
{
	int	start_wall;
	int	end_wall;
	int	wall_color;
	int	y;

	y = 0;
	init_col(&start_wall, &end_wall, ray);
	place_texture(data, ray);
	while (y < WIN_HEIGHT)
	{
		if (y >= start_wall && y <= end_wall)
		{
			data->map->texture.y = (int)data->map->text_pos & (128 - 1);
			data->map->text_pos += data->map->step;
			wall_color = get_texture_color(texture, data->map->texture.x, \
			data->map->texture.y);
			img_pix_put(data->window->image, x, y, wall_color);
		}
		else if (y < WIN_HEIGHT / 2)
			img_pix_put(data->window->image, x, y, data->map->ceiling);
		else
			img_pix_put(data->window->image, x, y, data->map->floor);
		y++;
	}
	return (SUCCESS);
}

int	mlx_render_events(t_data *data)
{
	mlx_clear_window(data->window->mlx_ptr, data->window->win_ptr);
	rotate(data, ROTATION_SPEED * 2, data->player->pressed_keys);
	move(data, data->player->pressed_keys);
	mlx_mouse_move(data->window->mlx_ptr, data->window->win_ptr, \
	WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (SUCCESS);
}

int	ft_render(t_data *data)
{
	int		x;
	t_img	*texture;
	t_ray	ray;

	mlx_render_events(data);
	data->map->side = 0;
	x = 0;
	while (x < WIN_WIDTH)
	{
		ray = init_ray(data, x);
		texture = get_texture(data, &ray);
		if (!texture)
			return (UNKNOWN_ERROR);
		ray.dist = dda(data, &ray);
		draw_col(data, &ray, texture, x++);
	}
	mlx_put_image_to_window(data->window->mlx_ptr, data->window->win_ptr, \
	data->window->image->mlx_img, 0, 0);
	if (data->map->minimap->display)
	{
		minimap(data);
		mlx_put_image_to_window(data->window->mlx_ptr, data->window->win_ptr, \
		data->map->minimap->img->mlx_img, 20, 20);
	}
	return (SUCCESS);
}
