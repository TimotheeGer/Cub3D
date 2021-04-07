/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:38:15 by tigerber          #+#    #+#             */
/*   Updated: 2021/03/31 12:30:26 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ischarset(char c, char const *charset)
{
	int		i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		k;
	int		l;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	k = ft_strlen((char*)s1) - 1;
	l = 0;
	while (ischarset(s1[i], set))
		i++;
	if (!(s1[i] == '\0'))
		while (ischarset(s1[k], set))
			k--;
	k += 1;
	if (!(ptr = malloc(sizeof(char) * (k - i) + 1)))
		return (NULL);
	while (i < k)
	{
		ptr[l++] = s1[i++];
	}
	ptr[l] = '\0';
	return (ptr);
}
