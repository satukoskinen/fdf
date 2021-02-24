/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 13:01:39 by skoskine          #+#    #+#             */
/*   Updated: 2021/02/24 10:36:35 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define KEY_ESC 65307

# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_DOWN 65364

# define KEY_A 97
# define KEY_W 119
# define KEY_S 115
# define KEY_D 100

# define KEY_Z 122
# define KEY_X 120

# define KEY_P 112
# define KEY_R 114

# define KEY_I 105
# define KEY_O 111

# define WIN_WIDTH 700
# define WIN_HEIGHT 700

# define HEIGHT_COLOR_SCALE 50

typedef struct	s_vertex
{
	float		x;
	float		y;
	float		z;
	float		w;
	int			has_colour;
	int			colour;
	int			is_empty;
}				t_vertex;

typedef struct	s_map
{
	t_vertex	**arr;
	int			*row_width;
	int			max_width;
	int			height;
	int			isometric;
	float		zoom;
	float		move_x;
	float		move_y;
	float		move_z;
	int			rotation;
}				t_map;

typedef struct	s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_width;
	int			win_height;
}				t_window;

typedef struct	s_image
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct	s_fdf
{
	t_image		img;
	t_window	win;
	t_map		*map;
}				t_fdf;

t_map			*read_input(char *file, int arr_size);
void			free_str_arr(char **arr);
int				get_vertex_colour(char *str, int *has_colour);
int				key_action(int key, t_fdf *fdf);
int				close_window(t_fdf *fdf);
float			get_initial_zoom(t_map *map);
t_vertex		transform_vertex(t_vertex vertex, t_vertex start, t_map *map);
void			draw_line(t_vertex start, t_vertex end, t_image *img);
int				draw_map_to_image(t_fdf *fdf);

#endif
