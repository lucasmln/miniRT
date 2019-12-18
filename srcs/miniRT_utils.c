/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:22:36 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/18 12:18:13 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

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
	fd = open(av, O_RDONLY);
	if (!(param = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ret = read(fd, param, size);
	param[size] = '\0';
	return (param);
}

void		ft_go_start_lst(t_data *data, char *lst)
{
	if (ft_strncmp(lst, "light", 5) == 0 && data->light->next)
	{
		while (data->light->rank != -1)
			data->light = data->light->next;
		data->light = data->light->next;
	}
	else if (ft_strncmp(lst, "camera", 6) == 0 && data->cam->next)
	{
		while (data->cam->rank != -1)
			data->cam = data->cam->next;
		data->cam = data->cam->next;
	}
	else if (ft_strncmp(lst, "sphere", 6) == 0 && data->sp->next)
	{
		while (data->sp->rank != -1)
			data->sp = data->sp->next;
		data->sp = data->sp->next;
	}
	else if (ft_strncmp(lst, "plane", 5) == 0 && data->pl->next)
	{
		while (data->pl->rank != -1)
			data->pl = data->pl->next;
		data->pl = data->pl->next;
	}
	ft_go_start_2(data, lst);
}

void		ft_go_start_2(t_data *data, char *lst)
{
	if (ft_strncmp(lst, "square", 6) == 0 && data->sq->next)
	{
		while (data->sq->rank != -1)
			data->sq = data->sq->next;
		data->sq = data->sq->next;
	}
	else if (ft_strncmp(lst, "cylinder", 8) == 0 && data->cy->next)
	{
		while (data->cy->rank != -1)
			data->cy = data->cy->next;
		data->cy = data->cy->next;
	}
	else if (ft_strncmp(lst, "triangle", 8) == 0 && data->tr->next)
	{
		while (data->tr->rank != -1)
			data->tr = data->tr->next;
		data->tr = data->tr->next;
	}
	else if (ft_strncmp(lst, "all obj", 7) == 0)
	{
		ft_go_start_lst(data, "sphere");
		ft_go_start_lst(data, "plane");
		ft_go_start_2(data, "square");
		ft_go_start_2(data, "cylinder");
		ft_go_start_2(data, "triangle");
	}
}
