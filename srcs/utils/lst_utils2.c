/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:52:16 by tigerber          #+#    #+#             */
/*   Updated: 2021/07/06 16:02:00 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_lstclear_sp(t_lstsp *sp_begin)
{
	t_para	temp;

	while (sp_begin != NULL)
	{
		temp.sprite = sp_begin;
		sp_begin = temp.sprite->next;
		if (temp.sprite)
			free(temp.sprite);
	}
	sp_begin = NULL;
}

void	ft_lstadd_backsprite(t_lstsp **alst, t_lstsp *new)
{
	t_lstsp	*temp;

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

t_lstsp	*ft_newsprite(int x, int y)
{
	t_lstsp	*newsprite;

	newsprite = malloc (sizeof (t_lstsp));
	if (!(newsprite))
		return (NULL);
	newsprite->sp_y = y;
	newsprite->sp_x = x;
	newsprite->next = NULL;
	return (newsprite);
}
