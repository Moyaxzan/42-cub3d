/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:27:28 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/14 20:03:15 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	file_parserr(t_data *data, char *line, int line_nb)
{
	if (line)
	{
		write(2, "Error\nUnexpected character.\nl.", 30);
		ft_putnbr_fd(line_nb, 2);
		write(2, ": ", 2);
		write(2, line, ft_strlen(line));
	}
	else
		write(2, "Error\nmissing informations\n", 26);
	return (cherr_code(data, PARSING_ERROR));
}

int	fill_element(t_data *data, char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (!*line)
		return (0);
	if (!ft_strncmp(line, "NO", 2))
		data->map->walls[NORTH]->path = ft_strtrim(line + 2, " \t\n\v\r");
	else if (!ft_strncmp(line, "SO", 2))
		data->map->walls[SOUTH]->path = ft_strtrim(line + 2, " \t\n\v\r");
	else if (!ft_strncmp(line, "WE", 2))
		data->map->walls[WEST]->path = ft_strtrim(line + 2, " \t\n\v\r");
	else if (!ft_strncmp(line, "EA", 2))
		data->map->walls[EAST]->path = ft_strtrim(line + 2, " \t\n\v\r");
	else if (!ft_strncmp(line, "F", 1))
		data->map->floor = rgb_to_int(ft_strtrim(line + 1, " \t\n\v\r"));
	else if (!ft_strncmp(line, "C", 1))
		data->map->ceiling = rgb_to_int(ft_strtrim(line + 1, " \t\n\v\r"));
	else
		return (PARSING_ERROR);
	return (1);
}

int	parse_elements(t_data *data, int *line_nb)
{
	int		nb_elem;
	int		filled;

	nb_elem = 0;
	filled = 0;
	data->map->line = get_next_line(data->map->fd);
	while (data->map->line && nb_elem < 6)
	{
		filled = fill_element(data, data->map->line);
		if (errno == ENOMEM)
			return (strerror(errno), cherr_code(data, ENOMEM));
		else if (filled == PARSING_ERROR)
			return (file_parserr(data, data->map->line, *line_nb));
		else if (filled)
			nb_elem++;
		free(data->map->line);
		if (nb_elem == 6)
			break ;
		data->map->line = get_next_line(data->map->fd);
		(*line_nb)++;
	}
	return (SUCCESS);
}

int	check_texture_path(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 3)
	{
		fd = open(data->map->walls[i++]->path, O_RDONLY);
		if (fd == -1)
			return (ft_errornl(strerror(errno)), cherr_code(data, errno));
		close(fd);
	}
	return (0);
}

int	file_parsing(t_data *data, int *line_nb)
{
	if (parse_elements(data, line_nb))
	{
		finish_gnl(data);
		return (data->err_code);
	}
	if (parse_map(data))
	{
		finish_gnl(data);
		return (data->err_code);
	}
	if (check_texture_path(data))
		return (PARSING_ERROR);
	if (map_checks(data))
		return (data->err_code);
	return (SUCCESS);
}
