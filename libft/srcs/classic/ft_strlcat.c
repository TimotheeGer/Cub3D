/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:55:25 by tigerber          #+#    #+#             */
/*   Updated: 2021/03/31 12:29:54 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t lendest;
	size_t lensrc;

	i = 0;
	lendest = ft_strlen(dst);
	lensrc = ft_strlen(src);
	j = lendest + lensrc;
	if (size <= lendest)
		return (lensrc + size);
	while (src[i] && lendest + i < size - 1)
	{
		dst[lendest + i] = src[i];
		i++;
	}
	dst[lendest + i] = '\0';
	return (j);
}
