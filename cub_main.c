/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 09:16:03 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/15 20:59:52 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_description(t_des *description)
{
	int index;

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

int			main(int ac, char **av)
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
}
