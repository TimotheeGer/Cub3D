/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 12:12:01 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/12 15:32:27 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_struct(t_para *par)
{
	if (par->textNO.path != NULL)
	{
		free(par->textNO.path);
		par->textNO.path = NULL;
	}
	if (par->textEA.path != NULL)
	{
		free(par->textEA.path);
		par->textEA.path = NULL;
	}
	if (par->textSO.path != NULL)
	{
		free(par->textSO.path);
		par->textSO.path = NULL;
	}
	if (par->textWE.path != NULL)
	{
		free(par->textWE.path);
		par->textWE.path = NULL;
	}
	if (par->textSp.path != NULL)
	{
		free(par->textSp.path);
		par->textSp.path = NULL;
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

void	ft_lstclear_sp(t_para *par, void (*del)(void*))
{
	t_para *temp;

	while (par->sprite != NULL)
	{
		temp->sprite = par->sprite;
		del(temp->sprite->sp_x);
		del(temp->sprite->sp_y);
		par->sprite = temp->sprite->next;
		free(temp->sprite);
	}
	*par->sprite = NULL;
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
