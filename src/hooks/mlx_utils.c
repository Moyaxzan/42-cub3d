/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:37:22 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/18 02:03:03 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->map->walls[i]->mlx_img)
			mlx_destroy_image(data->window->mlx_ptr, \
			data->map->walls[i]->mlx_img);
		ft_free(data->map->walls[i]->path);
		ft_free(data->map->walls[i]);
		data->map->walls[i] = NULL;
		i++;
	}
}

void	free_minimap(t_data *data)
{
	if (data->map->minimap && data->map->minimap->img->mlx_img)
	{
		mlx_destroy_image(data->window->mlx_ptr, \
		data->map->minimap->img->mlx_img);
		free(data->map->minimap->img);
		data->map->minimap->img = NULL;
	}
	ft_free(data->map->minimap);
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
