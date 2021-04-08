/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:42:48 by tigerber          #+#    #+#             */
/*   Updated: 2021/04/06 14:50:42 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef _CUB3D_
# define _CUB3D_
# include "../libft/includes/libft.h"

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

//liste chainer pour sprite
typedef struct       s_lstsprite 
{
    int                 sp_x;
    int                 sp_y;
    struct s_lstsprite  *next;
}                   t_lstsp; // liste sprite

typedef struct      s_index
{
    int     R;
    int     NO;
    int     SO;
    int     WE;
    int     EA;
    int     SP;
    int     F;
    int     C;
}                   t_index;

typedef struct      s_texture
{
    char    *path; // ./path_to_the_texture 
}                   t_tex;

typedef struct      s_player
{
    char     vue; //vue du perso NO EA SO WE
    int      pos_x; //axe x
    int      pos_y; //axe y
    int      indexNO; // index on off des vue une seul vue autoriser
    int      indexSO; // -1 off // 1 on 
    int      indexWE;
    int      indexEA;
    int      indexSP;
}                   t_perso;


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
    t_index   index;
    t_lstsp   *sprite;
}                    t_para;

// autoure dun 0 N S E W 2 pas despace sinon map ouverte
void        ft_checkisdigit(char *str);
void        ft_indexplus(char c, t_perso *perso, int y, int x);
void        ft_control0(t_para *par, int len, t_perso *perso); 
int         ft_checkisnwse201(char c);
int         ft_checkis0news2(char c);
int         ft_checkisnews(char c);
int         ft_countline_map(char **map);
void        ft_checkpos(t_perso *perso);
t_lstsp     *ft_newsprite(int x, int y);
void	    ft_lstadd_backsprite(t_lstsp **alst, t_lstsp *new);
void        ft_checkaround(char **map, int y, int x, char c);
void        ft_get_allpara(t_para *par, t_list *lst);
void        ft_mapisok(t_para *par, t_perso *perso);
int         ft_quit(int a, char *str);
int         ft_checkpara(char *str, char c);
int         ft_countlst(t_list *lst);
void        ft_get_no(t_para *par, char *line);
void        ft_get_so(t_para *par, char *line);
void        ft_get_we(t_para *par, char *line);
void        ft_get_ea(t_para *par, char *line);
void        ft_get_s(t_para *par, char *line);
void        ft_get_r(t_para *par, char *line);
void        ft_get_f(t_para *par, char *line);
void        ft_get_c(t_para *par, char *line);
void        ft_get_map(t_para *par, t_list *lst);
void	    ft_lstadd_back(t_list **alst, t_list *new);
t_list	    *ft_lstnew(void *content);
void	    ft_lstiter(t_list *lst, void (*f)(void *));

# endif