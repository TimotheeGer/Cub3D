/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:42:48 by tigerber          #+#    #+#             */
/*   Updated: 2021/06/21 16:06:26 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef _CUB3D_
# define _CUB3D_
# include "../libft/includes/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include "../mlx/mlx.h"
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

typedef struct		s_floor
{
	int		w;
	int		h;
	int		x;
	int		y;
	float	raydirx0;
    float	raydiry0;
    float	raydirx1;
    float	raydiry1;
	int		p;
	float	posz;
	float	rowdistance;
	float	floorstepx;
	float	floorstepy;
	float	floorx;
	float	floory;
	int		cellx;
	int		celly;
	int		tx;
	int		ty;
	int		i;
	int		color;
}					t_floor;


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
	int		width;
	int		heigth;
	void	*img;
	char	*addr;
	int		b_p_pix;
	int		line_len;
	int		endian;
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
	t_tex     t_ea; // structure des textures EAST
	t_tex     t_no; // structure des textures NORD
	t_tex     t_so; // structure des textures SOUTH
	t_tex     t_we; // structure des textures WEST
	t_tex     t_sp; // structure des textures SPRITE
	t_tex     t_sol; // structure des textures SPRITE
	int       F[3]; //[0]R [1]G [2]B
	int       C[3]; //[0]R [1]G [2]B //255 max
	char      **map;
	int       indexmap;
	t_index   index;
	t_lstsp   *sprite;
	t_list    *lst_begin;
	t_lstsp	  *sp_begin;
	int		  map_open;
}                    t_para;

typedef struct	s_img
{
	
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
	int		color2;

}				t_img;

typedef struct	s_data
{
	t_perso perso;
	t_para	par;
	t_img   player;
	t_img   screen;
	t_floor	f;
	int 	i;
	int		j;
	float	y;
	float	x;
	float	dx;
	float	dy;
	float	planeX;
	float	planeY;
	float	a;
	int     refresh;
	double	move;
	double	rota;
	int		color;
	int		color2;
	int		color3;
	int		colorF;
	int		colorC;
	int		colormap1;
	int		colormap2;
	void	*mlx;
	void	*win;
	int		mapS;
}				t_data;
// autoure dun 0 N S E W 2 pas despace sinon map ouverte
int			ft_line_av_one(char *line, char c);
void        free_struct(t_para *par);
void	    ft_lstclear_sp(t_lstsp *par);
void	    ft_free_tab(char **strs);
void        ft_checkisdigit(char *str, t_para *par, char **strs);
void        ft_indexplus(char c, t_perso *perso, int y, int x);
void        ft_control0(t_para *par, int len, t_perso *perso); 
int         ft_checkisnwse201(char c);
int         ft_checkis0news2(char c);
int         ft_checkisnews(char c);
int         ft_countline_map(char **map);
void        ft_checkpos(t_perso *perso, t_para *par);
t_lstsp     *ft_newsprite(int x, int y);
void	    ft_lstadd_backsprite(t_lstsp **alst, t_lstsp *new);
void        ft_checkaround(char **map, int y, int x, t_para *par);
void        ft_get_allpara(t_para *par, t_list *lst);
void        ft_mapisok(t_para *par, t_perso *perso);
int         ft_quit(int a, char *str, t_para *par);
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
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			create_trgb(int t, int r, int g, int b);
void		drawverticalline(t_data *data, int x, int drawstart, int drawend, int color);
void    	raycaster(t_data *img);
int			key_hook2(int keycode, t_data *img);
void		ft_ray(t_data *data);
void		full_screen_grey(t_data *data);
void		ft_init(t_data *data);
int     	add_shade(double distance, int color);
void		drawMap(t_data *data);
void		drawPlayer2d(t_data *data, int size);
void		ft_sprite(t_data *d);
int			ft_cross(int keycode, t_data *d);
# endif