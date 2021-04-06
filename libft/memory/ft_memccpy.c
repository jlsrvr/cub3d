/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 23:09:08 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/01 11:57:11 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	index;
	char	*csrc;
	char	*cdest;

	csrc = (char *)src;
	cdest = (char *)dest;
	index = 0;
	while (index < n)
	{
		cdest[index] = csrc[index];
		if ((unsigned char)(csrc[index]) == (unsigned char)c)
			return (&dest[index + 1]);
		index++;
	}
	return (NULL);
}
