/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:59:36 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/01 14:02:33 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	lensrc;
	size_t	index;

	if (!dst)
		return (0);
	lensrc = (size_t)ft_strlen((char *)src);
	index = 0;
	if (dstsize < 1)
		return (lensrc);
	while ((index < (dstsize - 1)) && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = 0;
	return (lensrc);
}
