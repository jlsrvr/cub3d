/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:27:16 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/01 11:39:30 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	len_num(int n)
{
	size_t			len;
	unsigned int	nbr;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		nbr = -n;
	}
	else
		nbr = n;
	while (nbr > 9)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len + 1);
}

static	void	store_num(unsigned int nbr, char *num, size_t *index)
{
	if (nbr < 10)
		num[(*index)++] = (nbr + 48);
	else
	{
		store_num((nbr / 10), num, index);
		store_num((nbr % 10), num, index);
	}
	num[*index] = 0;
	return ;
}

char	*ft_itoa(int n)
{
	char			*num;
	size_t			index;
	unsigned int	nbr;

	num = malloc(sizeof(*num) * (len_num(n) + 1));
	if (!num)
		return (NULL);
	index = 0;
	if (n < 0)
	{
		num[index++] = '-';
		nbr = -n;
	}
	else
		nbr = n;
	store_num(nbr, num, &index);
	return (num);
}
