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

	x = 0;
	cast = &data->cast;
	while (x < cast->width)
	{
		init_raycaster_loop(cast, x, cast->width);
		cast_ray(cast, data->desc);
		calculate_distance_to_wall(cast);
		cast->line_height = (int)(cast->height / cast->perp_wall_dist);
		define_line_start_end(cast);
		render_ray(data, (t_ray){x, cast->draw_start, cast->draw_end});
		x++;
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
	mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

static void	destroy_mlx_image(void **ptr_to_ptr, void *mlx_ptr)
{
	if(!(*ptr_to_ptr))
		return ;
	mlx_destroy_image(mlx_ptr, *ptr_to_ptr);
}

static int	destroy_mlx_resources(t_data *data)
{
		destroy_mlx_image((void **)&data->img.mlx_img, data->mlx_ptr);
		destroy_mlx_image((void **)&data->textures[0].img.mlx_img, data->mlx_ptr);
		destroy_mlx_image((void **)&data->textures[1].img.mlx_img, data->mlx_ptr);
		destroy_mlx_image((void **)&data->textures[2].img.mlx_img, data->mlx_ptr);
		destroy_mlx_image((void **)&data->textures[3].img.mlx_img, data->mlx_ptr);
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (1);
}

int			cub_engine(t_des *description)
{
	t_data	data;
	int		win_x;
	int		win_y;

	win_x = description->x_res;
	win_y = description->y_res;
	data.desc = description;
	data.mlx_ptr = mlx_init();
	if (!(data.mlx_ptr))
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, win_x, win_y, "Jules' Cub3D");
	if (!(data.win_ptr))
		return (destroy_mlx_resources(&data));
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, win_x, win_y);
	data.textures[0].img.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, data.desc->no_path, &data.textures[0].width, &data.textures[0].height);
	data.textures[1].img.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, data.desc->ea_path, &data.textures[1].width, &data.textures[1].height);
	data.textures[2].img.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, data.desc->so_path, &data.textures[2].width, &data.textures[2].height);
	data.textures[3].img.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, data.desc->we_path, &data.textures[3].width, &data.textures[3].height);
	if (!(data.img.mlx_img) || !(data.textures[0].img.mlx_img) || !(data.textures[1].img.mlx_img)|| !(data.textures[2].img.mlx_img)|| !(data.textures[3].img.mlx_img))
		return (destroy_mlx_resources(&data));
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	data.textures[0].addr = (int *)mlx_get_data_addr(data.textures[0].img.mlx_img, &data.textures[0].img.bpp, &data.textures[0].img.line_len, &data.textures[0].img.endian);
	data.textures[1].addr = (int *)mlx_get_data_addr(data.textures[1].img.mlx_img, &data.textures[1].img.bpp, &data.textures[1].img.line_len, &data.textures[1].img.endian);
	data.textures[2].addr = (int *)mlx_get_data_addr(data.textures[2].img.mlx_img, &data.textures[2].img.bpp, &data.textures[2].img.line_len, &data.textures[2].img.endian);
	data.textures[3].addr = (int *)mlx_get_data_addr(data.textures[3].img.mlx_img, &data.textures[3].img.bpp, &data.textures[3].img.line_len, &data.textures[3].img.endian);
	init_raycaster(&data.cast, description);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop_hook(data.mlx_ptr, &render_view, &data);
	mlx_loop(data.mlx_ptr);
	destroy_mlx_resources(&data);
	return (0);
}
