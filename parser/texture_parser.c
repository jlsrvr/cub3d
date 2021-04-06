/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:55:11 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/07 14:20:01 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int texture_parser(char **line, t_des *description)
{
	char **to_fill;

	if (ft_strnstr(*line, "NO", 2))
	{
		(*line) += 2;
		to_fill = &(description->no_path);
	}
	else if (ft_strnstr(*line, "EA", 2))
	{
		(*line) += 2;
		to_fill = &(description->ea_path);
	}
	else if (ft_strnstr(*line, "SO", 2))
	{
		(*line) += 2;
		to_fill = &(description->so_path);
	}
	else if (ft_strnstr(*line, "WE", 2))
	{
		(*line) += 2;
		to_fill = &(description->we_path);
	}
	else if (ft_strnstr(*line, "S", 2))
	{
		(*line) += 2;
		to_fill = &(description->s_path);
	}
	while (ft_isspace(**line))
		(*line)++;
	*to_fill = ft_strdup(*line);
	return (0);
}
