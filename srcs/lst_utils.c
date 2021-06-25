/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:12:01 by tigerber          #+#    #+#             */
/*   Updated: 2021/06/23 15:56:58 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_struct(t_para *par)
{
	if (par->t_no.path != NULL)
	{
		free(par->t_no.path);
		par->t_no.path = NULL;
	}
	if (par->t_ea.path != NULL)
	{
		free(par->t_ea.path);
		par->t_ea.path = NULL;
	}
	if (par->t_so.path != NULL)
	{
		free(par->t_so.path);
		par->t_so.path = NULL;
	}
	if (par->t_we.path != NULL)
	{
		free(par->t_we.path);
		par->t_we.path = NULL;
	}
	if (par->t_sp.path != NULL)
	{
		free(par->t_sp.path);
		par->t_sp.path = NULL;
	}
	if (par->map != NULL)
	{
		ft_free_tab(par->map);
	}
}

void	ft_free_tab(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *temp;

	while (*lst != NULL)
	{
		temp = *lst;
		del(temp->content);
		*lst = temp->next;
		free(temp);
	}
	*lst = NULL;
}

void	ft_lstclear_sp(t_lstsp *sp_begin)
{
	t_para temp;

	while (sp_begin != NULL)
	{
		temp.sprite = sp_begin;
		sp_begin = temp.sprite->next;
		if (temp.sprite)
			free(temp.sprite);
	}
	sp_begin = NULL;
}

void		ft_lstadd_backsprite(t_lstsp **alst, t_lstsp *new)
{
	t_lstsp *temp;

	if (!alst || !new)
		return ;
	if (*alst)
	{
		temp = *alst;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	else
		*alst = new;
}

t_lstsp		*ft_newsprite(int x, int y)
{
	t_lstsp	*newsprite;

	if (!(newsprite = malloc(sizeof(t_lstsp))))
		return (NULL);
	newsprite->sp_y = y;
	newsprite->sp_x = x;
	newsprite->next = NULL;
	return (newsprite);
}

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (!alst || !new)
		return ;
	if (*alst)
	{
		temp = *alst;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	else
		*alst = new;
}

t_list		*ft_lstnew(void *content)
{
	t_list	*newlist;

	if (!(newlist = malloc(sizeof(t_list))))
		return (NULL);
	newlist->content = content;
	newlist->next = NULL;
	return (newlist);
}

void		ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!(lst))
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
