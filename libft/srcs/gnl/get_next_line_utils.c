/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:36:57 by tigerber          #+#    #+#             */
/*   Updated: 2021/03/31 12:47:09 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"


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

char		*ft_newrest(char *str)
{
	char	*dest;
	int		i;

	i = 0;
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
