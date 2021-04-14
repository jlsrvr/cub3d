/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 09:16:03 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/14 10:24:14 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_description(t_des *description)
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

int main(int ac, char **av)
{
	t_des *ptn_description;
	int ret;
	int fd;

	ret = 0;
	if (ac == 1)
	{
		printf(RED"Error\n"RESET"A path to a scene description must be given!");
		return (1);
	}
	if (path_checker(av[1], ".cub"))
	{
		printf(RED"Error\n"RESET"%s : invalid", av[1]);
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (cub_parser(fd, &ptn_description))
	{
		printf(RED"Error\n"RESET"There is a problem with the scene given at %s", av[1]);
		close(fd);
		free_description(ptn_description);
		return (1);
	}
	if (cub_validator(ptn_description))
	{
		close(fd);
		free_description(ptn_description);
		return (1);
	}
	return (0);
}
