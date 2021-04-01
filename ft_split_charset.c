/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 11:27:43 by ldrieu            #+#    #+#             */
/*   Updated: 2021/04/01 16:05:08 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include <stdlib.h>

int		cmp_char(char c, char *str)
{
	int i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int		count_words(char *str, char *charset)
{
	int i;
	int count;
	int check;

	i = 0;
	count = 0;
	check = 0;
	if (charset[0] == '\0')
		return (1);
	while (str[i])
	{
		if (check == 1 && cmp_char(str[i], charset) == 1)
			check = 0;
		if (check == 0 && cmp_char(str[i], charset) == 0)
		{
			check = 1;
			count++;
		}
		i++;
	}
	return (count);
}

int		lengthword(char *str, int k, char *charset)
{
	int len;

	len = 0;
	if (charset[0] == '\0')
	{
		while (str[len])
			len++;
		return (len);
	}
	while (cmp_char(str[k], charset) == 0)
	{
		k++;
		len++;
	}
	return (len);
}

char	*strsub(char *str, int start, int size)
{
	char	*newstr;
	int		i;

	i = 0;
	if (!(newstr = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (i < size)
	{
		newstr[i] = str[start];
		start++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	**ft_split(char *str, char *charset)
{
	char	**split;
	int		words;
	int		i;
	int		k;

	k = 0;
	i = 0;
	if (str == NULL)
		return (NULL);
	words = count_words(str, charset);
	if (!(split = (char **)malloc(sizeof(char *) * words + 1)))
		return (NULL);
	while (words > 0)
	{
		while (cmp_char(str[k], charset) == 1)
			k++;
		split[i] = strsub(str, k, lengthword(str, k, charset));
		i++;
		words--;
		k = k + lengthword(str, k, charset);
	}
	split[i] = NULL;
	return (split);
}
