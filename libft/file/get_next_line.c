/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:55:07 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/15 15:00:09 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

static char	*add_to_line(char **line, char add)
{
	char	*temp;
	int		index;

	index = 0;
	temp = malloc(sizeof(*temp) * (ft_strlen(*line) + 2));
	if (!temp)
	{
		free(*line);
		*line = NULL;
		return (NULL);
	}
	while ((*line)[index])
	{
		temp[index] = (*line)[index];
		index++;
	}
	temp[index++] = add;
	temp[index] = 0;
	free(*line);
	*line = temp;
	return (*line);
}

static int	clean_return(int result, char **line)
{
	if (result == 0 && ft_strlen(*line) == 0)
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		buff[2];
	char		*empty;
	int			index;
	int			result;

	if (!line)
		return (-1);
	*line = malloc(sizeof(**line) * 2);
	if (read(fd, buff, 0) == -1 || fd < 0 || !(*line))
		return (-1);
	empty = "";
	index = 0;
	(*line)[index] = empty[index];
	(*line)[1] = 0;
	result = read(fd, buff, 1);
	while (result > 0 && buff[0] != '\n')
	{
		buff[1] = 0;
		if (!add_to_line(line, buff[0]))
			return (-1);
		result = read(fd, buff, 1);
	}
	return (clean_return(result, line));
}
