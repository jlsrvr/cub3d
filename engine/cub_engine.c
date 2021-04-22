//////HEADER?????//
//
//

#include "engine.h"

static int define_texture(t_cast *cast)
{
	int side;
	double ray_dir;

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

int render_ray(t_data *data, t_ray ray)
{
	int y;
	int tex_index;
	double  wall_x;
	int tex_x;
	int tex_y;
	double step;
	int tex_height;
	int tex_width;
	double tex_pos;
	int colour;

	tex_index = define_texture(&data->cast);
	tex_width = data->textures[tex_index].width;
	tex_height = data->textures[tex_index].height;

	if (data->cast.side == 0)
		wall_x = data->cast.pos_y + data->cast.perp_wall_dist * data->cast.ray_dir_y;
	else
		wall_x = data->cast.pos_x + data->cast.perp_wall_dist * data->cast.ray_dir_x;
	wall_x -= floor((wall_x));

	tex_x = (int)(wall_x * (double)tex_width);
	if ((data->cast.side == 0 && data->cast.ray_dir_x > 0) || (data->cast.side == 1 && data->cast.ray_dir_x < 0))
		tex_x = tex_width - tex_x - 1;
	step = 1.0 * tex_height / data->cast.line_height;
	tex_pos = (ray.y_start - data->cast.height / 2 + data->cast.line_height / 2) * step;
	y = ray.y_start;
	while (y < ray.y_end)
	{
		tex_y = (int)tex_pos & (tex_height - 1);
		tex_pos += step;
		colour = data->textures[tex_index].addr[tex_width * tex_y + tex_x];
		img_pix_put(&data->img, ray.x, y, colour);
		y++;
	}
	return (0);
}

static int raycaster(t_data *data)
{
	t_cast *cast;
	int x = 0;

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

static int render_view(t_data *data)
{
	int win_x;
	int win_y;

	if (data->win_ptr == NULL)
		return (1);
	win_x = data->desc->x_res;
	win_y = data->desc->y_res;
	render_rect(&data->img, (t_rect){0, win_y * 0.5, win_x, win_y / 2, data->desc->floor_c}); //data->description.res
	render_rect(&data->img, (t_rect){0, 0, win_x, win_y / 2, data->desc->ceiling_c}); //data->description.res
	raycaster(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int cub_engine(t_des *description)
{
	t_data data;
	int win_x;
	int win_y;

	win_x = description->x_res;
	win_y = description->y_res;
	data.desc = description;
	data.mlx_ptr = mlx_init(); //protect this form being NULL
	data.win_ptr = mlx_new_window(data.mlx_ptr, win_x, win_y, "Jules' Cub3D");//protect this form being NULL
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, win_x, win_y);//protect this form being NULL
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);//protect this form being NULL
	data.textures[0].img.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, data.desc->no_path, &data.textures[0].width, &data.textures[0].height);//protect this form being NULL
	data.textures[0].addr = (int *)mlx_get_data_addr(data.textures[0].img.mlx_img, &data.textures[0].img.bpp, &data.textures[0].img.line_len, &data.textures[0].img.endian);//protect this form being NULL
	data.textures[1].img.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, data.desc->ea_path, &data.textures[1].width, &data.textures[1].height);//protect this form being NULL
	data.textures[1].addr = (int *)mlx_get_data_addr(data.textures[1].img.mlx_img, &data.textures[1].img.bpp, &data.textures[1].img.line_len, &data.textures[1].img.endian);//protect this form being NULL
	data.textures[2].img.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, data.desc->so_path, &data.textures[2].width, &data.textures[2].height);//protect this form being NULL
	data.textures[2].addr = (int *)mlx_get_data_addr(data.textures[2].img.mlx_img, &data.textures[2].img.bpp, &data.textures[2].img.line_len, &data.textures[2].img.endian);//protect this form being NULL
	data.textures[3].img.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, data.desc->we_path, &data.textures[3].width, &data.textures[3].height);//protect this form being NULL
	data.textures[3].addr = (int *)mlx_get_data_addr(data.textures[3].img.mlx_img, &data.textures[3].img.bpp, &data.textures[3].img.line_len, &data.textures[3].img.endian);//protect this form being NULL
	init_raycaster(&data.cast, description);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop_hook(data.mlx_ptr, &render_view, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
