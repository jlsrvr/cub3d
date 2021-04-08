/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:50:52 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/08 11:13:32 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_space(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
}

int	count_words(char **words)
{
	int count;

	count = 0;
	while(words[count])
		count++;
	return (count);
}

int	parse_number(char *number)
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
