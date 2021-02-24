/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_vertex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:13:35 by skoskine          #+#    #+#             */
/*   Updated: 2021/02/24 11:04:16 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static t_vertex	rotate_vertex(t_vertex vertex, t_vertex origin, float angle)
{
	t_vertex	tmp;
	float		rotation_angle;

	tmp.x = vertex.x;
	tmp.y = vertex.y;
	rotation_angle = angle * M_PI / 180;
	vertex.x = (tmp.x - origin.x) * cos(rotation_angle) -
	(tmp.y - origin.y) * sin(rotation_angle) + origin.x;
	vertex.y = (tmp.y - origin.y) * cos(rotation_angle) +
	(tmp.x - origin.x) * sin(rotation_angle) + origin.y;
	return (vertex);
}

static t_vertex	transform_isometric_vertex(t_vertex vertex, float zoom)
{
	t_vertex	tmp;
	float		isometric_angle;

	isometric_angle = 30 * M_PI / 180;
	tmp.x = vertex.x;
	tmp.y = vertex.y;
	vertex.x = (tmp.x - tmp.y) * cos(isometric_angle);
	vertex.y = -vertex.z * zoom + (tmp.x + tmp.y) * sin(isometric_angle);
	return (vertex);
}

t_vertex		transform_vertex(t_vertex vertex, t_vertex start, t_map *map)
{
	t_vertex center;

	center.x = map->max_width / 2;
	center.y = map->height / 2;
	if (map->rotation != 0)
		vertex = rotate_vertex(vertex, center, map->rotation);
	vertex.x = vertex.x * map->zoom + start.x;
	vertex.y = vertex.y * map->zoom + start.y;
	vertex.z = vertex.z * (1 + map->move_z / 100);
	if (map->isometric)
		vertex = transform_isometric_vertex(vertex, map->zoom);
	return (vertex);
}
