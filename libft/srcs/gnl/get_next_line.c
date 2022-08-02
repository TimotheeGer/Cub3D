/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 10:17:53 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 19:35:18 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_strnew(void)
{
	char	*dest;

	dest = malloc(sizeof(char) * (1));
	if (!(dest))
		return (NULL);
	dest[0] = '\0';
	return (dest);
}

char	*ft_lineintemp(char *temp)
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
	str = malloc(sizeof(char) * i + 1);
	if (!(str))
		return (NULL);
	while (temp[j] && j < i)
	{
		str[j] = temp[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	ft_free_tmp(char *temp)
{
	free(temp);
	temp = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	char			*tempo;
	static char		*temp;
	int				ret;

	ret = 1;
	if (fd < 0 || line == NULL || BUFFER_SIZE < 1 || read(fd, buff, 0) < 0)
		return (-1);
	if (temp == NULL)
		temp = ft_strnew();
	while ((!(ft_tempavbs(temp))) && (ret > 0))
	{
		ret = read(fd, buff, BUFFER_SIZE);
		buff[ret] = '\0';
		tempo = temp;
		temp = ft_strjoin(tempo, buff);
		free(tempo);
	}
	*line = ft_lineintemp(temp);
	if ((ft_newrest(temp)) == NULL)
	{
		return (ft_free_tmp(temp));
	}
	return (1);
}
