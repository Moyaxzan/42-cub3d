/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:18:26 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/17 12:19:34 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	handle_no_events(t_data *data)
{
	printf("no events\n");
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

// A corriger : le premier deplacement prend en compte le tout premier 
// rotate meme si la souris a ete recentrée
// Egalement : pas mis le ft_render pour l'instant dc les rotations 
// de souris s'effectuent en mm tps que les deplacements, sinon trop 
// de lag

int	mouse_events(int x, int y, t_data *data)
{
	(void)y;
	if ((double)x < WIN_WIDTH / 6)
		rotate(data, ROTATION_SPEED / 3, A_LEFT);
	else if ((double)x > WIN_WIDTH / 1.2)
		rotate(data, ROTATION_SPEED / 3, A_RIGHT);
	// ft_render(data);
	return (SUCCESS);
}
