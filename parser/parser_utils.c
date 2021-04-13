/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:50:52 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/13 17:09:15 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_space(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
}

int		count_words(char **words)
{
	int count;

	count = 0;
	while (words[count])
		count++;
	return (count);
}

int		parse_number(char *number)
{
	int num;
	int digit;

	num = 0;
	digit = 0;
	while (number[num])
	{
		if (!ft_isspace(number[num]) && !ft_isdigit(number[num]))
			return (-1);
		if (ft_isdigit(number[num]))
			digit = 1;
		if (ft_isspace(number[num]) && digit == 1)
			return (-1);
		num++;
	}
	num = ft_atoi(number);
	if (!digit)
		return (-1);
	return (num);
}

int	init_description(t_des **to_fill)
{
	*to_fill = malloc(sizeof(**to_fill));
	if (!*to_fill)
		return (1);
	(*to_fill)->x_res = 0;
	(*to_fill)->y_res = 0;
	(*to_fill)->no_path = NULL;
	(*to_fill)->ea_path = NULL;
	(*to_fill)->so_path = NULL;
	(*to_fill)->we_path = NULL;
	(*to_fill)->s_path = NULL;
	(*to_fill)->floor_c = -2;
	(*to_fill)->ceiling_c = -2;
	(*to_fill)->map = NULL;
	return (0);
}

int	validate_map_line(char *line, t_des *to_fill)
{
	int index;
	int filled;

	index = -1;
	filled = 0;
	while (line[++index])
		if (ft_isalnum(line[index]))
			filled = 1;
	if (to_fill->map && filled == 0)
		return (1);
	if (filled == 0)
		return (2);
	return (0);
}
