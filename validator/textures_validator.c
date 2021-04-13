/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:11:10 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/13 15:02:12 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

static int	path_checker(char *path, char *extension)
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

int	textures_validator(t_des *description)
{
	int		index;
	char	*ext;
	char	*paths[5];

	index = -1;
	paths[0] = description->no_path;
	paths[1] = description->ea_path;
	paths[2] = description->so_path;
	paths[3] = description->we_path;
	paths[4] = description->s_path;
	ext = ".xpm";
	while (++index < 5)
		if (path_checker(paths[index], ext))
			return (1);
	return (0);
}
