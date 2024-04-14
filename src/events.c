/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:52:57 by taospa            #+#    #+#             */
/*   Updated: 2024/04/15 01:08:49 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	hook_n_loop(t_data *data)
{
	mlx_hook(data->window->win_ptr, KeyPress,
		KeyPressMask, &handle_keypress, data);
	mlx_hook(data->window->win_ptr, KeyRelease,
		KeyReleaseMask, &handle_keyrelease, data);
	mlx_hook(data->window->win_ptr, 6, 1L << 6, mouse_events, data);
	mlx_hook(data->window->win_ptr, DestroyNotify, 0, &handle_cross, data);
	mlx_loop(data->window->mlx_ptr);
	return (0);
}

int	handle_cross(t_data *data)
{
	clean_exit(data);
	return (0);
}

int	handle_keypress(int key, t_data *data)
{
	// printf("keypress = %d\n", key);
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
	// printf("keyrelease = %d\n", key);
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

// A corriger : le premier deplacement prend en compte le tout premier rotate meme si la
// souris a ete recentrée
// Egalement : pas mis le ft_render pour l'instant dc les rotations de souris s'effectuent
// en mm tps que les deplacements, sinon trop de lag

int	mouse_events(int x, int y, t_data *data)
{
	(void)y;
	if ((double)x < WIN_WIDTH / 6)
		rotate(data, ROTATION_SPEED / 2, A_LEFT);
	else if ((double)x > WIN_WIDTH / 1.2)
		rotate(data, ROTATION_SPEED / 2, A_RIGHT);
	// ft_render(data);
	return (SUCCESS);
}
