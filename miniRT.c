/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:31 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/12 13:07:53 by lmoulin          ###   ########.fr       */
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

int		ft_check_file(t_data *data, char *s)
{
	int		i;

	i = 0;
	if (s[i] == 'R')
}

int		main(int ac, char **av)
{
	char	*file;
	int		*render;
	t_data	*data;
	unsigned int	color;
	t_mlx	mlx;

	int		i = 0;
	int		k = 0;

	file = ft_read_file(av[1]);
	render = ft_get_render(file);
	if (render == NULL)
		return (-1);
	if ((mlx.mlx_ptr = mlx_init()) == NULL)
		return (-1);
	if ((mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, render[0], render[1], "miniRT")) == NULL)
		return (-1);
	color = 0x255;
	color = color * 100 + 0x255;
	color = color * 100 + 0x255;
	int	save;
	k = 0;
//	while (i < render[0])
//	{
//		k = 0;
		while (k < render[1])
		{
			save = mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, k, i, 0xffcc99);
			k++;
		}
//		i++;
//	}
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
