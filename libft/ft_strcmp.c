/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 12:09:23 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/22 12:12:28 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
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
