/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:18:57 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/21 11:06:55 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int			ft_set_color(t_vect3 c)
{
	return (((((int)c.x << 8) + (int)c.y) << 8) + (int)c.z);
}

char		*ft_read_file(char *av)
{
	int		ret;
	int		fd;
	int		size;
	char	buf[BUF_SIZE + 1];
	char	*param;

	fd = open(av, O_RDONLY);
	size = 0;
	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
		size += ret;
	close(fd);
	if (size == 0)
		ft_print_error(-3);
	fd = open(av, O_RDONLY);
	if (!(param = malloc(sizeof(char) * (size + 1))))
		ft_print_error(-1);
	ret = read(fd, param, size);
	param[size] = '\0';
	return (param);
}

void		ft_go_start_lst(char *lst)
{
	if (ft_strncmp(lst, "light", 5) == 0 && g_data->light->rank != 0)
	{
		if (g_data->light->rank == 0)
			return ;
		while (g_data->light->rank != -1)
			g_data->light = g_data->light->next;
		g_data->light = g_data->light->next;
	}
	else if (ft_strncmp(lst, "camera", 6) == 0 && g_data->cam->next)
	{
		while (g_data->cam->rank != -1)
			g_data->cam = g_data->cam->next;
		g_data->cam = g_data->cam->next;
	}
	else if (ft_strncmp(lst, "sphere", 6) == 0 && g_data->sp->next)
	{
		while (g_data->sp->rank != -1)
			g_data->sp = g_data->sp->next;
		g_data->sp = g_data->sp->next;
	}
	ft_go_start_2(lst);
}

void		ft_go_start_2(char *lst)
{
	if (ft_strncmp(lst, "cylinder", 8) == 0 && g_data->cy->next)
	{
		while (g_data->cy->rank != -1)
			g_data->cy = g_data->cy->next;
		g_data->cy = g_data->cy->next;
	}
	else if (ft_strncmp(lst, "triangle", 8) == 0 && g_data->tr->next)
	{
		while (g_data->tr->rank != -1)
			g_data->tr = g_data->tr->next;
		g_data->tr = g_data->tr->next;
	}
	else if (ft_strncmp(lst, "all obj", 7) == 0)
	{
		ft_go_start_lst("sphere");
		ft_go_start_lst("plane");
		ft_go_start_lst("square");
		ft_go_start_lst("cylinder");
		ft_go_start_lst("triangle");
	}
	ft_go_start_3(lst);
}

void		ft_go_start_3(char *lst)
{
	if (ft_strncmp(lst, "cam", 3) == 0 && g_data->cam->next)
	{
		while (g_data->cam->rank != -1)
			g_data->cam = g_data->cam->next;
		g_data->cam = g_data->cam->next;
	}
	else if (ft_strncmp(lst, "plane", 5) == 0 && g_data->pl->next)
	{
		while (g_data->pl->rank != -1)
			g_data->pl = g_data->pl->next;
		g_data->pl = g_data->pl->next;
	}
	if (ft_strncmp(lst, "square", 6) == 0 && g_data->sq->next)
	{
		while (g_data->sq->rank != -1)
			g_data->sq = g_data->sq->next;
		g_data->sq = g_data->sq->next;
	}
}
