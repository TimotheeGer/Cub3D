/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:42:48 by tigerber          #+#    #+#             */
/*   Updated: 2021/03/26 15:39:28 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef _CUB3D_
# define _CUB3D_

# include <libc.h>

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct      s_texture
{
    char    *path; // ./path_to_the_texture 
}                   t_tex;

typedef struct      s_par
{
    int       Rx; //Resoution [0]axe x [1]axe y
    int       Ry; //Resoution [0]axe x [1]axe y
    t_tex     textNO; // structure des textures NORD
    t_tex     textEA; // structure des textures EAST
    t_tex     textSO; // structure des textures SOUTH
    t_tex     textWE; // structure des textures WEST
    t_tex     textSp; // structure des textures SPRITE
    int       F[3]; //[0]R [1]G [2]B
    int       C[3]; //[0]R [1]G [2]B //255 max
    char      **map;
    int       indexmap;
}                    t_para;

// autoure dun 0 N S E W 2 pas despace sinon map ouverte 

size_t		ft_strlen(char *s);
int		    ft_strnstr(const char *haystack, const char *needle, size_t len);
void	    *ft_memset(void *s, int c, size_t n);
char	    *ft_strdup(const char *s1);
void	    ft_lstadd_back(t_list **alst, t_list *new);
t_list	    *ft_lstnew(void *content);
void	    ft_lstiter(t_list *lst, void (*f)(void *));
char		**ft_split(char const *s, char c);
void	    ft_putchar(char c);
void	    ft_putstr(char *str);
int			ft_isdigit(char c);
int			ft_atoi(char *str);
char	    *ft_strdup(const char *s1);
size_t	    ft_strlen(char *s);
char	    *ft_strjoin(char *s1, char *s2);
char	    *get_first_line(int fd, char *buff, char **line, char *temp);
char	    *ft_strnew(void);
char	    *ft_newrest(char *str);
int		    ft_tempavbs(char *temp);
char	    *ft_lineintemp(char *temp);
int		    get_next_line(int fd, char **line);

# endif