/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:12:56 by tigerber          #+#    #+#             */
/*   Updated: 2022/02/10 17:44:32 by tigerber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_check_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	ft_checkargu(char *arg)
{
	int	i;

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
	if (par->index.no != 1)
		ft_quit(0, "Error\nMissing ./path_NO or too much ./path_NO.\n", par);
	if (par->index.so != 1)
		ft_quit(0, "Error\nMissing ./path_SO or too much ./path_SO.\n", par);
	if (par->index.we != 1)
		ft_quit(0, "Error\nMissing ./path_WE or too much ./path_WE.\n", par);
	if (par->index.ea != 1)
		ft_quit(0, "Error\nMissing ./path_EA or too much ./path_EA.\n", par);
	if (par->index.f != 1)
		ft_quit(0, "Error\nMissing RGB floor or too much RGB floor.\n", par);
	if (par->index.c != 1)
		ft_quit(0, "Error\nMissing RGB ceil or too much RGB ceil.\n", par);
	if (par->indexmap != 1)
		ft_quit(0, "Error\nMissing Map.\n", par);
}

void	ft_argu(t_data *d, int ac, char **av)
{
	if (ac == 1)
		ft_quit(1, "Error\nerror argument.\n", NULL);
	if ((ft_checkargu(av[1])) == 1 && ac == 2)
		d->fd = open(av[1], O_RDONLY);
	else
		ft_quit(1, "Error\nerror argument.\n", NULL);
	if (d->fd == -1)
		ft_quit(1, "Error\nerror argument.\n", NULL);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_list		*lst;
	char		*line;

	line = NULL;
	lst = NULL;
	ft_memset(&data, 0, sizeof(t_data));
	ft_argu(&data, ac, av);
	while (get_next_line(data.fd, &line))
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
	ft_ray(&data);
	return (0);
}
