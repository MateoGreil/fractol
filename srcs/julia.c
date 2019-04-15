/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 17:18:53 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/06 09:17:59 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	is_fractal(t_env e, t_im c, t_im z)
{
	int		i;
	double	tmp;

	i = 0;
	while (z.r * z.r + z.i * z.i < 4 && i < e.precision)
	{
		tmp = z.r;
		z.r = z.r * z.r - z.i * z.i + c.r;
		z.i = 2 * z.i * tmp + c.i;
		i++;
	}
	return (i);
}

static void	draw_fractal(t_env e, int x, int y)
{
	int		color;
	t_im	c;
	t_im	z;

	c.r = -0.8 + (0.6 / ((double)e.mouse_pos.x / (double)WIN_SIZE_X));
	c.i = 0.27015 / ((double)e.mouse_pos.y / (double)WIN_SIZE_Y);
	z.r = x / e.zoom + e.x_start;
	z.i = y / e.zoom + e.y_start;
	if (e.psyche_mode == DISACTIVATED)
		color = get_color(is_fractal(e, c, z), e.precision);
	else
		color = psyche(is_fractal(e, c, z), e.precision);
	put_pixel_to_image(&e.img, x, y, color);
}

static void	*julia_thread(void *e)
{
	int	x;
	int	y;
	int	x_end;

	x = ((t_env *)e)->x_screen_start;
	x_end = ((t_env *)e)->x_screen_start + WIN_SIZE_X / NB_THREADS;
	while (x < x_end)
	{
		y = 0;
		while (y < WIN_SIZE_Y)
		{
			draw_fractal((*(t_env *)e), x, y);
			y++;
		}
		x++;
	}
	return (NULL);
}

void		julia(t_env *e)
{
	int			i;
	t_env		env[NB_THREADS];
	pthread_t	thread[NB_THREADS];

	i = 0;
	while (i < NB_THREADS)
	{
		ft_memcpy((void*)&env[i], (void*)e, sizeof(t_env));
		env[i].x_screen_start = WIN_SIZE_X / NB_THREADS * i;
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		if (pthread_create(&thread[i], NULL, &julia_thread, &env[i]))
			return ;
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}
