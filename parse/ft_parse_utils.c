/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:14:10 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/21 17:47:00 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../libft/libft.h"

int		ft_get_coord(double coord[], char *s, int i)
{
	int		k;

	k = 0;

	while (k <= 2)
	{
		if ((s[i] < '0' || s[i] > '9') && (s[i] == '-' && (s[i] < '0' && s[i] > '9')))
			return (-1);
		coord[k] = ft_atod(&s[i]);
		if (coord[k] < 0.0)
			i++;
		while (s[i] >= '0' && s[i] <= '9')
			i++;
		if (s[i] == '.')
			i++;
		while (s[i] >= '0' && s[i] <= '9')
			i++;
		if (s[i] == ',' && k < 2)
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
		while (s[i] == ' ')
			i++;
		color[k] = ft_atoi(&s[i]);
		i += ft_strlen_nb(color[k]);
		if (s[i] != ',' && k < 2)
		{
			return (-1);
			}
		i++;
		k++;
	}
	while (--k >= 0)
		if (color[k] > 255 || color[k] < 0)
			return (-1);
	return (i - 1);
}

int		ft_get_dir(double dir[], const char *s, int i)
{
	int		k;

	k = 0;
	while (k <= 2)
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '-')
			i++;
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		dir[k] = ft_atod((char *)&s[i]);
		if (dir[k] > 1.0 || dir[k] < -1.0)
			return (-1);
		if (dir[k] < 0.0)
			i++;
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

int		ft_pass_double(char *s, int i)
{
	if (s[i] == '-' && s[i + 1] <= '9' && s[i + 1] >= '0')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == '.')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	return (i);
}
