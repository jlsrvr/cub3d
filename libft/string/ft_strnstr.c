/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:16:11 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/01 14:18:36 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	look;

	index = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[index] && index < len)
	{
		look = 0;
		while (haystack[(index + look)] == needle[look]
			&& needle[look] && (index + look) < len)
			look++;
		if (!needle[look])
			return (&((char *)haystack)[index]);
		index++;
	}
	return (NULL);
}
