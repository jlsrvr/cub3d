/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:50:02 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/14 10:21:09 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/headers/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>

# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PINK	"\e[35m"
# define CYAN	"\e[36m"
# define BOLD	"\e[1m"
# define UNDER	"\e[4m"
# define BLINK	"\e[5m"
# define RESET  "\e[0m"

typedef struct s_description
{
	int		x_res;
	int		y_res;
	char	*no_path;
	char	*ea_path;
	char	*so_path;
	char	*we_path;
	char	*s_path;
	int		floor_c;
	int		ceiling_c;
	char	**map;
}				t_des;

int				path_checker(char *path, char *extension);

int				cub_parser(int fd, t_des **to_fill);
int				cub_validator(t_des *description);
#endif
