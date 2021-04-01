/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:36:57 by tigerber          #+#    #+#             */
/*   Updated: 2021/03/31 14:05:00 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

size_t		ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	while (s1[j] != '\0')
	{
		str[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}

int			ft_tempavbs(char *temp)
{
	int	i;

	i = 0;
	while (temp && temp[i])
	{
		if (temp[i] == '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

// char		*ft_strdup(const char *s1)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	if (!(str = malloc(sizeof(char) * ft_strlen((char*)s1) + 1)))
// 	{
// 		return (NULL);
// 	}
// 	while (s1[i] != '\0')
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

char		*ft_newrest(char *str)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_tempavbs(str))
	{
		while (str && str[i] != '\n' && str[i] != '\0')
			i++;
		dest = ft_strdup(&str[i + 1]);
		i = 0;
		while (dest[i])
		{
			str[i] = dest[i];
			i++;
		}
		str[i] = '\0';
		free(dest);
		return (str);
	}
	return (NULL);
}
