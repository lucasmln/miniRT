/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:22:36 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/26 15:03:44 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int		ft_set_color(t_vect3 c)
{
	return (((((int)c.x << 8) + (int)c.y) << 8) + (int)c.z);

}

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
