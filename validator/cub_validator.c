/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:19:26 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/14 10:06:39 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

int	cub_validator(t_des *description)
{
	if (textures_validator(description))
	{
		printf(RED"Error\n"RESET);
		printf("At least one of the texture paths is invalid\n");
		return (1);
	}
	if (map_validator(description))
	{
		printf(RED"Error\n"RESET);
		printf("The map is invalid\n");
		return (1);
	}
	return (0);
}
