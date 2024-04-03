/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:37:22 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/03 16:26:56 by taospa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_mlx(t_window *window)
{
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
		return (MLX_ERROR);
	window->win_ptr
		= mlx_new_window(window->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!window->win_ptr)
	{
		free(window->mlx_ptr);
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
	// mlx_destroy_image(window->mlx_ptr, window->img.mlx_img);
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

int	hook_n_loop(t_window *window)
{
	// mlx_key_hook(window->win_ptr, &handle_input, window);
	// mlx_mouse_hook(window->win_ptr, &mouse_events, window);
	// mlx_hook(window->win_ptr, DestroyNotify, 0, &handle_cross, window);
	mlx_loop(window->mlx_ptr);
	return (0);
}
