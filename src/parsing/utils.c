/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:44:14 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/23 11:40:01 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**ft_strjoin_map(char **tab, char *line)
{
	char	**new_tab;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (tab[count])
		count++;
	count++;
	new_tab = malloc(sizeof(char *) * (count + 1));
	if (!new_tab)
		return (NULL);
	while (tab[i])
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[i] = line;
	new_tab[i + 1] = NULL;
	free(tab);
	return (new_tab);
}

int	error_map(t_data *data)
{
	ft_putstr_fd("Error\nMap not closed\n", 2);
	return (cherr_code(data, PARSING_ERROR));
}

void	free_n_gnl(t_data *data)
{
	free(data->map->line);
	data->map->line = get_next_line(data->map->fd);
	data->map->line_nb++;
}
