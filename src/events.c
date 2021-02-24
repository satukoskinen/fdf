/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:31:39 by skoskine          #+#    #+#             */
/*   Updated: 2021/02/24 11:03:46 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include "mlx.h"

int			close_window(t_fdf *fdf)
{
	int	i;

	mlx_destroy_window(fdf->win.mlx_ptr, fdf->win.win_ptr);
	mlx_destroy_image(fdf->win.mlx_ptr, fdf->img.img_ptr);
	mlx_destroy_display(fdf->win.mlx_ptr);
	free(fdf->map->row_width);
	i = 0;
	while (i < fdf->map->height)
		free(fdf->map->arr[i++]);
	free(fdf->map->arr);
	free(fdf->map);
	free(fdf);
	exit(0);
}

static void	reset_image(t_fdf *fdf)
{
	fdf->map->isometric = 0;
	fdf->map->zoom = get_initial_zoom(fdf->map);
	fdf->map->move_x = 0;
	fdf->map->move_y = 0;
	fdf->map->move_z = 0;
}

int			key_action(int key, t_fdf *fdf)
{
	if (key == KEY_ESC)
		close_window(fdf);
	else if (key == KEY_R)
		reset_image(fdf);
	else if (key == KEY_P)
		fdf->map->isometric = fdf->map->isometric ? 0 : 1;
	else if (key == KEY_X || key == KEY_Z)
		fdf->map->zoom *= (key == KEY_X) ? 1.05 : 0.95;
	else if (key == KEY_RIGHT || key == KEY_LEFT)
		fdf->map->move_x += (key == KEY_RIGHT) ? 10 : -10;
	else if (key == KEY_DOWN || key == KEY_UP)
		fdf->map->move_y += (key == KEY_DOWN) ? 10 : -10;
	else if (key == KEY_I || key == KEY_O)
		fdf->map->move_z += (key == KEY_I) ? 5 : -5;
	else if (key == KEY_A || key == KEY_D)
		fdf->map->rotation += (key == KEY_A) ? -5 : 5;
	draw_map_to_image(fdf);
	mlx_put_image_to_window(fdf->win.mlx_ptr, fdf->win.win_ptr,
	fdf->img.img_ptr, 0, 0);
	return (0);
}
