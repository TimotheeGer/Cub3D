/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:17:53 by tigerber          #+#    #+#             */
/*   Updated: 2021/03/25 13:05:18 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char				*ft_strnew(void)
{
	char	*dest;

	if (!(dest = malloc(sizeof(char) * (1))))
		return (NULL);
	dest[0] = '\0';
	return (dest);
}

char				*ft_lineintemp(char *temp)
{
	char			*str;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (temp && temp[i] != '\n' && temp[i] != '\0')
	{
		i++;
	}
	if (!(str = malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (temp[j] && j < i)
	{
		str[j] = temp[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int					get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	char			*tempo;
	static char		*temp;
	int				ret;

	ret = 0;
	if (fd < 0 || line == NULL || BUFFER_SIZE < 1 || read(fd, buff, 0) < 0)
		return (-1);
	if (!temp && (!(temp = ft_strnew())))
		return (-1);
	while ((!(ft_tempavbs(temp))) && (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tempo = temp;
		temp = ft_strjoin(tempo, buff);
		free(tempo);
	}
	*line = ft_lineintemp(temp);
	if ((ft_newrest(temp)) == NULL)
	{
		free(temp);
		temp = NULL;
		return (0);
	}
	return (1);
}
