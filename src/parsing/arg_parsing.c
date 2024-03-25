/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:27:21 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/25 17:26:51 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// temporary error function

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

//checks if the map extension is indeed .cub

int	check_map_extension(char *str)
{
	char	*ext;
	
	if (!str)
		return (1);
	if (!ft_strchr(str, '.'))
		return (1);
	ext = ft_strchr(str, '.');
	if (ft_strcmp(ext, ".cub") || ft_strlen(ext) != 4)
		return (1);
	return (0);
}

//checks potential errors on arg number or validity of file

int	check_args(int argc, char **argv)
{
	if (argc != 2)
		ft_error("Invalid arguments. Usage : ./cub3D [path_to_map]\n");
	else if (argv[1])
	{
		if (check_map_extension(argv[1]))
			ft_error("Invalid map extension. Expected : *.cub\n");
		if (open(argv[1], O_RDONLY) == -1)
			ft_error("Error : the selected map could not be opened\n");
	}
	return (0);
}
