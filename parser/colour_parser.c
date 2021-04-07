/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:58:41 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/08 11:01:54 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int **build_dest(t_des *description)
{
	int **dest;

	dest = malloc(sizeof(int*) * 5);
	if (!dest)
		return (NULL);
	dest[0] = &(description->floor_c);
	dest[1] = &(description->ceiling_c);
	return (dest);
}

static int	count_words(char **words)
{
	int count;

	count = 0;
	while(words[count])
		count++;
	return (count);
}

static int	parse_number(char *number)
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

static int	hex_conversion(char **numbers)
{
	int index;
	int rgb[3] = {0, 0, 0};
	int hex;

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

int	colour_parser(char **line, t_des *description)
{
	int index;
	int **dest;
	char **numbers;
	char *identifiers;

	identifiers = "FC";
	dest = build_dest(description);
	if (!dest)
		return (1);
	index = -1;
	while (++index < 2)
	{
		if (!ft_strncmp(*line, &identifiers[index], 1))
			break ;
	}
	(*line)++;
	numbers = ft_split(*line, ',');
	if (count_words(numbers) == 3)
		*(dest[index]) = hex_conversion(numbers);
	else
		*(dest[index]) = -1;
	if (*(dest[index]) == -1)
	{
		free(dest);
		return (1);
	}
	free(dest);
	return (0);
}
