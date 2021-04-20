//////HEADER///
//


#include "engine.h"

int handle_keypress(int keysym, t_data *data)
{
	double rot_speed = 0.3;
	double move_speed = 0.5;
	char **world_map = data->desc->map;
	if (keysym == KEY_ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	else if (keysym == KEY_W)
	{
		printf("Keypress 'w' (forward)\n");
		int next_x = (int)(data->cast.pos_x + data->cast.dir_x * move_speed);
		int next_y = (int)(data->cast.pos_y + data->cast.dir_y * move_speed);
		if (world_map[next_x][(int)(data->cast.pos_y)] == (int)'0')
			data->cast.pos_x = next_x;
		if (world_map[(int)(data->cast.pos_x)][next_y] == (int)'0')
			data->cast.pos_y = next_y;
	}
	else if (keysym == KEY_S)
	{
		printf("Keypress 's' (backward)\n");
		int next_x = (int)(data->cast.pos_x - data->cast.dir_x * move_speed);
		int next_y = (int)(data->cast.pos_y - data->cast.dir_y * move_speed);
		if (world_map[next_x][(int)(data->cast.pos_y)] == (int)'0')
			data->cast.pos_x = next_x;
		if (world_map[(int)(data->cast.pos_x)][next_y] == (int)'0')
			data->cast.pos_y = next_y;
	}
	else if (keysym == KEY_A)
	{
		printf("Keypress 'a' (left)\n");
		int next_x = (int)(data->cast.pos_x - data->cast.dir_y * move_speed);
		int next_y = (int)(data->cast.pos_y + data->cast.dir_x * move_speed);
		if (world_map[next_x][(int)(data->cast.pos_y)] == (int)'0')
			data->cast.pos_x = next_x;
		if (world_map[(int)(data->cast.pos_x)][next_y] == (int)'0')
			data->cast.pos_y = next_y;
	}
	else if (keysym == KEY_D)
	{
		printf("Keypress 'd' (right)\n");
		int next_x = (int)(data->cast.pos_x + data->cast.dir_y * move_speed);
		int next_y = (int)(data->cast.pos_y - data->cast.dir_x * move_speed);
		if (world_map[next_x][(int)(data->cast.pos_y)] == (int)'0')
			data->cast.pos_x = next_x;
		if (world_map[(int)(data->cast.pos_x)][next_y] == (int)'0')
			data->cast.pos_y = next_y;
	}
	else if (keysym == LEFT_ARROW)
	{
		printf("Keypress 'a' (rotate left)\n");
		double old_dir_x = data->cast.dir_x;
		data->cast.dir_x = data->cast.dir_x * cos(rot_speed) - data->cast.dir_y * sin(rot_speed);
		data->cast.dir_y = old_dir_x * sin(rot_speed) + data->cast.dir_y * cos(rot_speed);
		double old_plane_x = data->cast.plane_x;
		data->cast.plane_x = data->cast.plane_x * cos(rot_speed) - data->cast.plane_y * sin(rot_speed);
		data->cast.plane_y = old_plane_x * sin(rot_speed) + data->cast.plane_y * cos(rot_speed);
	}
	else if (keysym == RIGHT_ARROW)
	{
		printf("Keypress 'd' (rotate right)\n");
		double old_dir_x = data->cast.dir_x;
		data->cast.dir_x = data->cast.dir_x * cos(-rot_speed) - data->cast.dir_y * sin(-rot_speed);
		data->cast.dir_y = old_dir_x * sin(-rot_speed) + data->cast.dir_y * cos(-rot_speed);
		double old_plane_x = data->cast.plane_x;
		data->cast.plane_x = data->cast.plane_x * cos(-rot_speed) - data->cast.plane_y * sin(-rot_speed);
		data->cast.plane_y = old_plane_x * sin(-rot_speed) + data->cast.plane_y * cos(-rot_speed);
	}
	return (0);
}
