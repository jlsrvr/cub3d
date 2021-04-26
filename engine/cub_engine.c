/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_engine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:31:48 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/22 15:42:45 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int	raycaster(t_data *data)
{
	t_cast	*cast;
	int		x;

	x = -1;
	cast = &data->cast;
	while (++x < cast->width)
	{
		init_raycaster_loop(cast, x, cast->width);
		cast_ray(cast, data->desc);
		calculate_distance_to_wall(cast);
		cast->line_height = (int)(cast->height / cast->perp_wall_dist);
		define_line_start_end(cast);
		render_ray(data, (t_ray){x, cast->draw_start, cast->draw_end});
		data->wall_dist[x] = cast->perp_wall_dist;
	}
	return (0);
}

static int	render_view(t_data *data)
{
	int win_x;
	int win_y;

	if (data->win_ptr == NULL)
		return (1);
	win_x = data->desc->x_res;
	win_y = data->desc->y_res;
	render_rect(&data->img,
			(t_rect){0, win_y * 0.5, win_x, win_y / 2, data->desc->floor_c});
	render_rect(&data->img,
			(t_rect){0, 0, win_x, win_y / 2, data->desc->ceiling_c});
	raycaster(data);
	if (add_sprites(data))
		return (exit_game(data));
	mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

static void	open_textures(t_data *data)
{
	t_texture	*texture;
	int			index;
	char		*paths[5];

	paths[0] = data->desc->no_path;
	paths[1] = data->desc->ea_path;
	paths[2] = data->desc->so_path;
	paths[3] = data->desc->we_path;
	paths[4] = data->desc->s_path;
	index = -1;
	while (++index < 5)
	{
		texture = &data->textures[index];
		texture->img.mlx_img = mlx_xpm_file_to_image(data->mlx_ptr,
					paths[index], &texture->width, &texture->height);
	}
}

static int	init_images(t_data *data)
{
	int			index;
	t_texture	*texture;

	open_textures(data);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, data->desc->x_res,
										data->desc->y_res);
	if (!(data->img.mlx_img) || !(data->textures[0].img.mlx_img)
			|| !(data->textures[1].img.mlx_img)
			|| !(data->textures[2].img.mlx_img)
			|| !(data->textures[3].img.mlx_img)
			|| !(data->textures[4].img.mlx_img))
		return (destroy_mlx_resources(data));
	index = -1;
	while (++index < 5)
	{
		texture = &data->textures[index];
		texture->addr = (int *)mlx_get_data_addr(texture->img.mlx_img,
								&texture->img.bpp, &texture->img.line_len,
								&texture->img.endian);
	}
	data->img.addr = mlx_get_data_addr(data->img.mlx_img,
						&data->img.bpp, &data->img.line_len, &data->img.endian);
	return (0);
}

int			cub_engine(t_des *description)
{
	t_data	data;

	data.desc = description;
	data.mlx_ptr = mlx_init();
	if (!(data.mlx_ptr))
		return (1);
	set_screen_resolution(data.mlx_ptr, &data.desc->x_res, &data.desc->y_res);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.desc->x_res,
			data.desc->y_res, "Jules' Cub3D");
	data.wall_dist = malloc(sizeof(*data.wall_dist) * data.desc->x_res);
	if (!(data.win_ptr) || !(data.wall_dist))
		return (destroy_mlx_resources(&data));
	if (init_images(&data))
		return (1);
	init_raycaster(&data.cast, description);
	mlx_hook(data.win_ptr, KEY_PRESS, (1L<<0), &handle_keypress, &data);
	mlx_loop_hook(data.mlx_ptr, &render_view, &data);
	mlx_hook(data.win_ptr, CROSS_PRESS, (1L<<17), &exit_game, &data);
	mlx_loop(data.mlx_ptr);
	destroy_mlx_resources(&data);
	return (0);
}
