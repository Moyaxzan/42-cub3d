/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:27:28 by jdufour           #+#    #+#             */
/*   Updated: 2024/03/25 17:37:21 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Assigns the textures on the right index depending on the key (NO SO WE EA)

int	get_text_index(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (NORTH);
	if (!ft_strncmp(line, "SO ", 3))
		return (SOUTH);
	if (!ft_strncmp(line, "WE ", 3))
		return (WEST);
	if (!ft_strncmp(line, "EA ", 3))
		return (EAST);	
	else
		return (-1);
}

// checks on the validity of the texture path

int	text_path_ok(char *line)
{
	int		i;
	char	*path;

	i = 0;
	if (get_text_index == -1)
		return (0);
	path = ft_strdup(line + 3);
	if (!path)
		return (0);
	if (open(path, O_RDONLY) == -1)
	{
		free(path);
		return (0);
	}
	free(path);
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

int	parsing(char *path, t_map *map)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(path, O_RDONLY);
	i = 0;
	if (fd == -1)
		ft_error("Error\n Map could not be opened\n");
	map->walls = malloc(sizeof(char *) * 4);
	if (!map->walls)
		ft_error("Error\n Failed malloc on texture path tab\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!text_path_ok(line))
			break;
		if (!map->walls[get_text_index(line)])
			map->walls[get_text_index(line)] = ft_strdup(line + 3);
		else
		{
			free(line);
			ft_error("Error\n Texture in double\n");
		}
		if (!map->walls[get_text_index(line)])
		{
			free(line);
			ft_error("Error\n Failed strdup on texture storage\n");
		}
	}
	if (!got_all_text(map->walls))
	{
		free(line);
		ft_error("Error\n");
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