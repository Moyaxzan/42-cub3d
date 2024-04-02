/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaint-p </var/spool/mail/tsaint-p>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:15:26 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/04/02 12:18:42 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**get_rgb_tab(char *line)
{
	char	**split_rgb;
	int		cpt;

	split_rgb = ft_split(line, ',');
	if (!split_rgb)
		return (free(line), free_dchartab(split_rgb), NULL);
	cpt = 0;
	while (split_rgb[cpt])
		cpt++;
	if (cpt != 3 || (ft_strlen(split_rgb[0]) > 3)
		|| (ft_strlen(split_rgb[1]) > 3) || (ft_strlen(split_rgb[2]) > 3))
		return (free(line), free_dchartab(split_rgb), NULL);
	return (split_rgb);
}

int	get_rgb_val(char *str_rgb)
{
	int	val;

	if (!ft_isnum(str_rgb))
		return (-1);
	val = ft_atoi(str_rgb);
	if (val > 255 || val < 0)
		return (-1);
	return (val);
}

// split with ',' ? check if 3 componoents + atoi + bitshift
// implement error messages
int	rgb_to_int(char *line)
{
	char	**split_rgb;
	int		cpt;
	int		res;
	int		val;

	if (!line)
		return (-1);
	split_rgb = get_rgb_tab(line);
	if (!split_rgb)
		return (-1);
	cpt = 0;
	res = 0;
	while (split_rgb[cpt])
	{
		val = get_rgb_val(split_rgb[cpt++]);
		if (val == -1)
			return (free(line), free_dchartab(split_rgb), -1);
		res = (res << 8) + val;
	}
	return (free_dchartab(split_rgb), free(line), res);
}

