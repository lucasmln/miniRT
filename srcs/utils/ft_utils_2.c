/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 15:21:10 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/30 15:14:44 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double		ft_atod(char *s)
{
	double	nb;
	int		div;
	double	temp;
	int		i;
	int		neg;

	i = 0;
	nb = 0;
	neg = 1;
	div = 1;
	if (s[i] == '-' || s[i] == '+')
		neg = (s[i++] == '-') ? -1 : 1;
	while ((s[i] <= '9' && s[i] >= '0'))
		nb = nb * 10 + (s[i++] - '0');
	if (s[i] != '.')
		return (nb * neg);
	i++;
	temp = 0.1;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb + ((s[i++] - '0') * temp);
		temp /= 10;
	}
	return (nb * neg);
}

int			ft_atoi(const char *str)
{
	long	i;
	long	negative;
	long	nb;

	i = 0;
	negative = 1;
	nb = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ') && str[i])
		i++;
	if (str[i] == '-')
	{
		negative = -negative;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (str[i] - '0') + nb * 10;
		i++;
	}
	return (nb * negative);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	int				res;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		res = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (res != 0)
			return (res);
		i++;
	}
	return (0);
}

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				res;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		res = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (res != 0)
			return (res);
		i++;
	}
	return (0);
}
