/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:47:28 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/25 18:44:37 by tsaint-p         ###   ########.fr       */
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


# define PARSING_ERROR 1
# define MLX_ERROR 666


# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3


//player (coord, orientation)
// typedef struct s_player {
// }	t_player;

//map (images, floor, plafond, map_table)

typedef struct s_map {
	char	*file_path;
	char	**map;
	char	*walls[4];
	int		ceiling;
	int		floor;
}	t_map;

//data(map, player)
//
typedef struct s_data {
	//player
	t_map	*map;
}	t_data;


/*---------parsing.c---------*/
int	parsing(t_data *data);

/*---------arg_parsing.c---------*/
void	ft_errornl(char *str);

#endif
