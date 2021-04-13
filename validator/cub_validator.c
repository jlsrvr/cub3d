/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:19:26 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/13 17:24:01 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

int	cub_validator(t_des *description)
{
	if (textures_validator(description) || map_validator(&(description->map)))
			return (1);
	return (0);
}
