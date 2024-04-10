/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:52:57 by taospa            #+#    #+#             */
/*   Updated: 2024/04/10 15:31:42 by taospa           ###   ########.fr       */
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
	double	s;

	s = SPEED;
	if ((keys & (S | W)) && (keys & (A | D)))
		s = s * 0.1;
	if (keys & W && !(keys & S))
	{
		if (data->map->map_tab[(int)data->player->pos.y][(int)(data->player->pos.x + data->player->dir.x * s)] != '1')
			data->player->pos.x = data->player->pos.x + data->player->dir.x * s;

		if (data->map->map_tab[(int)(data->player->pos.y + data->player->dir.y * s)][(int)data->player->pos.x] != '1')
			data->player->pos.y = data->player->pos.y + data->player->dir.y * s;
	}
	else if (keys & S && !(keys & W))
	{
		if (data->map->map_tab[(int)data->player->pos.y][(int)(data->player->pos.x - data->player->dir.x * s)] != '1')
			data->player->pos.x = data->player->pos.x - data->player->dir.x * s;
	
		if (data->map->map_tab[(int)(data->player->pos.y - data->player->dir.y * s)][(int)data->player->pos.x] != '1')
			data->player->pos.y = data->player->pos.y - data->player->dir.y * s;
	}
	if (keys & D && !(keys & A))
	{
		if (data->map->map_tab[(int)data->player->pos.y][(int)(data->player->pos.x - data->player->dir.y * s)] != '1')
			data->player->pos.x = data->player->pos.x - data->player->dir.y * s;

		if (data->map->map_tab[(int)(data->player->pos.y + data->player->dir.x * s)][(int)data->player->pos.x] != '1')
			data->player->pos.y = data->player->pos.y + data->player->dir.x * s;
	}
	else if (keys & A && !(keys & D))
	{
		if (data->map->map_tab[(int)data->player->pos.y][(int)(data->player->pos.x + data->player->dir.y * s)] != '1')
			data->player->pos.x = data->player->pos.x + data->player->dir.y * s;

		if (data->map->map_tab[(int)(data->player->pos.y - data->player->dir.x * s)][(int)data->player->pos.x] != '1')
			data->player->pos.y = data->player->pos.y - data->player->dir.x * s;
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
	else if (key == K_S)
		data->player->pressed_keys = data->player->pressed_keys | S;
	else if (key == K_D)
		data->player->pressed_keys = data->player->pressed_keys | D;
	else if (key == K_A)
		data->player->pressed_keys = data->player->pressed_keys | A;
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
	else if (key == K_S)
		data->player->pressed_keys = data->player->pressed_keys - S;
	else if (key == K_D)
		data->player->pressed_keys = data->player->pressed_keys - D;
	else if (key == K_A)
		data->player->pressed_keys = data->player->pressed_keys - A;
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
