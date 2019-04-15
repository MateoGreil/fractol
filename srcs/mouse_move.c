/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 11:26:24 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/06 09:21:55 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_move(int x, int y, t_env *e)
{
	if ((e->fractal == TREE || e->fractal == JULIA) && e->mouse_lock ==
			DISACTIVATED && x > 0 && x < WIN_SIZE_X && y > 0 && y < WIN_SIZE_Y)
	{
		e->mouse_pos.x = x;
		e->mouse_pos.y = y;
		fractol(*e);
	}
	return (0);
}
