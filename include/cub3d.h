/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:47:28 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/16 04:20:08 by jdufour          ###   ########.fr       */
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

# define K_ESC 65307
# define K_A_UP 65362    // move up
# define K_A_DOWN 65364  // move down
# define K_A_LEFT 65361  // move left
# define K_A_RIGHT 65363 // move right
# define K_Q 113    // change color -
# define K_W 119    // move up
# define K_E 101    // change color +
# define K_A 97     // move left
# define K_S 115    // move down
# define K_D 100    //move right
# define ROTATION_SPEED 3
# define SPEED 0.3

# define W 0b1
# define D 0b10
# define S 0b100
# define A 0b1000
# define A_RIGHT 0b10000
# define A_LEFT 0b100000

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

typedef struct s_vect
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
	double	dist;
}	t_ray;

//player (coord, orientation)
typedef struct s_player
{
	t_vect		pos;
	t_vect		dir;
	t_vect		plane;
	int			pressed_keys;
}	t_player;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	char	*path;
	int		bpp;
	int		line_len;
	int		endian;
	int		height;
	int		width;
}	t_img;

typedef struct s_minimap
{
	int		width;
	int		height;
	int		pix_factor;
	t_img	*img;
}	t_minimap;

typedef struct s_map
{
	char		*file_path;
	char		*line;
	int			fd;
	char		**map_tab;
	int			height;
	int			width;
	t_img		*walls[4];
	int			ceiling;
	int			floor;
	int			side;
	double		step;
	double		wall_x;
	double		text_pos;		
	t_vect		texture;
	t_minimap	*minimap;
}	t_map;

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
void		ft_free(void *ptr);

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
int			init_mlx(t_window *window);
void		exit_mlx(t_window *window);
void		img_pix_put(t_img *img, int x, int y, int color);
void		free_texturesnminimap(t_data *data);

/*----------render.c---------*/
int			ft_render(t_data *data);
int			ch_plr_dir(t_player *plr, t_vect dir, t_vect plane);

/*----------events.c---------*/
int			mouse_events(int x, int y, t_data *data);
int			handle_keypress(int key, t_data *data);
int			handle_keyrelease(int key, t_data *data);
int			handle_cross(t_data *data);
int			hook_n_loop(t_data *data);

/*------------ray.c-----------*/
t_ray		init_ray(t_data *data, int x);

/*------------textures.c-----------*/
int			init_textures(t_data *data);
int			get_texture_color(t_img *texture, int x, int y);
t_img		*get_texture(t_data *data, t_ray *ray);
int			place_texture(t_data *data, t_ray *ray);

/*------------moves.c-----------*/
int			rotate(t_data *data, int speed, int key);
int			move(t_data *data, int key);

/*------------minimap.c-----------*/
int			init_minimap(t_data *data);
int			minimap(t_data *data);

#endif
