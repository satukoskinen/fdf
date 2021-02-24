/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 19:13:37 by skoskine          #+#    #+#             */
/*   Updated: 2021/02/23 16:27:05 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

void	free_str_arr(char **arr)
{
	size_t i;

	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

float	get_initial_zoom(t_map *map)
{
	float	zoom;

	if ((float)map->max_width / map->height >= (float)WIN_WIDTH / WIN_HEIGHT)
		zoom = ((float)WIN_WIDTH / 2) / map->max_width;
	else
		zoom = ((float)WIN_HEIGHT / 2) / map->max_width;
	return (zoom);
}

int		get_vertex_colour(char *str, int *has_colour)
{
	int			i;
	int			colour;

	i = 0;
	while (str[i] != ',' && str[i] != '\0')
		i++;
	if (str[i] == ',')
	{
		*has_colour = 1;
		colour = ft_atoi_base(&str[i + 1], 16);
	}
	else
	{
		*has_colour = 0;
		colour = 0;
	}
	return (colour);
}
