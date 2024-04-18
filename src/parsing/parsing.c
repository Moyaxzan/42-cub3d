/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:27:21 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/18 01:23:55 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ch_plr_dir(t_player *plr, t_vect dir, t_vect plane, char c)
{
	plr->dir = dir;
	plr->plane = plane;
	plr->c_dir = c;
	return (0);
}

void	ft_errornl(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	free_dchartab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	parsing(int argc, char **argv, t_data *data)
{
	if (arg_parsing(argc, argv, data))
		return (data->err_code);
	data->map->line_nb = 1;
	if (file_parsing(data))
		return (data->err_code);
	return (SUCCESS);
}
