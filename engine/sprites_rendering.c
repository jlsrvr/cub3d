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
	int index;
	int	*sprite_order;
	double *sprite_dist;
	t_sprite sprite;
	double sprite_x;
	double sprite_y;
	double inv_det;
	double transform_x;
	double transform_y;
	int sprite_screen_x;
	int sprite_height;
	int sprite_width;
	int draw_start_y;
	int draw_end_y;
	int draw_start_x;
	int draw_end_x;
	int stripe;
	int tex_x;
	int tex_y;
	int y;
	int d;
	int colour;

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

	index = -1;
	while (++index < data->desc->sprite_cnt)
	{
		sprite_x = data->desc->sprites[sprite_order[index]].pos_x - data->cast.pos_x;
		sprite_y = data->desc->sprites[sprite_order[index]].pos_y - data->cast.pos_y;
		inv_det = 1.0 / (data->cast.plane_x * data->cast.dir_y - data->cast.dir_x * data->cast.plane_y);
		transform_x = inv_det * (data->cast.dir_y * sprite_x - data->cast.dir_x * sprite_y);
		transform_y = inv_det * (-data->cast.plane_y * sprite_x + data->cast.plane_x * sprite_y);
		sprite_screen_x = (int)((data->cast.height / 2) * (1 + transform_x / transform_y));
		sprite_height = abs((int)(data->cast.height / (transform_y)));
		draw_start_y = -sprite_height / 2 + data->cast.height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		draw_end_y = sprite_height / 2 + data->cast.height / 2;
		if (draw_end_y >= data->cast.height)
			draw_end_y = data->cast.height - 1;
		sprite_width = abs((int)(data->cast.height / (transform_y))); //seems weird to use height again here
		draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= data->cast.width)
			draw_end_x = data->cast.width - 1;
		stripe = draw_start_x - 1;
		while (++stripe < draw_end_x)
		{
			tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * data->textures[4].width / sprite_width) / 256;
			if (transform_y > 0 && stripe > 0 && stripe < data->cast.width && transform_y < data->wall_dist[stripe])
			{
				y = draw_start_y - 1;
				while (++y < draw_end_y)
				{
					d = (y) * 256 - data->cast.height + sprite_height * 128;
					tex_y = ((d * data->textures[4].height) / sprite_height) / 256;
					colour = 0xff0000; //data->textures[4].addr[data->textures[4].width * tex_y + tex_x];
					if ((colour & 0x00FFFFFF) != 0)
						img_pix_put(&data->img, stripe, y, colour);
				}
			}
		}
	}
	free(sprite_order);
	free(sprite_dist);
	return (0);
}
