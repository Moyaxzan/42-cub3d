/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:47:28 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/02 12:57:25 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# define SUCCESS 0
# define PARSING_ERROR 3
# define UNKNOWN_ERROR 2
# define MLX_ERROR 666

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

//player (coord, orientation)
typedef struct s_player {
	char	orient;
	int		pos_x;
	int		pos_y;
}	t_player;

//map (images, floor, plafond, map_table)
typedef struct s_map {
	char	*file_path;
	char	*line;
	int		fd;
	char	**map_tab;
	int		map_height;
	int		map_width;
	char	*walls[4];
	int		ceiling;
	int		floor;
}	t_map;

//data(map, player)
typedef struct s_data {
	t_player	*player;
	t_map		*map;
}	t_data;

/*______________________PARSING_________________________*/

/*---------init.c---------*/
t_map		*init_map(void);
t_player	*init_player(void);
t_data		*init_data(void);

/*---------parsing.c---------*/
int			parsing(int argc, char **argv, t_data *data);
void		ft_errornl(char *str);
void		free_dchartab(char **tab);

/*---------file_parsing.c---------*/
int			file_parserr(char *line, int line_nb);

/*---------map_parsing.c---------*/
int			parse_map(t_data *data);
int			finish_gnl(t_data *data);

/*---------map_checks.c---------*/
int			map_checks(t_data *data);

/*-----------rgb.c-----------*/
int			rgb_to_int(char *line);

/*---------arg_parsing.c---------*/
int			arg_parsing(int argc, char **argv, t_data *data);
int			file_parsing(t_data *data, int *line_nb);

/*-----------utils_checks.c-----------*/
int			space_or_one(char c);
int			ft_is_player_pos(char c);
int			ft_isspace(int c);
int			ft_is_empty_line(char *line);
int			ft_isnum(char *str);

/*-----------utils.c-----------*/
char		**ft_strjoin_map(char **tab, char *line);

#endif
