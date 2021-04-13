/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:33:16 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/13 12:34:01 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void	replace_spaces(char ***map_in)
{
	char	**map;
	int		x_index;
	int		y_index;

	map = *map_in;
	y_index = -1;
	while (map[++y_index])
	{
		x_index = -1;
		while (map[y_index][++x_index])
			if (ft_isspace(map[y_index][x_index]))
				map[y_index][x_index] = '1';
	}
}
