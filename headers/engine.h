/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:35:09 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/16 15:23:34 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# include "cub3d.h"
# include <math.h>

typedef struct	s_sprite_vars
{
	double	sprite_x;
	double	sprite_y;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;

}				t_sprite_vars;

typedef struct	s_transfer
{
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_x;

}				t_transfer;

typedef struct	s_ray
{
	int x;
	int y_start;
	int y_end;
}				t_ray;

typedef struct	s_cast
{
	int		width;
	int		height;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		colour;
}				t_cast;

typedef struct	s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;

}				t_rect;

typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct	s_texture
{
	t_img	img;
	int		*addr;
	int		width;
	int		height;
}				t_texture;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_cast		cast;
	t_img		img;
	t_des		*desc;
	t_texture	textures[5];
	double		*wall_dist;
}				t_data;

int				add_sprites(t_data *data);
int				destroy_mlx_resources(t_data *data);
int				exit_game(t_data *data);
int				handle_keypress(int keysym, t_data *data);
int				init_sprite_order(t_data *data, int **sprite_order,
									double **sprite_dist);
int				save_image(t_data *data);
void			calculate_distance_to_wall(t_cast *cast);
void			cast_ray(t_cast *cast, t_des *desc);
void			define_line_start_end(t_cast *cast);
void			img_pix_put(t_img *img, int x, int y, int color);
void			init_raycaster(t_cast *cast, t_des *desc);
void			init_raycaster_loop(t_cast *cast, int x, int w);
void			render_ray(t_data *data, t_ray ray);
void			render_rect(t_img *img, t_rect rect);
void			set_screen_resolution(void *mlx_ptr, int *x_res, int *y_res);
#endif
