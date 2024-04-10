/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:52:57 by taospa            #+#    #+#             */
/*   Updated: 2024/04/10 14:37:45 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	rotate(t_data *data, int keys)
{
	double	rot;
	double	tmp_dir_x;
	double	tmp_plane_x;

	if (!(keys & A_RIGHT || keys & A_LEFT))
		return (SUCCESS);
	rot = (ROTATION_SPEED * M_PI) / 180;
	if (keys & A_LEFT)
		rot = -rot;
	tmp_dir_x = data->player->dir.x;
	tmp_plane_x = data->player->plane.x;
	data->player->dir.x = data->player->dir.x * cos(rot) - data->player->dir.y * sin(rot);
	data->player->dir.y = tmp_dir_x * sin(rot) + data->player->dir.y * cos(rot);
	data->player->plane.x = data->player->plane.x * cos(rot) - data->player->plane.y * sin(rot);
	data->player->plane.y = tmp_plane_x * sin(rot) + data->player->plane.y * cos(rot);
	return (SUCCESS);
}

int	move(t_data *data, int keys)
{
	(void)keys;
	if (keys & W)
	{
		if (data->map->map_tab[(int)data->player->pos.y][(int)(data->player->pos.x + data->player->dir.x)] != '1')
			data->player->pos.x = data->player->pos.x + data->player->dir.x * 0.3;
		if (data->map->map_tab[(int)(data->player->pos.y + data->player->dir.y)][(int)data->player->pos.x] != '1')
			data->player->pos.y = data->player->pos.y + data->player->dir.y * 0.3;
	}
	return (SUCCESS);
}

int	handle_keypress(int key, t_data *data)
{
	printf("keypress = %d\n", key);
	if (key == K_ESC)
		return (clean_exit(data));
	else if (key == K_A_LEFT)
		data->player->pressed_keys = data->player->pressed_keys | A_LEFT;
	else if (key == K_A_RIGHT)
		data->player->pressed_keys = data->player->pressed_keys | A_RIGHT;
	else if (key == K_W)
		data->player->pressed_keys = data->player->pressed_keys | W;
	ft_render(data);
	return (SUCCESS);
}

int	handle_keyrelease(int key, t_data *data)
{
	printf("keyrelease = %d\n", key);
	if (key == K_ESC)
		return (clean_exit(data));
	else if (key == K_A_LEFT)
		data->player->pressed_keys = data->player->pressed_keys - A_LEFT;
	else if (key == K_A_RIGHT)
		data->player->pressed_keys = data->player->pressed_keys - A_RIGHT;
	else if (key == K_W)
		data->player->pressed_keys = data->player->pressed_keys - W;
	ft_render(data);
	return (SUCCESS);
}

int	mouse_events(int key, int x, int y, t_data *data)
{
	(void)data;
	(void)x;
	(void)y;
	printf("mouse : %d\n", key);
	return (SUCCESS);
}
