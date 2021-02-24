/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 09:11:50 by skoskine          #+#    #+#             */
/*   Updated: 2021/02/24 11:04:02 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

void			draw_line_to_image(t_vertex start, t_vertex end,
t_vertex map_start, t_fdf *fdf)
{
	start = transform_vertex(start, map_start, fdf->map);
	end = transform_vertex(end, map_start, fdf->map);
	draw_line(start, end, &fdf->img);
}

static t_vertex	get_start_coordinates(t_window win, t_map *map)
{
	t_vertex map_start;

	map_start.x = ((float)win.win_width / 2) -
	((float)map->max_width * map->zoom / 2) + map->move_x;
	map_start.y = ((float)win.win_height / 2) -
	((float)map->height * map->zoom / 2) + map->move_y;
	return (map_start);
}

static void		reset_image(t_image *img, t_window win)
{
	ft_memset(img->addr, 0, win.win_height * win.win_height * 4);
}

int				draw_map_to_image(t_fdf *fdf)
{
	t_vertex	**map;
	t_vertex	map_start;
	int			i;
	int			j;

	reset_image(&fdf->img, fdf->win);
	map = fdf->map->arr;
	map_start = get_start_coordinates(fdf->win, fdf->map);
	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		while (j < fdf->map->row_width[i])
		{
			if (j + 1 < fdf->map->row_width[i] &&
			!map[i][j].is_empty && !map[i][j + 1].is_empty)
				draw_line_to_image(map[i][j], map[i][j + 1], map_start, fdf);
			if (i + 1 < fdf->map->height && j < fdf->map->row_width[i + 1]
			&& !map[i][j].is_empty && !map[i + 1][j].is_empty)
				draw_line_to_image(map[i][j], map[i + 1][j], map_start, fdf);
			j++;
		}
		i++;
	}
	return (0);
}
