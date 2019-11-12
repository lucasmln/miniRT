/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:08:52 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/12 18:02:54 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_struct.h"
#include "miniRT.h"
#include "libft/libft.h"

int		ft_get_coord(double coord[], char *s, int i)
{
	int		k;

	k = 0;
	while (k <= 2)
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		coord[k] = ft_atod(&s[i]);
		while (s[i] >= '0' && s[i] <= '9')
			i++;
		if (s[i] == '.')
			i++;
		while (s[i] >= '0' && s[i] <= '9')
			i++;
		if (s[i] == ',' && k != 2)
			i++;
		k++;
	}
	return (i);
}

int		ft_get_color(int color[], char *s, int i)
{
	int		k;

	k = 0;
	while (k <= 2)
	{
		color[k] = ft_atoi(&s[i]);
		i += ft_strlen_nb(color[k]);
		if (s[i] != ',' && k <= 1)
			return (-1);
		i++;
		k++;
	}
	while (--k >= 0)
		if (color[k] > 255 || color[k] < 0)
			return (-1);
	return (i);
}

int		ft_strlen_nb(int nb)
{
	int		len;
	long	nbr;

	nbr = (nb < 0) ? -nb : nb;
	len = (nb == 0) ? 1: 0;
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}
