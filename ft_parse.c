/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:08:10 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/12 18:10:44 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/libft.h"
#include "miniRT_struct.h"
#include "miniRT.h"

int		ft_check_file(t_data *data, char *s)
{
	int		i;

	i = 0;
	if (s[i] == 'R' || s[i] == 'A')
		if ((i = ft_ambience_and_res(data, s, i)) == -1)
			return (-1);
	while (s[i] == '\n')
		i++;
	if (s[i] == 'c' || s[i] == 'l')
		if ((i = ft_cam_and_light(data, s, i)));

	}
}
