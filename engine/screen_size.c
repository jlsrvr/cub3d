/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:53:54 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/26 09:53:57 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	set_screen_resolution(void *mlx_ptr, int *x_res, int *y_res)
{
	int max_x;
	int max_y;

	mlx_get_screen_size(mlx_ptr, &max_x, &max_y);
	if (*x_res > max_x)
		*x_res = max_x;
	if (*y_res > max_y)
		*y_res = max_y;
}
