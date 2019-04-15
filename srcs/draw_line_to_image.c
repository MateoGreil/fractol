/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_to_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 22:52:28 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/06 09:16:36 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	swap_point(t_point *p1, t_point *p2)
{
	t_point	tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

static void	draw_line_case_one(t_img *img, t_point p1, t_point p2)
{
	int	x;
	int color;

	if (p1.x > p2.x)
		swap_point(&p1, &p2);
	x = p1.x;
	color = 0x00FFFFFF;
	while (x <= p2.x)
	{
		put_pixel_to_image(img, x, p1.y + ((p2.y - p1.y) * (x - p1.x)) /
				(p2.x - p1.x), color);
		x++;
	}
}

static void	draw_line_case_two(t_img *img, t_point p1, t_point p2)
{
	int	y;
	int color;

	if (p1.y > p2.y)
		swap_point(&p1, &p2);
	y = p1.y;
	color = 0x00FFFFFF;
	while (y <= p2.y)
	{
		put_pixel_to_image(img, p1.x + ((p2.x - p1.x) * (y - p1.y)) /
				(p2.y - p1.y), y, color);
		y++;
	}
}

void		draw_line_to_image(t_img *img, t_point p1, t_point p2)
{
	if (fabs(p2.x - p1.x) >= fabs(p2.y - p1.y))
	{
		draw_line_case_one(img, p1, p2);
	}
	else
	{
		draw_line_case_two(img, p1, p2);
	}
}
