/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:01:02 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/02 12:54:29 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//checks if the map extension is indeed .cub

int	check_map_extension(char *str)
{
	if (!str)
		return (1);
	if (ft_strlen(str) < 4)
		return (1);
	if (ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4))
		return (1);
	return (0);
}

//checks potential errors on arg number or validity of file

int	arg_parsing(int argc, char **argv, t_data *data)
{
	if (argc != 2)
		return (ft_errornl("Invalid arguments. Usage : ./cub3D [path_to_map]\n")
			, cherr_code(data, PARSING_ERROR));
	if (check_map_extension(argv[1]))
		return (ft_errornl("Invalid map extension. Expected : *.cub\n")
			, cherr_code(data, PARSING_ERROR));
	data->map->fd = open(argv[1], O_RDONLY);
	if (data->map->fd == -1)
		return (ft_errornl(strerror(errno)), cherr_code(data, errno));
	return (0);
}
