/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_block_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:06:11 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/12 18:13:09 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "miniRT_struct.h"
#include "libft/libft.h"

int		ft_get_render(t_data *data, char *s, int i)
{
	while (s[i] == ' ')
		i++;
	if (s[i] > '9' || s[i] < '0')
		return (-1);
	data->render[0] = ft_atoi(&s[i]);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	while (s[i] == ' ')
		i++;
	if (s[i] > '9' || s[i] < '0')
		return (-1);
	data->render[1] = ft_atoi(&s[i]);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] != '\n')
		return (-1);
	i++;
	return (i);
}

int		ft_get_ambience(t_data *data, char *s, int i)
{
	int		k;

	while (s[i] == ' ')
		i++;
	if (s[i] < '0' || s[i] > '9')
		return (-1);
	data->ambience.ratio = ft_atod(&s[i]);
	if (data->ambience.ratio < 0.0 || data->ambience.ratio > 1.0)
		return (-1);
	k = 0;
	while (s[i] == ' ')
		i++;
	while (k <= 2)
	{
	if (s[i] < '0' || s[i] > '9')
			return (-1);
		data->ambience.color[k] = ft_atoi(&s[i]);
		i += ft_strlen_nb(data->ambience.color[k]);
		if (k != 2 && s[i] == ',')
			i++;
		if (data->ambience.color[k] < 0 || data->ambience.color[k] > 255)
			return (-1);
		k++;
	}
	return ((s[i++] == '\n' ? i : -1));
}


int		ft_ambience_and_res(t_data *data, char *s, int i)
{
	static int		check;

	if (check >= 2)
		return (-1);
	check = 0;
	if (s[i] == 'R')
	{
		check = 1;
		i = ft_get_render(data, s, i);
	}
	else
		i = ft_get_ambience(data, s, i);
	if (i == -1 || (s[i] != 'R' && check == 0) || (check == 1 && s[i] != 'A'))
		return (-1);
	i = (check == 1) ? ft_get_ambience(data, s, i) : ft_get_render(data, s, i);
	check += 2;
	return (i);
}

