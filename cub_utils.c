/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:03:56 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/13 15:06:33 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	path_checker(char *path, char *extension)
{
	int fd;
	int pos_ext;

	fd = open(path, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	pos_ext = ft_strlen(path) - ft_strlen(extension);
	if (ft_strncmp(&(path[pos_ext]), extension, ft_strlen(extension)))
		return (1);
	return (0);
}

