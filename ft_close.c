/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:20:57 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/20 15:53:04 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"

int		esc_key(int key, void *p)
{
	if (key == 0x35)
		exit (0);
}

int		close_window(int button,int x,int y, void *p)
{
	if (button == 1 && x == 0 && y == 0)
		exit(0);
printf("Mouse in Win1, button %d at %dx%d.\n",button,x,y);
}
