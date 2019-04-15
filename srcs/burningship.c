/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:11:46 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/06 09:13:10 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	is_fractal(t_env e, t_im c, t_im z)
{
	double	tmp;
	int		i;

	i = 0;
	while (z.r * z.r + z.i * z.i < 4 && i < e.precision)
	{
		tmp = z.r * z.r - z.i * z.i + c.r;
		z.i = fabs(2 * z.r * z.i) + c.i;
		z.r = tmp;
		i++;
	}
	return (i);
}

static void	draw_fractal(t_env e, int x, int y)
{
	int		color;
	t_im	c;
	t_im	z;

	c.r = e.x_start + (double)x / e.zoom;
	c.i = e.y_start + (double)y / e.zoom;
	z.r = 0;
	z.i = 0;
	if (e.psyche_mode == DISACTIVATED)
		color = get_color(is_fractal(e, c, z), e.precision);
	else
		color = psyche(is_fractal(e, c, z), e.precision);
	put_pixel_to_image(&e.img, x, y, color);
}

static void	*burningship_thread(void *e)
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

void		burningship(t_env *e)
{
	pthread_t	thread[NB_THREADS];
	t_env		env[NB_THREADS];
	int			i;

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
		if (pthread_create(&thread[i], NULL, &burningship_thread, &env[i]))
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
