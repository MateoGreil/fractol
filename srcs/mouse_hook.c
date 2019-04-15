/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 11:26:28 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/06 09:22:57 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom(t_env *e, double x, double y)
{
	e->zoom *= 1.1;
	e->x_start = ((1.1 * (e->x_end - e->x_start)) * (x / WIN_SIZE_X)) -
		((e->x_end - e->x_start) * (x / WIN_SIZE_X)) + e->x_start;
	e->y_start = ((1.1 * (e->y_end - e->y_start)) * (y / WIN_SIZE_Y)) -
		((e->y_end - e->y_start) * (y / WIN_SIZE_Y)) + e->y_start;
	e->x_end = e->x_start + WIN_SIZE_X / e->zoom;
	e->y_end = e->y_start + WIN_SIZE_Y / e->zoom;
	e->precision++;
}

static void	dezoom(t_env *e, double x, double y)
{
	e->zoom /= 1.1;
	e->x_start = (((e->x_end - e->x_start) / 1.1) * (x / WIN_SIZE_X)) -
		((e->x_end - e->x_start) * (x / WIN_SIZE_X)) + e->x_start;
	e->y_start = (((e->y_end - e->y_start) / 1.1) * (y / WIN_SIZE_Y)) -
		((e->y_end - e->y_start) * (y / WIN_SIZE_Y)) + e->y_start;
	e->x_end = e->x_start + WIN_SIZE_X / e->zoom;
	e->y_end = e->y_start + WIN_SIZE_Y / e->zoom;
	e->precision--;
}

int			mouse_hook(int mousecode, int x, int y, t_env *e)
{
	if (mousecode == MOUSE_1 || mousecode == MOUSE_WHEEL_DOWN)
		zoom(e, (double)x, (double)y);
	else if ((mousecode == MOUSE_2 || mousecode == MOUSE_WHEEL_UP)
			&& e->zoom > 2)
		dezoom(e, (double)x, (double)y);
	fractol(*e);
	return (0);
}
