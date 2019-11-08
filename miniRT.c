/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:31 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/08 19:07:45 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft/libft.h"
#include "minilibx_opengl/mlx.h"
#include <stdio.h>
#define BUF_SIZE 1024


char	*ft_read_file(char *av)
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

int		*ft_get_render(char *s)
{
	int		i;
	int		k;
	int		*render;

	i = 0;
	k = 0;
	if (!(render = malloc(sizeof(int) * 2)) || !s)
		return (NULL);
	while (s[i] && s[i] != 'R')
		i++;
	if (s[i] != 'R')
		return (NULL);
	i++;
	while (k < 2)
	{
		while (s[i] == ' ')
			i++;
		if (s[i] <= '0' || s[i] >= '9')
			return (NULL);
		render[k] = ft_atoi(&s[i]);
		k++;
	}
	return (render);
}



int		main(int ac, char **av)
{
	char	*param;
	int		*render;
	unsigned int	color;
	data_t	data;

	int		i = 0;
	int		k = 0;

	param = ft_read_file(av[1]);
	render = ft_get_render(param);
	if (render == NULL)
		return (-1);
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (-1);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, render[0], render[1], "miniRT")) == NULL)
		return (-1);
	mlx_loop(data.mlx_ptr);
	color = 0x255;
	color = color * 100 + 0x255;
	color = color * 100 + 0x255;
	int	save;
	while (i < render[0])
	{
		k = 0;
		while (i < render[1])
		{
			save = mlx_pixel_put(data.mlx_ptr, data.mlx_win, i, k, 0xffffff);
			k++;
		}
		i++;
	}
	return (0);
}
