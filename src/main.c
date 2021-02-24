/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 13:01:36 by skoskine          #+#    #+#             */
/*   Updated: 2021/02/24 11:03:54 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf.h"
#include "mlx.h"

#define ARR_SIZE 500

t_map		*init_map(char *file)
{
	t_map	*map;

	if (!(map = read_input(file, ARR_SIZE)))
		return (NULL);
	map->zoom = get_initial_zoom(map);
	return (map);
}

t_window	init_window(void)
{
	t_window	win;

	if ((win.mlx_ptr = mlx_init()) == NULL)
		exit(1);
	win.win_width = WIN_WIDTH;
	win.win_height = WIN_HEIGHT;
	if ((win.win_ptr = mlx_new_window(win.mlx_ptr, win.win_width,
	win.win_height, "fdf")) == NULL)
		exit(1);
	return (win);
}

t_image		init_image(t_window win)
{
	t_image	img;

	img.img_ptr = mlx_new_image(win.mlx_ptr, win.win_width, win.win_height);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
	&img.line_length, &img.endian);
	return (img);
}

int			main(int argc, char **argv)
{
	t_fdf		*fdf;

	if (argc != 2)
		return (1);
	if (!(fdf = (t_fdf*)malloc(sizeof(t_fdf))))
		return (1);
	if (!(fdf->map = init_map(argv[1])))
		return (1);
	fdf->win = init_window();
	fdf->img = init_image(fdf->win);
	draw_map_to_image(fdf);
	mlx_put_image_to_window(fdf->win.mlx_ptr, fdf->win.win_ptr,
	fdf->img.img_ptr, 0, 0);
	mlx_hook(fdf->win.win_ptr, 02, 1L << 0, key_action, (void*)fdf);
	mlx_hook(fdf->win.win_ptr, 33, 0, close_window, (void*)fdf);
	mlx_loop(fdf->win.mlx_ptr);
	return (0);
}
