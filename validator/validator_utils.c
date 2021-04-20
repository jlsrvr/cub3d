/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:33:16 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/13 12:34:01 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

static void	assign_value(t_des *desc, char direction)
{
	if (direction == 'N')
		desc->dir_x = -1;
	if (direction == 'S')
		desc->dir_x = 1;
	if (direction == 'E')
		desc->dir_y = 1;
	if (direction == 'W')
		desc->dir_y = -1;
}

void	replace_spaces(t_des *desc)
{
	char	**map;
	int		x_index;
	int		y_index;

	map = desc->map;
	y_index = -1;
	while (map[++y_index])
	{
		x_index = -1;
		while (map[y_index][++x_index])
		{
			if (ft_strchr("NESW", map[y_index][x_index]))
			{
				desc->pos_x = y_index + 0.5;
				desc->pos_y = x_index + 0.5;
				assign_value(desc, map[y_index][x_index]);
				map[y_index][x_index] = '0';
			}
			if (ft_isspace(map[y_index][x_index]))
				map[y_index][x_index] = '1';
		}
	}
}
