/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:35:09 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/16 15:23:55 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATOR_H
# define VALIDATOR_H
# include "cub3d.h"

int		replace_spaces(t_des *desc);

int		map_validator(t_des *description);
int		textures_validator(t_des *description);
#endif
