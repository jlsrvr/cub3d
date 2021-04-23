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

static int	store_sprite_pos(t_des *desc, int x_index, int y_index)
{
	t_sprite	*old;
	int			index;

	desc->sprite_cnt += 1;
	old = desc->sprites;
	desc->sprites = malloc(sizeof(*(desc->sprites)) * desc->sprite_cnt);
	if (!desc->sprites)
		return (1);
	index = -1;
	while (++index < desc->sprite_cnt - 1)
	{
		desc->sprites[index].pos_x = old[index].pos_x;
		desc->sprites[index].pos_y = old[index].pos_y;
	}
	desc->sprites[index].pos_x = y_index + 0.5;
	desc->sprites[index].pos_y = x_index + 0.5;
	free(old);
	return (0);
}

int			replace_spaces(t_des *desc)
{
	int		x_index;
	int		y_index;

	y_index = -1;
	while (desc->map[++y_index])
	{
		x_index = -1;
		while (desc->map[y_index][++x_index])
		{
			if (ft_strchr("NESW", desc->map[y_index][x_index]))
			{
				desc->pos_x = y_index + 0.5;
				desc->pos_y = x_index + 0.5;
				assign_value(desc, desc->map[y_index][x_index]);
				desc->map[y_index][x_index] = '0';
			}
			if (desc->map[y_index][x_index] == '2')
				if (store_sprite_pos(desc, x_index, y_index))
					return (1);
			if (ft_isspace(desc->map[y_index][x_index]))
				desc->map[y_index][x_index] = '1';
		}
	}
	return (0);
}
