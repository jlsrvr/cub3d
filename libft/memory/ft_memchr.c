/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:57:38 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/01 11:57:51 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char	*s;
	size_t		index;

	s = (const char *)str;
	index = 0;
	while (index < n)
	{
		if (s[index] == c)
			return ((void *)(str + index));
		index++;
	}
	return (NULL);
}
