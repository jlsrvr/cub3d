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

#include <X11/X.h>
#include <X11/keysym.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;

}	t_data;

int handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	}
	else if (keysym == XK_w)
	{
		printf("Keypress 'w' (forward)\n");
	}
	else if (keysym == XK_a)
	{
		printf("Keypress 'a' (rotate left)\n");
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

int handle_no_event(void *data)
{
	(void)data;
	return (0);
}

int main(void)
{
	t_data data;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1200, 1060, "I Have keys");

	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);

}
