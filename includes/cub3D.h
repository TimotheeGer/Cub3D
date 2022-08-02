/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:42:48 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 17:45:00 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/includes/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include "../mlx/mlx.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_lstsprite
{
	int					sp_x;
	int					sp_y;
	struct s_lstsprite	*next;
}				t_lstsp;

typedef struct s_full_screen
{
	int	x;
	int	y;
	int	color;
}				t_screen;

typedef struct s_mini_map
{
	int	x;
	int	y;
	int	xo;
	int	yo;
	int	xa;
}				t_mini_map;

typedef struct s_floor
{
	int		w;
	int		h;
	int		x;
	int		y;
	float	rdx0;
	float	rdy0;
	float	rdx1;
	float	rdy1;
	int		p;
	float	posz;
	float	rwdist;
	float	flrstpx;
	float	flrstpy;
	float	flrx;
	float	flry;
	int		cellx;
	int		celly;
	int		tx;
	int		ty;
	int		i;
	int		color;
}					t_floor;

typedef struct s_raycast
{
	int		i;
	int		x;
	int		w;
	int		h;
	int		y;
	double	camx;
	double	rdirx;
	double	rdiry;
	int		mapx;
	int		mapy;
	double	sdstx;
	double	sdsty;
	double	dltdx;
	double	dltdy;
	double	pwlldst;
	int		stpx;
	int		stpy;
	int		hit;
	int		side;
	int		lineh;
	int		drws;
	int		drwe;
	double	wallx;
	double	step;
	double	texpos;
	int		texx;
	int		texy;
	int		color;
}					t_ray;

typedef struct s_index
{
	int	r;
	int	no;
	int	so;
	int	we;
	int	ea;
	int	sp;
	int	f;
	int	c;
}				t_index;

typedef struct s_texture
{
	char	*path;
	int		width;
	int		heigth;
	void	*img;
	char	*addr;
	int		b_p_pix;
	int		line_len;
	int		endian;
}				t_tex;

typedef struct s_player
{
	char	vue;
	int		pos_x;
	int		pos_y;
	int		indexno;
	int		indexso;
	int		indexwe;
	int		indexea;
	int		indexsp;
}				t_perso;

typedef struct s_par
{
	int			rx;
	int			ry;
	t_tex		t_ea;
	t_tex		t_no;
	t_tex		t_so;
	t_tex		t_we;
	t_tex		t_sp;
	t_tex		t_f;
	int			fl[3];
	int			ci[3];
	char		**map;
	int			indexmap;
	t_index		index;
	t_lstsp		*sprite;
	t_list		*lst_begin;
	t_lstsp		*sp_begin;
	int			map_open;
}					t_para;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;

}				t_img;

typedef struct s_data
{
	t_ray		r;
	t_screen	s;
	t_mini_map	m;
	t_perso		perso;
	t_para		par;
	t_img		player;
	t_img		screen;
	t_floor		f;
	int			fd;
	int			i;
	int			j;
	float		y;
	float		x;
	float		dx;
	float		dy;
	double		olddirx;
	double		oldplanex;
	float		planex;
	float		planey;
	float		a;
	int			refresh;
	double		move;
	double		rota;
	int			color;
	int			color3;
	int			colorf;
	int			colorc;
	int			colormap1;
	int			colormap2;
	void		*mlx;
	void		*win;
	int			maps;
	int			refreeesh;
}					t_data;

void		raycast_part_three(t_data *d);
void		raycast_part_two(t_data *d);
void		init_raycast_part_one(t_data *d);
void		ft_floor(t_data *d);
void		init_floor_one(t_data *d);
int			ft_line_av_one(char *line, char c);
void		free_struct(t_para *par);
void		ft_lstclear_sp(t_lstsp *par);
void		ft_free_tab(char **strs);
void		ft_checkisdigit(char *str, t_para *par, char **strs);
void		ft_indexplus(char c, t_perso *perso, int y, int x);
void		ft_control0(t_para *par, int len, t_perso *perso);
int			ft_checkisnwse201(char c);
int			ft_checkis0news2(char c);
int			ft_checkisnews(char c);
int			ft_countline_map(char **map);
void		ft_checkpos(t_perso *perso, t_para *par);
t_lstsp		*ft_newsprite(int x, int y);
void		ft_lstadd_backsprite(t_lstsp **alst, t_lstsp *new);
void		ft_checkaround(char **map, int y, int x, t_para *par);
void		ft_get_allpara(t_para *par, t_list *lst);
void		ft_mapisok(t_para *par, t_perso *perso);
int			ft_quit(int a, char *str, t_para *par);
int			ft_checkpara(char *str, char c);
int			ft_countlst(t_list *lst);
void		ft_get_no(t_para *par, char *line);
void		ft_get_so(t_para *par, char *line);
void		ft_get_we(t_para *par, char *line);
void		ft_get_ea(t_para *par, char *line);
void		ft_get_s(t_para *par, char *line);
void		ft_get_r(t_para *par, char *line);
void		ft_get_f(t_para *par, char *line);
void		ft_get_c(t_para *par, char *line);
void		ft_get_map(t_para *par, t_list *lst);
void		ft_lstadd_back(t_list **alst, t_list *new);
t_list		*ft_lstnew(void *content);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
int			create_trgb(int t, int r, int g, int b);
void		raycaster(t_data *img);
int			key_hook(int keycode, t_data *img);
void		ft_ray(t_data *data);
void		full_screen_bicolor(t_data *data);
void		ft_init(t_data *data);
int			add_shade(double distance, int color);
void		draw_map(t_data *data);
void		draw_player(t_data *data, int size);
int			ft_cross(t_data *d);
int			ft_escape(int keycode, t_data *d, int a);
void		ft_destroy(t_data *d);
int			ft_check_char(char *str, char c);
void		ft_vue(t_data *data);
#endif