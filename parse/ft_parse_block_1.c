/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_block_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:06:11 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/25 12:40:10 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../libft/libft.h"

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
	double	aux[3];

	while (s[i] == ' ')
		i++;
	if (s[i] < '0' || s[i] > '9')
		return (-1);
	data->ambience.ratio = ft_atod(&s[i]);
	if (data->ambience.ratio < 0.0 || data->ambience.ratio > 1.0)
		return (-1);
	i = ft_pass_double(s, i);
	k = -1;
	while (s[i] == ' ')
		i++;
	i = ft_get_color(aux, s, i);
	ft_set_ori(&data->ambience.color, aux);
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
		i = ft_get_render(data, s, i + 1);
	}
	else
		i = ft_get_ambience(data, s, i + 1);
	if (i == -1 || (s[i] == 'R' && check == 1) || (check == 0 && s[i] == 'A'))
		return (-1);
	i = (check == 1) ? ft_get_ambience(data, s, i + 1) : ft_get_render(data, s, i + 1);
	check += 2;
	return (i);
}

