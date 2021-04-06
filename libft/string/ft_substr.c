/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:00:08 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/01 14:20:20 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*dest;
	size_t		index;

	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	dest = malloc(sizeof(*dest) * (len + 1));
	if (!dest)
		return (NULL);
	index = 0;
	while (s[index + start] && (len != index))
	{
		dest[index] = s[index + start];
		index++;
	}
	dest[index] = 0;
	return (dest);
}
