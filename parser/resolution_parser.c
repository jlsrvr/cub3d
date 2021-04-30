/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:58:41 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/16 15:30:01 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	clean_return(t_des *des, char **numbers, int x_res, int y_res)
{
	int	num_index;
	int	ret;

	ret = 0;
	des->x_res = x_res;
	des->y_res = y_res;
	if (x_res == -1 || y_res == -1)
		ret = 1;
	if (numbers)
	{
		num_index = -1;
		while (numbers[++num_index])
			free(numbers[num_index]);
		free(numbers);
	}
	return (ret);
}

static int	check_split(char **numbers, int *first_index, int *last_index)
{
	int	num_i;
	int	let_i;
	int	num_cnt;

	num_i = -1;
	num_cnt = 0;
	while (numbers[++num_i] && num_cnt < 3)
	{
		let_i = -1;
		while (numbers[num_i][++let_i])
		{
			if (ft_isdigit(numbers[num_i][let_i]))
			{
				if (num_cnt++ == 0)
					*first_index = num_i;
				*last_index = num_i;
				break ;
			}
			if (!ft_isspace(numbers[num_i][let_i]))
				return (1);
		}
	}
	if (num_cnt < 2 || num_cnt > 2 || numbers[(*last_index) + 1])
		return (1);
	return (0);
}

int			resolution_parser(char **line, t_des *description)
{
	int		first_int;
	int		sec_int;
	char	**numbers;

	if (description->x_res != 0 || description->y_res != 0)
		return (clean_return(description, NULL, -1, -1));
	(*line)++;
	first_int = 0;
	sec_int = 0;
	numbers = ft_split(*line, ' ');
	if (check_split(numbers, &first_int, &sec_int))
		return (clean_return(description, numbers, -1, -1));
	first_int = parse_number(numbers[first_int]);
	sec_int = parse_number(numbers[sec_int]);
	if (first_int <= 0 || sec_int <= 0)
		return (clean_return(description, numbers, -1, -1));
	return (clean_return(description, numbers, first_int, sec_int));
}
