/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:30:18 by taospa            #+#    #+#             */
/*   Updated: 2024/04/15 23:23:12 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
