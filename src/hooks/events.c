/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:52:57 by taospa            #+#    #+#             */
/*   Updated: 2024/04/18 01:24:22 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	hook_n_loop(t_data *data)
{
	mlx_hook(data->window->win_ptr, KeyPress,
		KeyPressMask, &handle_keypress, data);
	mlx_hook(data->window->win_ptr, KeyRelease,
		KeyReleaseMask, &handle_keyrelease, data);
	mlx_hook(data->window->win_ptr, 6, 1L << 6, mouse_events, data);
	mlx_hook(data->window->win_ptr, DestroyNotify, 0, &handle_cross, data);
	mlx_loop_hook(data->window->mlx_ptr, &handle_no_events, data);
	mlx_loop(data->window->mlx_ptr);
	return (0);
}
