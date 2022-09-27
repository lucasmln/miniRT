/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:46:04 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/19 14:59:33 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int		ft_check_valid_obj(char *s, int i)
{
	if (ft_strncmp(&s[i], "pl", 2) == 0 || ft_strncmp(&s[i], "sp", 2) == 0 ||
	ft_strncmp(&s[i], "sq", 2) == 0 || ft_strncmp(&s[i], "cy", 2) == 0 ||
	ft_strncmp(&s[i], "tr", 2) == 0 || ft_strncmp(&s[i], "cu", 2) == 0)
		return (1);
	return (0);
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

void	skip_comment(char *s, int *i)
{
	while (s[*i] && (s[*i] == '#' || s[*i] == ' ' || s[*i] == '\n'))
	{
		while (s[*i] && s[*i] != '\n')
			(*i)++;
		(*i)++;
	}
}

int		ft_check_file(char *s)
{
	int		i;

	i = 0;
	skip_comment(s, &i);
	if (s[i] == 'R' || s[i] == 'A')
	{
		if ((i = ft_ambience_and_res(s, i)) == -1)
			return (-1);
	}
	else
		return (-1);
	skip_comment(s, &i);
	if (s[i] == 'c' || s[i] == 'l')
		if ((i = ft_cam_and_light(s, i)) == -1)
			return (-1);
	skip_comment(s, &i);
	if (ft_check_valid_obj(s, i) == 1)
		if ((i = ft_objet(s, i)) == -1)
			return (-1);
	return (0);
}
