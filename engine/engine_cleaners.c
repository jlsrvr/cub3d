/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_cleaners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:10:52 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/23 10:10:55 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static void	destroy_mlx_image(void **ptr_to_ptr, void *mlx_ptr)
{
	if (!(*ptr_to_ptr))
		return ;
	mlx_destroy_image(mlx_ptr, *ptr_to_ptr);
}

int			destroy_mlx_resources(t_data *data)
{
	destroy_mlx_image((void **)&data->img.mlx_img, data->mlx_ptr);
	destroy_mlx_image((void **)&data->textures[0].img.mlx_img, data->mlx_ptr);
	destroy_mlx_image((void **)&data->textures[1].img.mlx_img, data->mlx_ptr);
	destroy_mlx_image((void **)&data->textures[2].img.mlx_img, data->mlx_ptr);
	destroy_mlx_image((void **)&data->textures[3].img.mlx_img, data->mlx_ptr);
	destroy_mlx_image((void **)&data->textures[4].img.mlx_img, data->mlx_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->wall_dist)
		free(data->wall_dist);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (1);
}

int			exit_game(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (1);
}
