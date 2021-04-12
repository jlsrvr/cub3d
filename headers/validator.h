/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:35:09 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/12 21:20:31 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VALIDATOR_H
# define _VALIDATOR_H
# include "cub3d.h"

int		map_validator(char ***map);
int		textures_validator(t_des *description);
#endif
