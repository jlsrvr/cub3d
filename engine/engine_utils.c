/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:52:18 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/22 16:05:06 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		pix_pos;
	int		i;

	i = img->bpp - 8;
	pix_pos = y * img->line_len + x * (img->bpp / 8);
	pixel = img->addr + pix_pos;
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
}

void	cast_ray(t_cast *cast, t_des *desc)
{
	while (cast->hit == 0)
	{
		if (cast->side_dist_x < cast->side_dist_y)
		{
			cast->side_dist_x += cast->delta_dist_x;
			cast->map_x += cast->step_x;
			cast->side = 0;
		}
		else
		{
			cast->side_dist_y += cast->delta_dist_y;
			cast->map_y += cast->step_y;
			cast->side = 1;
		}
		if (desc->map[cast->map_x][cast->map_y] == '1')
			cast->hit = 1;
	}
}

void	calculate_distance_to_wall(t_cast *cast)
{
	int		map_cor;
	int		step;
	double	pos;
	double	ray_dir;

	if (cast->side == 0)
	{
		map_cor = cast->map_x;
		pos = cast->pos_x;
		step = cast->step_x;
		ray_dir = cast->ray_dir_x;
	}
	else
	{
		map_cor = cast->map_y;
		pos = cast->pos_y;
		step = cast->step_y;
		ray_dir = cast->ray_dir_y;
	}
	cast->perp_wall_dist = (map_cor - pos + (1 - step) / 2) / ray_dir;
}

void	define_line_start_end(t_cast *cast)
{
	cast->draw_start = -cast->line_height / 2 + cast->height / 2;
	if (cast->draw_start < 0)
		cast->draw_start = 0;
	cast->draw_end = cast->line_height / 2 + cast->height / 2;
	if (cast->draw_end >= cast->height)
		cast->draw_end = cast->height - 1;
}
