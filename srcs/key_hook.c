/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:18:08 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/06 09:22:18 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom(t_env *e, int keycode)
{
	if (keycode == KEYPAD_MORE)
	{
		e->zoom *= 1.1;
		e->x_start = ((1.1 * (e->x_end - e->x_start)) * 0.5) -
			((e->x_end - e->x_start) * 0.5) + e->x_start;
		e->y_start = ((1.1 * (e->y_end - e->y_start)) * 0.5) -
			((e->y_end - e->y_start) * 0.5) + e->y_start;
		e->x_end = e->x_start + WIN_SIZE_X / e->zoom;
		e->y_end = e->y_start + WIN_SIZE_Y / e->zoom;
		e->precision++;
	}
	else if (e->zoom > 2)
	{
		e->zoom /= 1.1;
		e->x_start = (((e->x_end - e->x_start)) * 0.5 / 1.1) -
			((e->x_end - e->x_start) * 0.5) + e->x_start;
		e->y_start = (((e->y_end - e->y_start)) * 0.5 / 1.1) -
			((e->y_end - e->y_start) * 0.5) + e->y_start;
		e->x_end = e->x_start + WIN_SIZE_X / e->zoom;
		e->y_end = e->y_start + WIN_SIZE_Y / e->zoom;
		e->precision--;
	}
	fractol(*e);
}

static void	precise(t_env *e, int keycode)
{
	if (keycode == KEY_MORE)
		e->precision += 1;
	else
		e->precision -= 1;
	fractol(*e);
}

static void	translate(t_env *e, int keycode)
{
	if (keycode == KEYPAD_UP)
	{
		e->y_start += (double)30 / e->zoom;
		e->y_end += (double)30 / e->zoom;
	}
	else if (keycode == KEYPAD_DOWN)
	{
		e->y_start -= (double)30 / e->zoom;
		e->y_end -= (double)30 / e->zoom;
	}
	else if (keycode == KEYPAD_RIGHT)
	{
		e->x_start -= (double)30 / e->zoom;
		e->x_end -= (double)30 / e->zoom;
	}
	else
	{
		e->x_start += (double)30 / e->zoom;
		e->x_end += (double)30 / e->zoom;
	}
	fractol(*e);
}

int			key_hook(int keycode, t_env *e)
{
	if (keycode == KEYPAD_LESS || keycode == KEYPAD_MORE)
		zoom(e, keycode);
	else if (keycode == KEY_MORE || keycode == KEY_LESS)
		precise(e, keycode);
	else if (keycode == KEY_ECHAP)
		exit(0);
	else if (keycode == KEYPAD_UP || keycode == KEYPAD_DOWN
				|| keycode == KEYPAD_LEFT || keycode == KEYPAD_RIGHT)
		translate(e, keycode);
	else if (keycode == KEY_L)
		e->mouse_lock *= -1;
	else if (keycode == KEY_C)
	{
		e->psyche_mode *= -1;
		fractol(*e);
	}
	return (0);
}
