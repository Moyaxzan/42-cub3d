/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:18:26 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/23 14:56:06 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	handle_no_events(t_data *data)
{
	move(data, data->player->pressed_keys);
	ft_render(data);
	return (0);
}

int	handle_cross(t_data *data)
{
	clean_exit(data);
	return (0);
}

int	handle_keypress(int key, t_data *data)
{
	if (key == K_TAB)
		data->map->minimap->display = !data->map->minimap->display;
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
	return (SUCCESS);
}

int	handle_keyrelease(int key, t_data *data)
{
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
	return (SUCCESS);
}

// mlx_mouse_hide(data->window->mlx_ptr, data->window->win_ptr);
int	mouse_events(int x, int y, t_data *data)
{
	(void)y;
	if (x < WIN_WIDTH / 2)
		rotate(data, ROTATION_SPEED * (x - WIN_WIDTH) * 0.005, A_RIGHT);
	else if (x > WIN_WIDTH / 2)
		rotate(data, ROTATION_SPEED * (x - WIN_WIDTH) * 0.005, A_LEFT);
	return (SUCCESS);
}
