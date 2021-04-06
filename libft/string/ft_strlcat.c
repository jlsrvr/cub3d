/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:56:10 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/01 14:01:09 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	index;

	lendst = (ft_strlen((char *)dst));
	lensrc = (ft_strlen((char *)src));
	index = 0;
	if (lendst >= dstsize)
		return (dstsize + lensrc);
	while ((lendst + index) < dstsize - 1 && src[index])
	{
		dst[(lendst + index)] = src[index];
		++index;
	}
	dst[(lendst + index)] = '\0';
	return (lendst + lensrc);
}
