/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:37:22 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/09 19:54:08 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

t_window	*init_window(void)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
		return (0x0);
	window->mlx_ptr = 0x0;
	window->win_ptr = 0x0;
	return (window);
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

// inputs handleing
int	handle_cross(t_data *data)
{
	clean_exit(data);
	return (0);
}

int	hook_n_loop(t_data *data)
{
	mlx_key_hook(data->window->win_ptr, &handle_input, data);
	mlx_mouse_hook(data->window->win_ptr, &mouse_events, data);
	mlx_hook(data->window->win_ptr, DestroyNotify, 0, &handle_cross, data);
	mlx_loop(data->window->mlx_ptr);
	return (0);
}
