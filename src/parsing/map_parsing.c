/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:27:28 by jdufour           #+#    #+#             */
/*   Updated: 2024/03/25 18:44:22 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Assigns the textures on the right index depending on the key (NO SO WE EA)

int	get_text_index(char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (NORTH);
	if (!ft_strncmp(line, "SO", 2))
		return (SOUTH);
	if (!ft_strncmp(line, "WE", 2))
		return (WEST);
	if (!ft_strncmp(line, "EA", 2))
		return (EAST);	
	return (-1);
}

// checks on the validity of the texture path

int	text_path_ok(char *line)
{
	int		i;

	i = 0;
	if (get_text_index(line) == -1)
		return (0);
	//skip cardinal + whitespaces
	if (open(line + 3, O_RDONLY) == -1)
		return (0);
	return (1);
}

// checks if we got all of the 4 textures for NO SO WE EA

int	got_all_text(char **tab)
{
	int	i;
	
	i = 0;
	while (i < 4)
	{
		if (!tab[i])
			return (0);
		i++;
	}
	return (1);
}

// not written yet but will check on the ceiling & floor color syntax

int	colors_ok(char *line)
{
	
}

// way too long and messy, just a first try on how to structure the parsing
// for now it only assigns the NO SO WE EA textures to the struct

int	parsing(t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(data->map->file_path, O_RDONLY);
	i = 0;
	if (fd == -1)
		ft_errornl("Error\n Map could not be opened\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!text_path_ok(line))
			break;
		if (!data->map->walls[get_text_index(line)])
			data->map->walls[get_text_index(line)] = ft_strdup(line + 3);
		else
		{
			free(line);
			ft_errornl("Error\n Texture in double\n");
		}
		if (!data->map->walls[get_text_index(line)])
		{
			free(line);
			ft_errornl("Error\n Failed strdup on texture storage\n");
		}
	}
	if (!got_all_text(data->map->walls))
	{
		free(line);
		ft_errornl("Error\n");
	}
	
}

// just the testing main 

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;

// 	printf("YO\n");
// 	int	fd = open("maps/map2.cub", O_RDONLY);
// 	char	*line = NULL;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 		break;
// 		printf("line = %s", line);
// 		free (line);
// 	}
// 	close (fd);
// }
