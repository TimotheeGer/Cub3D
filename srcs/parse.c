/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:12:56 by tigerber          #+#    #+#             */
/*   Updated: 2021/05/31 11:39:12 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ft_quit(int a, char *str, t_para *par)
{
	if (a == 0)
		write(2, str, ft_strlen(str));
	ft_lstclear(&par->lst_begin, free);
	free_struct(par);
	ft_lstclear_sp(par->sp_begin);
	exit(0);
}

int		ft_checkargu(char *arg)
{
	int i;

	i = ft_strlen(arg) - 4;
	if (arg[i] == '.')
	{
		if ((ft_strncmp(&arg[i], ".cub", 4) == 0))
			return (1);
	}
	return (0);
}

void	ft_checkpara_isok(t_para *par)
{
	if (par->index.R != 1)
		ft_quit(0, "Missing resolution or too much resolution.\n", par);
	if (par->index.NO != 1)
		ft_quit(0, "Missing ./path_NO or too much ./path_NO.\n", par);
	if (par->index.SO != 1)
		ft_quit(0, "Missing ./path_SO or too much ./path_SO.\n", par);
	if (par->index.WE != 1)
		ft_quit(0, "Missing ./path_WE or too much ./path_WE.\n", par);
	if (par->index.EA != 1)
		ft_quit(0, "Missing ./path_EA or too much ./path_EA.\n", par);
	if (par->index.SP != 1)
		ft_quit(0, "Missing ./path_SP or too much ./path_SP.\n", par);
	if (par->index.F != 1)
		ft_quit(0, "Missing RGB floor or too much RGB floor.\n", par);
	if (par->index.C != 1)
		ft_quit(0, "Missing RGB ceil or too much RGB ceil.\n", par);
	if (par->indexmap != 1)
		ft_quit(0, "Missing Map.\n", par);
}

void	ft_print_test(t_para *par, t_perso *perso)
{
	int i;

	i = 0;
	printf("R = [%d] [%d]\n", par->Rx, par->Ry);
	printf("F = [%d] [%d] [%d]\n", par->F[0], par->F[1], par->F[2]);
	printf("C = [%d] [%d] [%d]\n", par->C[0], par->C[1], par->C[2]);
	printf("textno = [%s]\n", par->textNO.path);
	printf("textSO = [%s]\n", par->textSO.path);
	printf("textWE = [%s]\n", par->textWE.path);
	printf("textEA = [%s]\n", par->textSO.path);
	printf("textSP = [%s]\n", par->textSp.path);
	while (par->map[i] != NULL)
	{
		printf("map = %s\n", par->map[i]);
		i++;
	}
	printf("indexR = %d\n", par->index.R);
	printf("indexNO = %d\n", par->index.NO);
	printf("indexSO = %d\n", par->index.SO);
	printf("indexWE = %d\n", par->index.WE);
	printf("indexEA = %d\n", par->index.EA);
	printf("indexSP = %d\n", par->index.SP);
	printf("indexF = %d\n", par->index.F);
	printf("indexC = %d\n", par->index.C);
	printf("Vue = %c\n", perso->vue);
	printf("pos_y = %d\n", perso->pos_y);
	printf("pos_x = %d\n", perso->pos_x);
	while (par->sprite)
	{
		printf("sprite sp_y = %d\n", par->sprite->sp_y);
		printf("sprite sp_x = %d\n", par->sprite->sp_x);
		par->sprite = par->sprite->next;
	}
}

//###############################################################################

int				main(int ac, char **av)
{
	(void)ac;
	t_data		data;
	//t_perso		perso; 
	t_list		*lst;
	char		*line;
	
	(void)av;
	int fd = 0;
	// if ((ft_checkargu(av[1])) == 1)
	// 	fd = open(av[1], O_RDONLY);
	// else
	// 	ft_quit(1, NULL, NULL);
	// if (fd == -1)
	// 	ft_quit(0, NULL, NULL);
	fd = open("srcs/map.cub", O_RDONLY);
	line = NULL;
	lst = NULL;;
	data.par.map = NULL;
	ft_memset(&data, 0, sizeof(t_data));
	while (get_next_line(fd, &line))
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(line)));
		free(line);
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(line)));
	free(line);
	data.par.lst_begin = lst;
	ft_get_allpara(&data.par, lst);
	ft_lstclear(&data.par.lst_begin, free);
	ft_checkpara_isok(&data.par);
	ft_mapisok(&data.par, &data.perso);
	ft_print_test(&data.par, &data.perso);
	ft_ray(&data);
	free_struct(&data.par);
	ft_lstclear_sp(data.par.sp_begin);
	return (0);
}
