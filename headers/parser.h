/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:35:09 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/08 13:03:56 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PARSER_H
# define _PARSER_H
# include "cub3d.h"

void	skip_space(char **line);
int		count_words(char **words);
int		parse_number(char *number);


int		colour_parser(char **line, t_des *description);
int		texture_parser(char **line, t_des *description);
int		resolution_parser(char **line, t_des *description);
#endif
