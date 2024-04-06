/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taospa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:46:22 by taospa            #+#    #+#             */
/*   Updated: 2024/04/06 17:07:32 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	cast_ray(t_data *data, int x)
{
	t_ray	ray;

	ray.len = 0;

	return (0);
}

int	ft_render(t_data *data)
{
	int	x = 0;

	// mlx_clear_window(data->window->mlx_ptr, data->window->win_ptr);
	while (x < WIN_WIDTH)
	{
		cast_ray(data, x);
		x++;
	}
	mlx_put_image_to_window(data->window->mlx_ptr, data->window->win_ptr, data->window->image->mlx_img, 0, 0);
	return (0);
}
