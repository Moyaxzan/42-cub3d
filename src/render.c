/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:46:22 by taospa            #+#    #+#             */
/*   Updated: 2024/04/15 23:01:59 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ch_plr_dir(t_player *plr, t_vect dir, t_vect plane)
{
	plr->dir = dir;
	plr->plane = plane;
	return (0);
}

double	dda(t_data *data, t_ray *ray, int *side)
{
	ray->curr_x = (int) data->player->pos.x;
	ray->curr_y = (int) data->player->pos.y;
	while (data->map->map_tab[ray->curr_y][ray->curr_x] != '1')
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			ray->curr_x += ray->step.x;
			*side = 0;
		}
		else
		{
			ray->side.y += ray->delta.y;
			ray->curr_y += ray->step.y;
			*side = 1;
		}
	}
	if (!*side)
		return (ray->side.x - ray->delta.x);
	return (ray->side.y - ray->delta.y);
}

int	get_texture_color(t_img *texture, int x, int y)
{
	texture->addr = mlx_get_data_addr(texture->mlx_img, &(texture->bpp), &(texture->line_len), &(texture->endian));
	return (*(int *)(texture->addr + (y * texture->line_len + x * (texture->bpp / 8))));
}

int	draw_col(t_data *data, double dist, t_ray *ray, t_img *texture, int x)
{
	int	start_wall;
	int	end_wall;
	int	wall_color;
	int	y;
	int	res_y;

	y = 0;
	data->map->texture_x = 0;
	data->map->texture_y = 0;
	res_y = 0;
	start_wall = WIN_HEIGHT / 2 - (int)(WIN_HEIGHT / dist) / 2;
	end_wall = WIN_HEIGHT / 2 + (int)(WIN_HEIGHT / dist) / 2;
	if (start_wall < 0)
		start_wall = 0;
	while (y < WIN_HEIGHT)
	{
		if (y >= start_wall && y <= end_wall)
		{
			data->map->texture_x = (int)floor((ray->side.x - (int)ray->side.x) * 128);
			res_y = (int)floor(data->map->texture_y * (dist / 8));
			wall_color = get_texture_color(texture, data->map->texture_x, res_y);
			img_pix_put(data->window->image, x, y, wall_color);
			data->map->texture_y++;
		}
		else if (y < WIN_HEIGHT / 2)
			img_pix_put(data->window->image, x, y, data->map->ceiling);
		else
			img_pix_put(data->window->image, x, y, data->map->floor);
		y++;
	}
	return (SUCCESS);
}

t_img	*get_texture(t_data *data, t_ray *ray, int *side)
{
	t_img	*texture;
	
	if (ray->dir.y < 0 && *side)
		return (texture = data->map->walls[SOUTH]);
	else if (ray->dir.y > 0 && *side)
		return (texture = data->map->walls[NORTH]);
	else if (ray->dir.x < 0 && !*side)
		return (texture = data->map->walls[WEST]);
	else if (ray->dir.x > 0 && !*side)
		return (texture = data->map->walls[EAST]);
	return (NULL);
}

int	ft_render(t_data *data)
{
	int		x;
	int		side;
	t_img	*texture;
	t_ray	ray;

	mlx_clear_window(data->window->mlx_ptr, data->window->win_ptr);
	rotate(data, ROTATION_SPEED, data->player->pressed_keys);
	move(data, data->player->pressed_keys);
	side = 0;
	x = 0;
	while (x < WIN_WIDTH)
	{
		ray = init_ray(data, x);
		texture = get_texture(data, &ray, &side);
		draw_col(data, dda(data, &ray, &side), &ray, texture, x);
		x++;
	}
	mlx_put_image_to_window(data->window->mlx_ptr, data->window->win_ptr, \
	data->window->image->mlx_img, 0, 0);
	return (SUCCESS);
}
