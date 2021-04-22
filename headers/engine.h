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
# include <X11/X.h>
# include <math.h>

# define KEY_A 0x0061
# define KEY_D 0x0064
# define KEY_S 0x0073
# define KEY_W 0x0077
# define KEY_ESC 0xff1b
# define LEFT_ARROW 0xff51
# define RIGHT_ARROW 0xff53

typedef struct s_ray
{
        int x;
        int y_start;
        int y_end;
}       t_ray;

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
        int     x;
        int     y;
        int width;
        int height;
        int color;

}       t_rect;

typedef struct s_img
{
        void    *mlx_img;
        char    *addr;
        int             bpp;
        int             line_len;
        int             endian;
}       t_img;

typedef struct s_texture
{
	t_img img;
	int *addr;
	int width;
	int height;
} t_texture;

typedef struct s_data
{
        void    *mlx_ptr;
        void    *win_ptr;
        t_cast  cast;
        t_img   img;
        t_des 	*desc;
		t_texture textures[5];

}       t_data;

void	img_pix_put(t_img *img, int x, int y, int color);
void render_rect(t_img *img, t_rect rect);
void init_raycaster(t_cast *cast, t_des *desc);
void init_raycaster_loop(t_cast *cast, int x, int w);
void cast_ray(t_cast *cast, t_des *desc);
void calculate_distance_to_wall(t_cast *cast);
void define_line_start_end(t_cast *cast);
void render_ray(t_data *data, t_ray ray);
int	handle_keypress(int keysym, t_data *data);
#endif
