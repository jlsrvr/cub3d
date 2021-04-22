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

void render_ray(t_data *data, t_ray ray)
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
}
