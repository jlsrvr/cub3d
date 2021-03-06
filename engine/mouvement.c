/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:07:01 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/22 16:07:03 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#define KEY_A 0x0061
#define KEY_D 0x0064
#define KEY_S 0x0073
#define KEY_W 0x0077
#define KEY_ESC 0xff1b
#define LEFT_ARROW 0xff51
#define RIGHT_ARROW 0xff53

static void	move_forward_backward(char dir, t_cast *cast,
									char **map, double move_speed)
{
	int inverser;
	int next_x;
	int next_y;

	inverser = 1;
	if (dir == 'B')
		inverser *= -1;
	next_x = (int)(cast->pos_x + (inverser * cast->dir_x * move_speed));
	next_y = (int)(cast->pos_y + (inverser * cast->dir_y * move_speed));
	if (map[next_x][(int)(cast->pos_y)] == '0')
	{
		if (dir == 'F')
			cast->pos_x += cast->dir_x * move_speed;
		if (dir == 'B')
			cast->pos_x -= cast->dir_x * move_speed;
	}
	if (map[(int)(cast->pos_x)][next_y] == '0')
	{
		if (dir == 'F')
			cast->pos_y += cast->dir_y * move_speed;
		if (dir == 'B')
			cast->pos_y -= cast->dir_y * move_speed;
	}
}

static void	move_left_right(char dir, t_cast *cast,
								char **map, double move_speed)
{
	int inverser;
	int next_x;
	int next_y;

	inverser = 1;
	if (dir == 'R')
		inverser *= -1;
	next_x = (int)(cast->pos_x - (inverser * cast->plane_x * move_speed));
	next_y = (int)(cast->pos_y - (inverser * cast->plane_y * move_speed));
	if (map[next_x][(int)(cast->pos_y)] == '0')
	{
		if (dir == 'R')
			cast->pos_x += cast->plane_x * move_speed;
		if (dir == 'L')
			cast->pos_x -= cast->plane_x * move_speed;
	}
	if (map[(int)(cast->pos_x)][next_y] == '0')
	{
		if (dir == 'R')
			cast->pos_y += cast->plane_y * move_speed;
		if (dir == 'L')
			cast->pos_y -= cast->plane_y * move_speed;
	}
}

static void	rotate_player(char dir, t_cast *cast)
{
	double old_dir_x;
	double old_plane_x;
	double speed;

	old_dir_x = cast->dir_x;
	old_plane_x = cast->plane_x;
	speed = 0.3;
	if (dir == 'R')
		speed *= -1;
	cast->dir_x = cast->dir_x * cos(speed) - cast->dir_y * sin(speed);
	cast->dir_y = old_dir_x * sin(speed) + cast->dir_y * cos(speed);
	cast->plane_x = cast->plane_x * cos(speed) - cast->plane_y * sin(speed);
	cast->plane_y = old_plane_x * sin(speed) + cast->plane_y * cos(speed);
}

int			handle_keypress(int keysym, t_data *data)
{
	double move_speed;
	t_cast *cast;

	cast = &data->cast;
	move_speed = 0.45;
	if (keysym == KEY_ESC)
		exit_game(data);
	else if (keysym == KEY_W)
		move_forward_backward('F', cast, data->desc->map, move_speed);
	else if (keysym == KEY_S)
		move_forward_backward('B', cast, data->desc->map, move_speed);
	else if (keysym == KEY_A)
		move_left_right('L', cast, data->desc->map, move_speed);
	else if (keysym == KEY_D)
		move_left_right('R', cast, data->desc->map, move_speed);
	else if (keysym == LEFT_ARROW)
		rotate_player('L', cast);
	else if (keysym == RIGHT_ARROW)
		rotate_player('R', cast);
	return (0);
}
