//////HEADER///
//


#include "engine.h"

static void rotate_player(char dir, t_cast *cast)
{
	double old_dir_x;
	double old_plane_x;
	double rot_speed;

	old_dir_x = cast->dir_x;
	old_plane_x = cast->plane_x;
	rot_speed = 0.3;
	if (dir == 'R')
		rot_speed *= -1;
	cast->dir_x = cast->dir_x * cos(rot_speed) - cast->dir_y * sin(rot_speed);
	cast->dir_y = old_dir_x * sin(rot_speed) + cast->dir_y * cos(rot_speed);
	cast->plane_x = cast->plane_x * cos(rot_speed) - cast->plane_y * sin(rot_speed);
	cast->plane_y = old_plane_x * sin(rot_speed) + cast->plane_y * cos(rot_speed);
}

int handle_keypress(int keysym, t_data *data)
{
	double move_speed = 0.5;
	char **world_map = data->desc->map;
	t_cast *cast = &data->cast;


	if (keysym == KEY_ESC)
	{
		// destroy image here??
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	else if (keysym == KEY_W)
	{
		printf("Keypress 'w' (forward)\n");
		int next_x = (int)(cast->pos_x + cast->dir_x * move_speed);
		int next_y = (int)(cast->pos_y + cast->dir_y * move_speed);
		if (world_map[next_x][(int)(cast->pos_y)] == '0')
			cast->pos_x += cast->dir_x * move_speed;
		if (world_map[(int)(cast->pos_x)][next_y] == '0')
			cast->pos_y += cast->dir_y * move_speed;
	}
	else if (keysym == KEY_S)
	{
		printf("Keypress 's' (backward)\n");
		int next_x = (int)(cast->pos_x - cast->dir_x * move_speed);
		int next_y = (int)(cast->pos_y - cast->dir_y * move_speed);
		if (world_map[next_x][(int)(cast->pos_y)] == '0')
			cast->pos_x -= cast->dir_x * move_speed;
		if (world_map[(int)(cast->pos_x)][next_y] == '0')
			cast->pos_y -= cast->dir_y * move_speed;
	}
	else if (keysym == KEY_A)
	{
		printf("Keypress 'a' (left)\n");
		int next_x = (int)(cast->pos_x - cast->dir_y * move_speed);
		int next_y = (int)(cast->pos_y + cast->dir_x * move_speed);
		if (world_map[next_x][(int)(cast->pos_y)] == '0')
			cast->pos_x -= cast->dir_y * move_speed;
		if (world_map[(int)(cast->pos_x)][next_y] == '0')
			cast->pos_y += cast->dir_x * move_speed;
	}
	else if (keysym == KEY_D)
	{
		printf("Keypress 'd' (right)\n");
		int next_x = (int)(cast->pos_x + cast->dir_y * move_speed);
		int next_y = (int)(cast->pos_y - cast->dir_x * move_speed);
		if (world_map[next_x][(int)(cast->pos_y)] == '0')
			cast->pos_x += cast->dir_y * move_speed;
		if (world_map[(int)(cast->pos_x)][next_y] == '0')
			cast->pos_y -= cast->dir_x * move_speed;
	}
	else if (keysym == LEFT_ARROW)
		rotate_player('L', cast);
	else if (keysym == RIGHT_ARROW)
		rotate_player('R', cast);
	return (0);
}
