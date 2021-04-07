/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:55:47 by tigerber          #+#    #+#             */
/*   Updated: 2021/03/31 12:34:51 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *map;
	t_list *tmp;

	map = NULL;
	while (lst)
	{
		if (!map)
		{
			if (!(map = ft_lstnew(f(lst->content))))
				return (NULL);
			tmp = map;
		}
		else
		{
			if (!(tmp->next = ft_lstnew(f(lst->content))))
			{
				ft_lstclear(&map, del);
				return (NULL);
			}
			tmp = tmp->next;
		}
		lst = lst->next;
	}
	return (map);
}
