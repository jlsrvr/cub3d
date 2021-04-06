/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:11:49 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/01 14:19:15 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	index;

	index = (int)ft_strlen((char *)s);
	while (index >= 0)
	{
		if (s[index] == c)
			return ((char *)(s + index));
		index--;
	}
	return (NULL);
}
