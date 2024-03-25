/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:27:21 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/25 18:16:05 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// temporary error function

void	ft_errornl(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
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
	if (ft_strncmp(ext, ".cub", 4) || ft_strlen(ext) != 4)
		return (1);
	return (0);
}

//checks potential errors on arg number or validity of file

int	check_args(int argc, char **argv)
{
	if (argc != 2)
		ft_errornl("Error\nInvalid arguments. Usage : ./cub3D [path_to_map]\n");
	else if (argv[1])
	{
		if (check_map_extension(argv[1]))
			ft_errornl("Error\nInvalid map extension. Expected : *.cub\n");
		// more precise error
		if (open(argv[1], O_RDONLY) == -1)
			ft_errornl("Error\nThe selected map could not be opened\n");
	}
	return (0);
}
