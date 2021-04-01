/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:49:00 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/01 14:41:37 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}	
}

int			ft_isdigit(char c)
{
	int i = 0;
	
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);	
}

int	ft_atoi(char *str)
{
	int i;
	int res;
	int neg;

	i = 0;
	res = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
	{
		i++;
	}
	if (str[i] == '-')
	{
		neg = -1;
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res = res + (str[i] - 48);
		i++;
	}
	return (res * neg);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;

	i = 0;
	if (!(str = malloc(sizeof(char) * ft_strlen((char*)s1) + 1)))
	{
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_memset(void *s, int c, size_t n)
{
	int		i;
	char	*str;

	i = 0;
	str = (char*)s;
	while (i < (int)n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

int		ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return (0);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while ((needle[j] == haystack[i + j]) && i + j < len)
		{
			if (needle[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		ft_strncmp(const char *s1, const char *s2, int n)
{
	int i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && (i < n - 1) && (unsigned char)s1[i] == (unsigned char)s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}