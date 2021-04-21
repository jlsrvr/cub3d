//////HEADER?????//
//
//

#include "engine.h"

#define RED_PIXEL 0xFF0000
#define WIN_X 1200
#define WIN_Y 800

int handle_keyrelease(int keysym, void *data)
{
	(void)data;
	if (keysym == KEY_W)
	{
		printf("Key release 'w' (forward)\n");
	}
	else if (keysym == KEY_A)
	{
		printf("Key release 'a' (rotate left)\n");
	}
	else if (keysym == KEY_S)
	{
		printf("Key release 's' (backward)\n");
	}
	else if (keysym == KEY_D)
	{
		printf("Key release 'd' (rotate right)\n");
	}
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
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

int render_rect(t_img *img, t_rect rect)
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
	return (0);
}

int render_ray(t_img *img, t_ray ray)
{
	int y;

	y = ray.y_start;
	while (y < ray.y_end)
	{
		img_pix_put(img, ray.x, y, ray.color);
		y++;
	}
	return (0);
}

double set_delta_dist(double ray_dir, double ray_dir_other)
{
	double delta_dist;

	delta_dist = 0;
	if (ray_dir_other != 0)
	{
		delta_dist = 1;
		if (ray_dir != 0)
			delta_dist = fabs(1 / ray_dir);
	}
	return (delta_dist);
}

static void init_raycaster(t_cast *cast, t_des *desc)
{
	cast->width = WIN_X;// = description->player_resolution
	cast->height = WIN_Y;// = description->player_resolution
	cast->pos_x = desc->pos_x;
	cast->pos_y = desc->pos_y;
	cast->dir_x = desc->dir_x;
	cast->dir_y = desc->dir_y;
	cast->plane_x = cast->dir_y * 0.66;
	cast->plane_y = cast->dir_x * -0.66;
}

static void calculate_step(int *step, double ray_dir)
{
	int ret;

	ret = 1;
	if (ray_dir < 0)
		ret = -1;
	*step = ret;
}

static void calculate_side_dist(t_cast *cast)
{
	if (cast->ray_dir_x < 0)
		cast->side_dist_x = (cast->pos_x - cast->map_x) * cast->delta_dist_x;
	else
		cast->side_dist_x = (cast->map_x + 1.0 - cast->pos_x) * cast->delta_dist_x;
	if (cast->ray_dir_y < 0)
		cast->side_dist_y = (cast->pos_y - cast->map_y) * cast->delta_dist_y;
	else
		cast->side_dist_y = (cast->map_y + 1.0 - cast->pos_y) * cast->delta_dist_y;
}

static void init_raycaster_loop(t_cast *cast, int x, int w)
{
	cast->camera_x = 2 * x / (double)w - 1;
	cast->ray_dir_x = cast->dir_x + (cast->plane_x * cast->camera_x);
	cast->ray_dir_y= cast->dir_y + (cast->plane_y * cast->camera_x);
	cast->map_x = (int)cast->pos_x;
	cast->map_y = (int)cast->pos_y;
	cast->delta_dist_x = set_delta_dist(cast->ray_dir_x, cast->ray_dir_y);
	cast->delta_dist_y = set_delta_dist(cast->ray_dir_y, cast->ray_dir_x);
	cast->hit = 0;
	calculate_step(&cast->step_x, cast->ray_dir_x);
	calculate_step(&cast->step_y, cast->ray_dir_y);
	calculate_side_dist(cast);
}

static void cast_ray(t_cast *cast, t_des *desc)
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
		if (desc->map[cast->map_x][cast->map_y] > '0')/// Worth trying with == '1'
			cast->hit = 1;
	}
}

static void calculate_distance_to_wall(t_cast *cast)
{
		if (cast->side == 0)
			cast->perp_wall_dist = (cast->map_x - cast->pos_x + (1 - cast->step_x) / 2) / cast->ray_dir_x;
		else
			cast->perp_wall_dist = (cast->map_y - cast->pos_y + (1 - cast->step_y) / 2) / cast->ray_dir_y;
}

static void def_line_start_end(t_cast *cast)
{
		cast->draw_start = -cast->line_height / 2 + cast->height / 2;
		if (cast->draw_start < 0)
			cast->draw_start = 0;
		cast->draw_end = cast->line_height / 2 + cast->height / 2;
		if (cast->draw_end >= cast->height)
			cast->draw_end = cast->height - 1;
}

static int raycaster(t_data *data)
{
	t_cast cast;
	int x = 0;

	cast = data->cast;
	while (x < cast.width)
	{
		init_raycaster_loop(&cast, x, cast.width);
		cast_ray(&cast, data->desc);
		calculate_distance_to_wall(&cast);
		cast.line_height = (int)(cast.height / cast.perp_wall_dist);
		def_line_start_end(&cast);
		cast.colour = RED_PIXEL;
		if (cast.side == 1)
		{
			cast.colour = 0x920000;
		}
		render_ray(&data->img, (t_ray){x, cast.draw_start, cast.draw_end, cast.colour});
		x++;
	}
	return (0);
}

static int render_map(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_rect(&data->img, (t_rect){0, WIN_Y * 0.5, WIN_X, WIN_Y / 2, data->desc->floor_c}); //data->description.res
	render_rect(&data->img, (t_rect){0, 0, WIN_X, WIN_Y / 2, data->desc->ceiling_c}); //data->description.res
	raycaster(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int cub_engine(t_des *description)
{
	t_data data;

	data.desc = description;
	data.mlx_ptr = mlx_init(); //protect this form being NULL
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_X, WIN_Y, "Jules' Cub3D");
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_X, WIN_Y);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	init_raycaster(&data.cast, description);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop_hook(data.mlx_ptr, &render_map, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
