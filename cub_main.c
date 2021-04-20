/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 09:16:03 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/16 15:42:43 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


char world_map[10][10] =
{
	"1111111111",
	"1000000001",
	"1000000011",
	"1000000001",
	"1000000001",
	"1000000001",
	"1000000001",
	"1000000001",
	"1000000001",
	"1111111111"
};

#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#define RED_PIXEL 0xFF0000
#define WIN_X 1200
#define WIN_Y 800

typedef struct s_ray
{
	int	x;
	int y_start;
	int y_end;
	int color;

}	t_ray;

typedef struct s_cast
{
	int width;
	int height;
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double  delta_dist_x;
	double  delta_dist_y;
	double perp_wall_dist;
	int step_x;
	int step_y;
	int hit;
	int side;
	int line_height;
	int draw_start;
	int draw_end;
	int colour;

}	t_cast;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;

}	t_rect;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_cast 	cast;
	t_img	img;
	//t_des	*description;

}	t_data;


int handle_keyrelease(int keysym, void *data)
{
	(void)data;
	if (keysym == XK_w)
	{
		printf("Key release 'w' (forward)\n");
	}
	else if (keysym == XK_a)
	{
		printf("Key release 'a' (rotate left)\n");
	}
	else if (keysym == XK_s)
	{
		printf("Key release 's' (backward)\n");
	}
	else if (keysym == XK_d)
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
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
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

static void init_raycaster(t_cast *cast)
{
	cast->width = WIN_X;// = description->player_resolution
	cast->height = WIN_Y;// = description->player_resolution
	cast->pos_x = 5; // = description->player_pos_x
	cast->pos_y = 5; // = description->player_pos_y
	cast->dir_x = 0; // -1 west, 1 east = description->player_dir_y
	cast->dir_y = 1; // -1 south, 1 north = description->player_dir_y
	cast->plane_x = 0.66;
	cast->plane_y = 0;
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

static void cast_ray(t_cast *cast)
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
		if (world_map[cast->map_x][cast->map_y] > '0')
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

static int raycaster(t_cast cast, t_img *img)
{
	int x = 0;

	while (x < cast.width)
	{
		init_raycaster_loop(&cast, x, cast.width);
		cast_ray(&cast);
		calculate_distance_to_wall(&cast);
		cast.line_height = (int)(cast.height / cast.perp_wall_dist);
		def_line_start_end(&cast);
		cast.colour = RED_PIXEL;
		if (cast.side == 1)
		{
			cast.colour = 0x920000;
		}
		render_ray(img, (t_ray){x, cast.draw_start, cast.draw_end, cast.colour});
		x++;
	}
	return (0);
}

int render_map(t_data *data)
{

	if (data->win_ptr == NULL)
		return (1);
	render_rect(&data->img, (t_rect){0, WIN_Y * 0.5, WIN_X, WIN_Y / 2, 0x00FF00}); //floor data->description->floor_c
	render_rect(&data->img, (t_rect){0, 0, WIN_X, WIN_Y / 2, 0x00FFFF}); //ceiling
	raycaster(data->cast, &data->img);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	else if (keysym == XK_w)
	{
		printf("Keypress 'w' (forward)\n");
	}
	else if (keysym == XK_a)
	{
		printf("Keypress 'a' (rotate left)\n");
		double rot_speed = 3;
		double old_dir_x = data->cast.dir_x;
		data->cast.dir_x = data->cast.dir_x * cos(-rot_speed) - data->cast.dir_y * sin(-rot_speed);
		data->cast.dir_y = old_dir_x * sin(-rot_speed) + data->cast.dir_y * cos(-rot_speed);
		double old_plane_x = data->cast.plane_x;
		data->cast.plane_x = data->cast.plane_x * cos(-rot_speed) - data->cast.plane_y * sin(-rot_speed);
		data->cast.plane_y = old_plane_x * sin(-rot_speed) + data->cast.plane_y * cos(-rot_speed);
		render_map(data);
	}
	else if (keysym == XK_s)
	{
		printf("Keypress 's' (backward)\n");
	}
	else if (keysym == XK_d)
	{
		printf("Keypress 'd' (rotate right)\n");
	}
	return (0);
}

int main(void)
{
	t_data data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_X, WIN_Y, "Jules' Cub3D");
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_X, WIN_Y);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	init_raycaster(&data.cast);
	mlx_loop_hook(data.mlx_ptr, &render_map, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}

/*static void	free_description(t_des *description)
  {
  int	index;

  if (!description)
  return ;
  free(description->no_path);
  free(description->ea_path);
  free(description->so_path);
  free(description->we_path);
  free(description->s_path);
  if (description->map)
  {
  index = -1;
  while (description->map[++index])
  free(description->map[index]);
  free(description->map);
  }
  }

  static int	pre_game_checks(char **av, int *fd, t_des *ptn_description)
  {
  if (path_checker(av[1], ".cub"))
  {
  printf(RED"Error\n"RESET"%s : invalid", av[1]);
  return (1);
  }
 *fd = open(av[1], O_RDONLY);
 if (cub_parser(*fd, &ptn_description))
 {
 printf(RED"Error\n"RESET);
 printf("There is a problem with the scene given at %s", av[1]);
 return (1);
 }
 else if (cub_validator(ptn_description))
 return (1);
 return (0);
 }

 int	main(int ac, char **av)
 {
 t_des	*ptn_description;
 int		ret;
 int		fd;

 ptn_description = NULL;
 ret = 0;
 if (ac == 1)
 {
 printf(RED"Error\n"RESET"A path to a scene description must be given!");
 return (1);
 }
 ret = pre_game_checks(av, &fd, ptn_description);
 close(fd);
 free_description(ptn_description);
 return (ret);
 }*/
