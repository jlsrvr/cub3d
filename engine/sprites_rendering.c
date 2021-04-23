/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:29:09 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/23 11:29:12 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

// needs to sort from farstest to closest
static void sort_sprites(int *order, double *dist, int amount)
{
	int index;
	int icomp;
	int temp_order;
	double temp_dist;

	index = -1;
	while (++index < amount)
	{
		icomp = index;
		while (++icomp < amount)
		{
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
}

int	add_sprites(t_data *data)
{
	int	*sprite_order;
	double *sprite_dist;
	int index;
	t_sprite sprite;

	sprite_order = malloc(sizeof(*sprite_order) * data->desc->sprite_cnt);
	sprite_dist = malloc(sizeof(*sprite_dist) * data->desc->sprite_cnt);
	if (!sprite_order || !sprite_dist)
	{
		free(sprite_order);
		free(sprite_dist);
		return (1);
	}
	index = -1;
	while (++index < data->desc->sprite_cnt)
	{
		sprite = data->desc->sprites[index];
		sprite_order[index] = index;
		sprite_dist[index] = ((data->cast.pos_x - sprite.pos_x) * (data->cast.pos_x - sprite.pos_x) + (data->cast.pos_y - sprite.pos_y) * (data->cast.pos_y - sprite.pos_y));
	}
	sort_sprites(sprite_order, sprite_dist, data->desc->sprite_cnt);
	free(sprite_order);
	free(sprite_dist);

	return (0);
}
