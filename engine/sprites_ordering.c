/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_ordering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:39:53 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/25 15:39:56 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	sort_sprites(int *order, double *dist, int amount)
{
	int		index;
	int		icomp;
	int		temp_order;
	double	temp_dist;

	index = -1;
	while (++index < amount)
	{
		icomp = index;
		while (++icomp < amount)
			if (dist[index] < dist[icomp])
			{
				temp_order = order[index];
				temp_dist = dist[index];
				order[index] = order[icomp];
				dist[index] = dist[icomp];
				order[icomp] = temp_order;
				dist[icomp] = temp_dist;
			}
	}
}

int			init_sprite_order(t_data *data, int **s_order, double **s_dist)
{
	int			index;
	double		pos_x;
	double		pos_y;
	t_sprite	sprite;

	*s_order = malloc(sizeof(**s_order) * data->desc->sprite_cnt);
	*s_dist = malloc(sizeof(**s_dist) * data->desc->sprite_cnt);
	if (!*s_order || !*s_dist)
	{
		free(s_order);
		free(s_dist);
		return (1);
	}
	index = -1;
	while (++index < data->desc->sprite_cnt)
	{
		pos_x = data->cast.pos_x;
		pos_y = data->cast.pos_y;
		sprite = data->desc->sprites[index];
		(*s_order)[index] = index;
		(*s_dist)[index] = ((pos_x - sprite.pos_x) * (pos_x - sprite.pos_x)
				+ (pos_y - sprite.pos_y) * (pos_y - sprite.pos_y));
	}
	sort_sprites(*s_order, *s_dist, data->desc->sprite_cnt);
	return (0);
}
