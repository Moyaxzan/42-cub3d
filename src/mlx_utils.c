/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:37:22 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/14 20:50:02 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_textures(t_data *data)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		data->map->walls[i]->mlx_img = mlx_xpm_file_to_image(data->window->mlx_ptr, \
		data->map->walls[i]->path, &data->map->walls[i]->width, &data->map->walls[i]->height);
		i++;
	}
	return (SUCCESS);
}

int	init_mlx(t_window *win)
{
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		return (MLX_ERROR);
	win->win_ptr
		= mlx_new_window(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	win->image = malloc(sizeof(t_img));
	if (!win->image)
		return (free(win->mlx_ptr), ENOMEM);
	win->image->mlx_img = mlx_new_image(win->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!win->image->mlx_img)
		return (MLX_ERROR);
	win->image->addr = mlx_get_data_addr
		(win->image->mlx_img, &(win->image->bpp),
			&(win->image->line_len), &(win->image->endian));
	if (!win->image->addr)
		return (MLX_ERROR);
	if (!win->win_ptr)
	{
		free(win->mlx_ptr);
		return (MLX_ERROR);
	}
	return (0);
}

void	exit_mlx(t_window *window)
{
	if (!window)
		return ;
	if (!window->mlx_ptr)
		return (free(window));
	if (window->image->mlx_img)
	{
		mlx_destroy_image(window->mlx_ptr, window->image->mlx_img);
		free(window->image);
		window->image = NULL;
	}
	mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	mlx_destroy_display(window->mlx_ptr);
	free(window->mlx_ptr);
	free(window);
	window = NULL;
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}
