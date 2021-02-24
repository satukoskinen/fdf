/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:28:51 by skoskine          #+#    #+#             */
/*   Updated: 2021/02/24 12:01:00 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <math.h>

static void		put_pixel_to_image(t_image *img, int x, int y, int colour)
{
	char			*dst;
	unsigned int	*colour_dst;

	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x *
		(img->bits_per_pixel / 8));
		colour_dst = (unsigned int*)dst;
		*colour_dst = colour;
	}
}

static int		calculate_colour(float z)
{
	float	scale;
	int		r;
	int		g;
	int		b;

	if (fabsf(z) > HEIGHT_COLOR_SCALE)
		scale = 0.0;
	else
		scale = (1.0 - fabsf(z) / HEIGHT_COLOR_SCALE);
	if (z >= 0.0)
	{
		r = 255;
		g = 255 * scale;
		b = 255 * scale;
	}
	else
	{
		r = 255 * scale;
		g = 255 * scale;
		b = 255;
	}
	return ((r & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (b & 0x0ff);
}

static int		get_line_colour(t_vertex start, t_vertex end)
{
	if (start.has_colour && end.has_colour && start.colour == end.colour)
		return (start.colour);
	else
		return (calculate_colour((start.z + end.z) / 2));
}

void			draw_line(t_vertex start, t_vertex end, t_image *img)
{
	float	dx;
	float	dy;
	float	s;
	float	i;
	int		line_colour;

	line_colour = get_line_colour(start, end);
	dx = end.x - start.x;
	dy = end.y - start.y;
	if (fabsf(dx) >= fabsf(dy))
		s = fabsf(dx);
	else
		s = fabsf(dy);
	if (s == 0)
		return ;
	dx = dx / s;
	dy = dy / s;
	i = 0;
	while (i++ <= s)
	{
		put_pixel_to_image(img, start.x, start.y, line_colour);
		start.x += dx;
		start.y += dy;
	}
}
