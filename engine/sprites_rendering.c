/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:40:04 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/25 15:40:06 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	sprite_init_calculations(t_data *data,
		t_sprite_vars *vars)
{
	t_cast	cast;
	double	inv_det;
	double	spt_x;
	double	spt_y;

	cast = data->cast;
	spt_x = vars->sprite_x;
	spt_y = vars->sprite_y;
	inv_det = 1.0 / (cast.plane_x * cast.dir_y - cast.dir_x * cast.plane_y);
	vars->transform_x = inv_det * (cast.dir_y * spt_x - cast.dir_x * spt_y);
	vars->transform_y = inv_det * (-cast.plane_y * spt_x +
			cast.plane_x * spt_y);
	vars->sprite_screen_x = (int)(
			(cast.width / 2) * (1 + vars->transform_x / vars->transform_y));
	vars->sprite_height = abs((int)(cast.height / (vars->transform_y)));
	vars->sprite_width = abs((int)(cast.height / (vars->transform_y)));
}

static void	define_start_end(t_sprite_vars *vars, t_data *data)
{
	t_cast	cast;
	int		s_height;
	int		s_width;

	s_height = vars->sprite_height;
	s_width = vars->sprite_width;
	cast = data->cast;
	vars->draw_start_y = -s_height / 2 + cast.height / 2;
	if (vars->draw_start_y < 0)
		vars->draw_start_y = 0;
	vars->draw_end_y = s_height / 2 + cast.height / 2;
	if (vars->draw_end_y >= cast.height)
		vars->draw_end_y = cast.height - 1;
	vars->draw_start_x = -s_width / 2 + vars->sprite_screen_x;
	if (vars->draw_start_x < 0)
		vars->draw_start_x = 0;
	vars->draw_end_x = s_width / 2 + vars->sprite_screen_x;
	if (vars->draw_end_x >= cast.width)
		vars->draw_end_x = cast.width - 1;
}

static void	img_stripe_put(t_data *data, int x, int tex_x, t_sprite_vars vars)
{
	int			y;
	int			d;
	int			tex_y;
	int			colour;
	t_texture	texture;

	texture = data->textures[4];
	y = vars.draw_start_y - 1;
	while (++y < vars.draw_end_y)
	{
		d = y * 256 - data->cast.height * 128 + vars.sprite_height * 128;
		tex_y = ((d * texture.height) / vars.sprite_height) / 256;
		colour = texture.addr[texture.width * tex_y + tex_x];
		if ((colour & 0x00FFFFFF) != 0)
			img_pix_put(&data->img, x, y, colour);
	}
}

static void	draw_sprite(t_sprite_vars vars, t_data *data)
{
	int	stripe;
	int	tex_x;
	int	s_width;

	s_width = vars.sprite_width;
	stripe = vars.draw_start_x - 1;
	while (++stripe < vars.draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-s_width / 2 + vars.sprite_screen_x))
								* data->textures[4].width / s_width) / 256;
		if (vars.transform_y > 0
				&& stripe > 0
				&& stripe < data->cast.width
				&& vars.transform_y < data->wall_dist[stripe])
			img_stripe_put(data, stripe, tex_x, vars);
	}
}

int			add_sprites(t_data *data)
{
	int				index;
	int				*sprite_order;
	double			*sprite_dist;
	t_sprite_vars	vars;
	t_sprite		sprite;

	if (init_sprite_order(data, &sprite_order, &sprite_dist))
		return (1);
	index = -1;
	while (++index < data->desc->sprite_cnt)
	{
		sprite = data->desc->sprites[sprite_order[index]];
		vars.sprite_x = sprite.pos_x - data->cast.pos_x;
		vars.sprite_y = sprite.pos_y - data->cast.pos_y;
		sprite_init_calculations(data, &vars);
		define_start_end(&vars, data);
		draw_sprite(vars, data);
	}
	free(sprite_order);
	free(sprite_dist);
	return (0);
}
