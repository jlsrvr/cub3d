/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 23:10:01 by jrivoire          #+#    #+#             */
/*   Updated: 2020/12/12 16:04:16 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		index;
	char		*pdest;
	const char	*psrc;

	if (dest == NULL && src == NULL)
		return (NULL);
	index = 0;
	pdest = dest;
	psrc = src;
	while (index < n)
	{
		*pdest++ = *psrc++;
		index++;
	}
	return (dest);
}
