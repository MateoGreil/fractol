/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreil <mgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 12:11:06 by mgreil            #+#    #+#             */
/*   Updated: 2018/02/06 09:16:08 by mgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_color_shift(int start, int end, int nb_color)
{
	char	dr;
	char	dg;
	char	db;
	int		shift;

	if (nb_color == 0)
		nb_color++;
	dr = (start / 256 / 256 % 256 - end / 256 / 256 % 256) / nb_color;
	dg = (start / 256 % 256 - end / 256 % 256) / nb_color;
	db = (start % 256 - end % 256) / nb_color;
	shift = dr * 256 * 256 + dg * 256 + db;
	return (shift);
}

int			psyche(int i, int precision)
{
	int color;

	color = 0x00000000;
	if (i == precision)
		return (0x00FFFFFF);
	return (color + get_color_shift(0x00000000, 0x00FFFFFF, NB_COLORS) *
			i / precision);
}

int			get_color(int i, int precision)
{
	int color[8];

	color[0] = 0x000044E5;
	color[1] = 0x002721E8;
	color[2] = 0x008043EC;
	color[3] = 0x00C566F0;
	color[4] = 0x00F38BF2;
	color[5] = 0x00F7B0DF;
	color[6] = 0x00FBD7E3;
	color[7] = 0x00FFFFFF;
	return (color[(int)((double)i / (double)precision * 7)]);
}
