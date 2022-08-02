/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:42:11 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 15:22:26 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(count * size);
	if (!(ptr))
		return (NULL);
	while (i < (int)(count * size))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
