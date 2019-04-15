/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 11:16:27 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/06 09:19:51 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_fractal(char *str)
{
	if (ft_strcmp(str, "mandelbrot") == 0)
		return (MANDELBROT);
	else if (ft_strcmp(str, "julia") == 0)
		return (JULIA);
	else if (ft_strcmp(str, "tree") == 0)
		return (TREE);
	else if (ft_strcmp(str, "burningship") == 0)
		return (BURNINGSHIP);
	return (0);
}

void		fractol(t_env e)
{
	e.img = new_image(e.mlx, WIN_SIZE_X, WIN_SIZE_Y);
	if (e.fractal == MANDELBROT)
	{
		mandelbrot(&e);
	}
	else if (e.fractal == JULIA)
	{
		julia(&e);
	}
	else if (e.fractal == BURNINGSHIP)
	{
		burningship(&e);
	}
	mlx_put_image_to_window(e.mlx, e.win, e.img.img, 0, 0);
	del_image(e.mlx, &(e.img));
	put_text_to_screen(&e);
}

static void	init_fractal(t_env *e)
{
	e->mouse_lock = DISACTIVATED;
	e->zoom = DEFAULT_ZOOM;
	if (e->fractal == MANDELBROT)
	{
		e->x_start = X_START_MANDELBROT;
		e->x_end = e->x_start + WIN_SIZE_X / e->zoom;
		e->y_start = Y_START_MANDELBROT;
		e->y_end = e->y_start + WIN_SIZE_Y / e->zoom;
	}
	else if (e->fractal == JULIA)
	{
		e->x_start = X_START_JULIA;
		e->x_end = e->x_start + WIN_SIZE_X / e->zoom;
		e->y_start = Y_START_JULIA;
		e->y_end = e->y_start + WIN_SIZE_Y / e->zoom;
	}
	else if (e->fractal == BURNINGSHIP)
	{
		e->x_start = X_START_BURNINGSHIP;
		e->x_end = e->x_start + WIN_SIZE_X / e->zoom;
		e->y_start = Y_START_BURNINGSHIP;
		e->y_end = e->y_start + WIN_SIZE_X / e->zoom;
	}
	else
		exit(0);
}

int			main(int ac, char **av)
{
	t_env	e;

	if (ac == 2)
	{
		e.fractal = get_fractal(av[1]);
		if (e.fractal != 0)
		{
			e.psyche_mode = DISACTIVATED;
			e.precision = DEFAULT_PRECISION;
			init_fractal(&e);
			e.mlx = mlx_init();
			e.win = mlx_new_window(e.mlx, WIN_SIZE_X, WIN_SIZE_Y, "fractol");
			fractol(e);
			mlx_hook(e.win, KEY_PRESS, KEY_PRESS_MASK, &key_hook, &e);
			mlx_hook(e.win, MOUSE_MOVE, MOUSE_MOVE_MASK, &mouse_move, &e);
			mlx_mouse_hook(e.win, &mouse_hook, &e);
			mlx_loop(e.mlx);
		}
		else
			ft_putendl("Usage : fractol [mandelbrot/julia/burningship]");
	}
	else
		ft_putendl("Usage : fractol [mandelbrot/julia/burningship]");
	return (0);
}
