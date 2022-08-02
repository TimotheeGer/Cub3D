/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:05 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 15:11:28 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	countword(char const *str, char c)
{
	int	i;
	int	sep;
	int	word;

	i = 0;
	sep = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && sep == 1)
		{
			sep = 0;
		}
		if (str[i] != c && sep == 0)
		{
			sep = 1;
			word++;
		}
		i++;
	}
	return (word);
}

static char	*getword(char const *s, int i, int newword)
{
	int		index;
	int		size;
	char	*ptr;

	size = i - newword;
	index = 0;
	ptr = malloc(sizeof(char) * ((newword) + 1));
	if (!(ptr))
		return (NULL);
	while (size < i)
	{
		ptr[index] = s[size];
		size++;
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}

static char	**getsplit(char **ptr, char const *s, char c, int count)
{
	int	i;
	int	j;
	int	newword;

	i = 0;
	j = -1;
	newword = 0;
	while (++j < count)
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			newword++;
		}
		ptr[j] = getword(s, i, newword);
		newword = 0;
	}
	ptr[j] = (NULL);
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**ptr;

	if (!s)
		return (NULL);
	count = countword(s, c);
	ptr = malloc(sizeof(char *) * (count + 1));
	if (!(ptr))
		return (NULL);
	ptr = getsplit(ptr, s, c, count);
	return (ptr);
}
