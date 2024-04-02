/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:27:21 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/02 12:44:07 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	int	line_nb;
	int	ret_val;

	ret_val = arg_parsing(argc, argv, data);
	if (ret_val)
		return (ret_val);
	line_nb = 1;
	ret_val = file_parsing(data, &line_nb);
	return (ret_val);
}
