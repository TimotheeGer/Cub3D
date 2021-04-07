/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:30:12 by tigerber          #+#    #+#             */
/*   Updated: 2021/03/31 12:48:07 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "./libft.h"
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

char	*get_first_line(int fd, char *buff, char **line, char *temp);
char	*ft_strnew(void);
char	*ft_newrest(char *str);
int		ft_tempavbs(char *temp);
char	*ft_lineintemp(char *temp);
int		get_next_line(int fd, char **line);

#endif
