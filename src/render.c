/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:46:22 by taospa            #+#    #+#             */
/*   Updated: 2024/04/12 18:30:56 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ch_plr_dir(t_player *plr, t_vect dir, t_vect plane)
{
	plr->dir = dir;
	plr->plane = plane;
	return (0);
}

double	dda(t_data *data, t_ray ray, int *side)
{
	int	curr_x;
	int	curr_y;

	curr_x = (int) data->player->pos.x;
	curr_y = (int) data->player->pos.y;
	while (data->map->map_tab[curr_y][curr_x] != '1')
	{
		if (ray.side.x < ray.side.y)
		{
			ray.side.x += ray.delta.x;
			curr_x += ray.step.x;
			*side = 0;
		}
		else
		{
			ray.side.y += ray.delta.y;
			curr_y += ray.step.y;
			*side = 1;
		}
	}
	if (!*side)
		return (ray.side.x - ray.delta.x);
	return (ray.side.y - ray.delta.y);
}

int	draw_col(t_data *data, double dist, int side, int x)
{
	int	start_wall;
	int	end_wall;
	int	wall_color;
	int	y;

	y = 0;
	wall_color = 0xffffff;
	start_wall = WIN_HEIGHT / 2 - (int)(WIN_HEIGHT / dist) / 2;
	end_wall = WIN_HEIGHT / 2 + (int)(WIN_HEIGHT / dist) / 2;
	if (start_wall < 0)
		start_wall = 0;
	if (side)
		wall_color = wall_color - 0x444444;
	while (y < WIN_HEIGHT)
	{
		if (y >= start_wall && y <= end_wall)
			img_pix_put(data->window->image, x, y, wall_color);
		else if (y < WIN_HEIGHT / 2)
			img_pix_put(data->window->image, x, y, data->map->ceiling);
		else
			img_pix_put(data->window->image, x, y, data->map->floor);
		y++;
	}
	return (SUCCESS);
}

int	ft_render(t_data *data)
{
	int		x;
	int		side;
	t_ray	ray;

	mlx_clear_window(data->window->mlx_ptr, data->window->win_ptr);
	rotate(data, data->player->pressed_keys);
	move(data, data->player->pressed_keys);
	side = 0;
	x = 0;
	while (x < WIN_WIDTH)
	{
		ray = init_ray(data, x);
		draw_col(data, dda(data, ray, &side), side, x);
		x++;
	}
	mlx_put_image_to_window(data->window->mlx_ptr, data->window->win_ptr, \
	data->window->image->mlx_img, 0, 0);
	return (SUCCESS);
}
