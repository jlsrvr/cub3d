///HEaders///
//

#include "engine.h"

static double set_delta_dist(double ray_dir, double ray_dir_other)
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

void init_raycaster(t_cast *cast, t_des *desc)
{
	cast->width = desc->x_res;
	cast->height = desc->y_res;
	cast->pos_x = desc->pos_x;
	cast->pos_y = desc->pos_y;
	cast->dir_x = desc->dir_x;
	cast->dir_y = desc->dir_y;
	cast->plane_x = cast->dir_y * 0.66;
	cast->plane_y = cast->dir_x * -0.66;
}

void init_raycaster_loop(t_cast *cast, int x, int w)
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
