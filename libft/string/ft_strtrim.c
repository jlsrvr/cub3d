/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:00:22 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/01 14:19:40 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			begin;
	size_t			end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	begin = 0;
	end = ft_strlen(s1);
	while (s1[begin] && ft_in_set(s1[begin], set))
		begin++;
	if (begin == end)
		return (ft_strdup(""));
	while (ft_in_set(s1[(end - 1)], set))
		end--;
	return (ft_substr(s1, begin, (end - begin)));
}
