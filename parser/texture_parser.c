/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:55:11 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/08 23:03:38 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	clean_return(char ***dest, int index, char **line)
{
	int		ret;
	char	*new;

	ret = 0;
	if (*(dest[index]))
	{
		ret = 1;
		free(*(dest[index]));
		new = ft_strdup("|duplicate|");
	}
	else
		new = ft_strdup(*line);
	if (!new)
		ret = 1;
	*(dest[index]) = new;
	free(dest);
	return (ret);
}

static char	***build_dest(t_des *description)
{
	char ***dest;

	dest = malloc(sizeof(char*) * 5);
	if (!dest)
		return (NULL);
	dest[0] = &(description->no_path);
	dest[1] = &(description->ea_path);
	dest[2] = &(description->so_path);
	dest[3] = &(description->we_path);
	dest[4] = &(description->s_path);
	return (dest);
}

int			texture_parser(char **line, t_des *description)
{
	int		index;
	char	***dest;
	char	*identifiers[5];

	identifiers[0] = "NO";
	identifiers[1] = "EA";
	identifiers[2] = "SO";
	identifiers[3] = "WE";
	identifiers[4] = "S";
	dest = build_dest(description);
	if (!dest)
		return (1);
	index = -1;
	while (++index < 5)
	{
		if (ft_strnstr(*line, identifiers[index], 2))
			break ;
	}
	(*line)++;
	if (index != 4)
		(*line)++;
	skip_space(line);
	return (clean_return(dest, index, line));
}
