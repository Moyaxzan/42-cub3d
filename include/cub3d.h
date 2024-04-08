/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:47:28 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/09 00:39:50 by taospa           ###   ########.fr       */
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
# include <X11/X.h>
# include <math.h>
# include <limits.h>

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800

# define SUCCESS 0
# define PARSING_ERROR 3
# define UNKNOWN_ERROR 2
# define MLX_ERROR 666

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

typedef	struct s_vect
{
	double	x;
	double	y;
}	t_vect;

typedef struct s_ray
{
	t_vect	dir;
	t_vect	side;
	t_vect	delta;
	t_vect	step;
}	t_ray;

//player (coord, orientation)
typedef struct s_player
{
	t_vect		pos;
	t_vect		dir;
	t_vect		plane;
}	t_player;

//map (images, floor, plafond, map_table)
typedef struct s_map
{
	char	*file_path;
	char	*line;
	int		fd;
	char	**map_tab;
	int		height;
	int		width;
	char	*walls[4];
	int		ceiling;
	int		floor;
}	t_map;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*image;
}	t_window;

//data(map, player)
typedef struct s_data
{
	int			err_code;
	t_player	*player;
	t_map		*map;
	t_window	*window;
}	t_data;

/*-----------main.c----------*/
int			cherr_code(t_data *data, int err_code);
int			clean_exit(t_data *data);

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
int			file_parserr(t_data *data, char *line, int line_nb);

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

/*----------mlx_utils.c---------*/
t_window	*init_window(void);
int			init_mlx(t_window *window);
void		exit_mlx(t_window *window);
int			hook_n_loop(t_data *data);
void		img_pix_put(t_img *img, int x, int y, int color);

/*----------render.c---------*/
int			ft_render(t_data *data);
int			ch_plr_dir(t_player *plr, t_vect dir, t_vect plane);

#endif
