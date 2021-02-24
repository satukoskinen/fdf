/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 14:11:08 by skoskine          #+#    #+#             */
/*   Updated: 2021/02/23 16:28:01 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "fdf.h"
#include "libft.h"

static t_vertex	get_vertex(char *input, int i, int j)
{
	t_vertex vertex;

	vertex.y = i;
	vertex.x = j;
	vertex.z = ft_atoi(input);
	if (vertex.z == 0 && !(ft_isdigit(input[0])) &&
	input[0] != '-' && input[0] != '+')
		vertex.is_empty = 1;
	else
		vertex.is_empty = 0;
	vertex.w = 0;
	vertex.colour = get_vertex_colour(input, &vertex.has_colour);
	return (vertex);
}

static t_vertex	*parse_row(char *line, t_map *map, int i)
{
	char		**char_arr;
	t_vertex	*row;
	int			j;

	if (!(char_arr = ft_strsplit(line, ' ')))
		return (NULL);
	j = 0;
	while (char_arr[j] != NULL)
		j++;
	map->row_width[i] = j;
	map->max_width = (map->max_width > j) ? map->max_width : j;
	if (!(row = (t_vertex*)malloc(sizeof(t_vertex) * j)))
		return (NULL);
	j = 0;
	while (char_arr[j] != NULL)
	{
		row[j] = get_vertex(char_arr[j], i, j);
		j++;
	}
	free_str_arr(char_arr);
	return (row);
}

static t_map	*init_map(int arr_size)
{
	t_map		*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	ft_memset(map, 0, sizeof(t_map));
	if (!(map->arr = (t_vertex**)malloc(sizeof(t_vertex*) * arr_size)))
	{
		free(map);
		return (NULL);
	}
	if (!(map->row_width = (int*)malloc(sizeof(int) * arr_size)))
	{
		free(map);
		free(map->arr);
		return (NULL);
	}
	return (map);
}

static t_map	*double_map_size(t_map *old_map, int *arr_size)
{
	t_map	*new_map;
	int		i;

	if (!(new_map = init_map(*arr_size * 2)))
		return (NULL);
	new_map->max_width = old_map->max_width;
	ft_memcpy(new_map->row_width, old_map->row_width, *arr_size * sizeof(int));
	i = 0;
	while (i < *arr_size)
	{
		new_map->arr[i] = old_map->arr[i];
		i++;
	}
	free(old_map->arr);
	free(old_map->row_width);
	free(old_map);
	*arr_size *= 2;
	return (new_map);
}

t_map			*read_input(char *file, int arr_size)
{
	t_map	*map;
	char	*line;
	int		fd;
	int		ret;
	int		i;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if ((map = init_map(arr_size)) == NULL)
		return (NULL);
	i = 0;
	while (((ret = get_next_line(fd, &line)) > 0))
	{
		if (i == arr_size && !(map = double_map_size(map, &arr_size)))
			return (NULL);
		if (!(map->arr[i] = parse_row(line, map, i)))
			exit(1);
		i++;
		free(line);
	}
	if (ret == -1)
		exit(1);
	map->height = i;
	return (map);
}
