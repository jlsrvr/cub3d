/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:24:21 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/22 16:25:19 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int	define_texture(t_cast *cast)
{
	int		side;
	double	ray_dir;

	ray_dir = cast->ray_dir_y;
	side = cast->side;
	if (side == 1)
	{
		if (ray_dir >= 0)
			return (3);
		return (2);
	}
	ray_dir = cast->ray_dir_x;
	if (ray_dir >= 0)
		return (1);
	return (0);
}

static void	init_transfer(t_transfer *trans, t_cast cast,
							t_texture texture, int ray_start)
{
	double pos;

	if (cast.side == 0)
		trans->wall_x = cast.pos_y + cast.perp_wall_dist * cast.ray_dir_y;
	else
		trans->wall_x = cast.pos_x + cast.perp_wall_dist * cast.ray_dir_x;
	trans->wall_x -= floor((trans->wall_x));
	trans->tex_x = (int)(trans->wall_x * (double)texture.width);
	trans->tex_x = texture.width - trans->tex_x - 1;
	trans->step = 1.0 * texture.height / cast.line_height;
	pos = (ray_start - cast.height / 2 + cast.line_height / 2) * trans->step;
	trans->tex_pos = pos;
}

void		render_ray(t_data *data, t_ray ray)
{
	int			y;
	int			tex_index;
	t_texture	texture;
	t_transfer	trans;
	int			tex_y;

	tex_index = define_texture(&data->cast);
	texture = data->textures[tex_index];
	init_transfer(&trans, data->cast, texture, ray.y_start);
	y = ray.y_start - 1;
	while (++y < ray.y_end)
	{
		tex_y = (int)trans.tex_pos & (texture.height - 1);
		trans.tex_pos += trans.step;
		img_pix_put(&data->img, ray.x, y,
				texture.addr[texture.height * tex_y + trans.tex_x]);
	}
}
