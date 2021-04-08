/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:58:41 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/08 12:29:38 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	hex_conversion(char **numbers)
{
	int index;
	int rgb[3];
	int hex;

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	hex = 0;
	index = -1;
	while (++index < 3 && numbers[index])
	{
		rgb[index] = parse_number(numbers[index]);
		if (rgb[index] < 0 || rgb[index] > 255)
			return (-1);
	}
	hex |= rgb[2];
	hex |= rgb[1] << 8;
	hex |= rgb[0] << 16;
	return (hex);
}

static int	clean_return(int index, char **numbers)
{
	int num_index;

	num_index = -1;
	while (numbers[++num_index])
		free(numbers[num_index]);
	free(numbers);
	if (*(dest[index]) == -1)
	{
		free(dest);
		return (1);
	}
	return (0);
}

int			resolution_parser(char **line, t_des *description)
{
	int		index;
	int		**dest;
	char	**numbers;
	char	*identifiers;

	if (!dest)
		return (1);
	index = -1;
	while (++index < 2)
		if (!ft_strncmp(*line, &identifiers[index], 1))
			break ;
	(*line)++;
	numbers = ft_split(*line, ',');
	if (count_words(numbers) == 3)
		*(dest[index]) = hex_conversion(numbers);
	else
		*(dest[index]) = -1;
	return (clean_return(dest, index, numbers));
}
