/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:50:02 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/08 18:03:06 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUBD3D_H
# define _CUBD3D_H
# include "../libft/headers/libft.h"
typedef struct s_description
{
	int x_res;
	int y_res;
	char *no_path;
	char *ea_path;
	char *so_path;
	char *we_path;
	char *s_path;
	int floor_c;
	int ceiling_c;
	char **map;
}	t_des;

int	cub_parser(int fd, t_des **to_fill);
#endif
