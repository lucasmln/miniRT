/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 12:05:22 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/19 15:16:12 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void		ft_fill_img_bmp(char **bmp)
{
	int		x;
	int		y;
	int		i;
	int		k;

	k = 122;
	y = g_data->render[1];
	while (y-- > 0)
	{
		x = -1;
		while (++x < g_data->render[0])
		{
			i = (x * g_data->image->bpp) + (y * g_data->image->stride);
			*(*bmp + k++) = *(g_data->image->ptr + i++);
			*(*bmp + k++) = *(g_data->image->ptr + i++);
			*(*bmp + k++) = *(g_data->image->ptr + i);
		}
	}
}

void		ft_fill_header_bmp(char **bmp, unsigned int size_bmp)
{
	*(unsigned int *)*bmp = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*bmp + 2) = (size_bmp + 122);
	*(unsigned int *)(*bmp + 6) = 0u;
	*(unsigned int *)(*bmp + 10) = 122;
	*(unsigned int *)(*bmp + 14) = 122 - 14;
	*(unsigned int *)(*bmp + 18) = g_data->render[0];
	*(unsigned int *)(*bmp + 22) = g_data->render[1];
	*(unsigned int *)(*bmp + 26) = 1;
	*(unsigned int *)(*bmp + 28) = 24;
	*(unsigned int *)(*bmp + 30) = 0;
	*(unsigned int *)(*bmp + 34) = size_bmp;
	*(unsigned int *)(*bmp + 38) = 3780;
	*(unsigned int *)(*bmp + 42) = 3780;
	*(unsigned int *)(*bmp + 46) = 0;
	*(unsigned int *)(*bmp + 50) = 0;
}

void		ft_save_bmp_img(char *bmp_name)
{
	char			*bmp;
	unsigned int	i;
	int				fd;
	unsigned int	size_bmp;

	size_bmp = g_data->render[0] * g_data->render[1] * 3;
	if (!(bmp = malloc(sizeof(char) * size_bmp + 122)))
		ft_print_error(-1);
	i = 0;
	while (i < size_bmp + 122)
		bmp[i++] = 0;
	ft_fill_header_bmp(&bmp, size_bmp);
	ft_fill_img_bmp(&bmp);
	if ((fd = open(bmp_name, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		ft_print_error(-7);
	write(fd, bmp, size_bmp + 122);
	close(fd);
}

void		ft_create_bmp(char *name, int len_name)
{
	int		i;
	char	*bmp_name;

	if (!(bmp_name = malloc(sizeof(char) * (len_name + 5))))
		ft_print_error(-1);
	i = -1;
	while (i++ < len_name)
		bmp_name[i] = name[i];
	bmp_name[i++] = 'b';
	bmp_name[i++] = 'm';
	bmp_name[i++] = 'p';
	bmp_name[i] = '\0';
	ft_save_bmp_img(bmp_name);
}
