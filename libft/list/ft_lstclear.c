/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrivoire <jrivoire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 21:00:15 by jrivoire          #+#    #+#             */
/*   Updated: 2021/04/01 11:44:32 by jrivoire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*my_lst;

	if (!lst || !del)
		return ;
	my_lst = *lst;
	if (!my_lst)
	{
		lst = NULL;
		return ;
	}
	while (my_lst)
	{
		temp = my_lst->next;
		del(my_lst->content);
		free(my_lst);
		my_lst = temp;
	}
	*lst = NULL;
}
