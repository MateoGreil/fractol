/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 17:01:27 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/06 09:08:31 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <pthread.h>

# define WIN_SIZE_X 1080
# define WIN_SIZE_Y 720

# define KEY_PRESS 2
# define MOUSE_PRESS 4
# define MOUSE_MOVE 6
# define EXIT_PRESS 17
# define EXIT_PRESS_MASK 0L
# define KEY_PRESS_MASK (1L << 6)
# define MOUSE_PRESS_MASK (1L << 2)
# define MOUSE_MOVE_MASK (1L << 6)

# define KEY_C 8
# define KEY_LESS 27
# define KEY_MORE 24
# define KEY_L 37
# define KEY_ECHAP 53
# define KEYPAD_MORE 69
# define KEYPAD_LESS 78
# define KEYPAD_LEFT 123
# define KEYPAD_RIGHT 124
# define KEYPAD_DOWN 125
# define KEYPAD_UP 126

# define MOUSE_1 1
# define MOUSE_2 2
# define MOUSE_WHEEL_DOWN 4
# define MOUSE_WHEEL_UP 5

# define BLUE  				0x000092FF
# define GREEN_DARK		0x00114912
# define GREEN				0x001D8D1F
# define GREEN_LIGHT	0x002EDF31
# define BROWN_LIGHT	0x00DF902E
# define BROWN				0x0098621E
# define BROWN_DARK		0x00563712
# define WHITE				0x00FFFFFF

# define DEFAULT_ZOOM 300
# define DEFAULT_PRECISION 50
# define X_START_MANDELBROT -2.5
# define Y_START_MANDELBROT -1.2
# define X_START_JULIA -1.8
# define Y_START_JULIA -1.2
# define X_START_BURNINGSHIP -2.2
# define Y_START_BURNINGSHIP -1.8

# define MANDELBROT 1
# define JULIA 2
# define BURNINGSHIP 3
# define TREE 4

# define ACTIVATED 1
# define DISACTIVATED -1

# define NB_THREADS 8
# define NB_COLORS 3

typedef struct	s_im
{
	double	r;
	double	i;
}				t_im;

typedef struct	s_point
{
	double	x;
	double	y;
	int		color;
}				t_point;

typedef struct	s_img
{
	void	*img;
	char	*data;
	int		size_x;
	int		size_y;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_point	mouse_pos;
	int		mouse_lock;
	int		psyche_mode;
	int		fractal;
	double	zoom;
	int		x_screen_start;
	double	x_start;
	double	y_start;
	double	x_end;
	double	y_end;
	int		precision;
}				t_env;

t_img			new_image(void *mlx, int img_size_x, int img_size_y);
void			del_image(void *mlx, t_img *img);
void			put_pixel_to_image(t_img *img, int x, int y, int color);
void			put_text_to_screen(t_env *e);
void			draw_line_to_image(t_img *img, t_point p1, t_point p2);

int				get_color(int i, int precision);
int				psyche(int i, int precision);

int				key_hook(int keycode, t_env *env);
int				mouse_hook(int mousecode, int x, int y, t_env *e);
int				mouse_move(int x, int y, t_env *e);

void			fractol(t_env e);
void			mandelbrot(t_env *e);
void			julia(t_env *e);
void			burningship(t_env *e);

#endif
