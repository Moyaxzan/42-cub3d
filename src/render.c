/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:46:22 by taospa            #+#    #+#             */
/*   Updated: 2024/04/09 17:11:35 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ch_plr_dir(t_player *plr, t_vect dir, t_vect plane)
{
	plr->dir = dir;
	plr->plane = plane;
	return (0);
}

void	get_sidendist(t_player *plr, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side.x = (plr->pos.x - (int) plr->pos.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side.x = ((int) plr->pos.x + 1.0 - plr->pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side.y = (plr->pos.y - (int) plr->pos.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side.y = ((int) plr->pos.y + 1.0 - plr->pos.y) * ray->delta.y;
	}
}

void	get_delta(t_ray *ray)
{
	if (!ray->dir.x)
		ray->delta.x = INT_MAX;
	else
		ray->delta.x = fabs(1 / ray->dir.x);
	if (!ray->dir.y)
		ray->delta.y = INT_MAX;
	else
		ray->delta.y = fabs(1 / ray->dir.y);
}

t_ray	init_ray(t_data *data, int x)
{
	t_ray	ray;
	double	cam_x;

	cam_x = 2 * x / ((double) WIN_WIDTH) - 1;
	ray.dir.x = data->player->dir.x + data->player->plane.x * cam_x;
	ray.dir.y = data->player->dir.y + data->player->plane.y * cam_x;
	get_delta(&ray);
	get_sidendist(data->player, &ray);
	return (ray);
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
