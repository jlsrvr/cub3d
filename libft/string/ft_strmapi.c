/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:49:00 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/01 14:04:10 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*dest;
	size_t		index;

	if (!s)
		return (NULL);
	if (!f)
		return (ft_strdup(s));
	dest = (char *)malloc(sizeof(*dest) * (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	index = -1;
	while (s[++index])
		dest[index] = f(index, s[index]);
	dest[index] = 0;
	return (dest);
}
