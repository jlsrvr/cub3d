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

static int	free_description(t_des *description)
{
	int	index;

	if (!description)
		return (1);
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
	free(description->sprites);
	free(description);
	return (1);
}

static int	pre_game_checks(int ac, char **av, int *fd, t_des **ptn_description)
{
	if (path_checker(av[1], ".cub"))
	{
		printf(RED"Error\n"RESET"%s : invalid\n", av[1]);
		return (1);
	}
	*fd = open(av[1], O_RDONLY);
	if (cub_parser(*fd, ptn_description))
	{
		printf(RED"Error\n"RESET);
		printf("There is a problem with the scene given at %s\n", av[1]);
		return (1);
	}
	else if (cub_validator(*ptn_description))
		return (1);
	(*ptn_description)->save = 0;
	if (ac == 3 && (ft_strncmp(av[2], "--save", 6) || ft_strlen(av[2]) != 6))
	{
		printf(RED"Error\n"RESET);
		printf("The second option should be --save not %s\n", av[2]);
		return (1);
	}
	else if (ac == 3)
		(*ptn_description)->save = 1;
	return (0);
}

int			main(int ac, char **av)
{
	t_des	*ptn_description;
	int		ret;
	int		fd;

	ptn_description = NULL;
	ret = 0;
	if (ac == 1 || ac > 3)
	{
		printf(RED"Error\n"RESET);
		printf("There must at least be a path and no more than 2 arguments\n");
		return (1);
	}
	if (pre_game_checks(ac, av, &fd, &ptn_description))
	{
		close(fd);
		return (free_description(ptn_description));
	}
	close(fd);
	ret = cub_engine(ptn_description);
	if (ret && ptn_description->save != 2)
		printf(RED"Error\n"RESET"Something went wrong in game build!\n");
	free_description(ptn_description);
	return (ret);
}
