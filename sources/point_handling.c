/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <nbunn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:13:16 by nbunn             #+#    #+#             */
/*   Updated: 2017/04/20 16:55:10 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		scale_points(t_draw *points, size_t point_tot, t_max max)
{
	size_t	i;
	i = 0;
	while (i < point_tot)
	{
		if ((WIDTH / max.x) < 2)
			points[i].x = points[i].x;
		else
			points[i].x = (points[i].x * ((WIDTH / 2) / max.x));
		if ((HEIGHT / max.y) < 2)
			points[i].y = points[i].y;
		else
			points[i].y = (points[i].y * ((HEIGHT / 2) / max.y));
		if (points[i].z != 0)
		{
			if (WIDTH > HEIGHT)
				points[i].z = (points[i].z * ((HEIGHT / 2) / max.z)) / 4;
			else
				points[i].z = (points[i].z * ((WIDTH / 2) / max.z)) / 4;
		}
		i++;
	}
}

void		scale_points_again(t_draw *points, size_t point_tot, t_max max)
{
	size_t	i;

	i = 0;
	while (i < point_tot)
	{
		if ((WIDTH / max.x) < 2)
			points[i].x += (WIDTH / 10);
		else
			points[i].x += (WIDTH / 4);
		if ((HEIGHT / max.y) < 2)
			points[i].y += (HEIGHT / 10);
		else
			points[i].y += (HEIGHT / 4);
		i++;
	}
}

static int	getpointcolor(t_draw point, t_max max)
{
	int		color;
	float	ratio;

	ratio = ((float)point.z / (float)max.z);
	if (ratio < 0.1)
		ratio = 0.0;
	if (ratio > 1.0)
		ratio = 1.0;
	ratio *= 65535;
	color = 16777215 - (int)ratio;
	return (color);
}

t_draw		setuppoint(int **fdf_file, int coord[], int direction, t_max max)
{
	t_draw	point;
	int		adj_x;
	int		adj_y;

	adj_x = max.x / 2;
	adj_y = max.y / 2;

	point.x = coord[1] - adj_x;
	point.y = coord[0] - adj_y;
	point.z = fdf_file[coord[0]][coord[1]];
	point.color = getpointcolor(point, max);
	if (direction == 10)
		point.direction = 10;
	else if (direction == 11)
		point.direction = 11;
	else
		point.direction = 1;
	return (point);
}

t_draw		*getpoints(int **fdf_file, size_t point_tot, t_max max)
{
	t_draw	*points;
	int		i;
	int		j;
	size_t	index;
	int		coord[2];

	i = -1;
	index = 0;
	points = (t_draw*)malloc(sizeof(t_draw) * point_tot);
	while (++i < max.y && index <= point_tot)
	{
		j = -1;
		while (++j < max.x && index <= point_tot)
		{
			coord[0] = i;
			coord[1] = j;
			if ((i + 1) != max.y && (j + 1) != max.x)
				points[index++] = setuppoint(fdf_file, coord, 11, max);
			else if ((j + 1) == max.x && (i + 1) != max.y)
				points[index++] = setuppoint(fdf_file, coord, 10, max);
			else
				points[index++] = setuppoint(fdf_file, coord, 1, max);
		}
	}
	return (points);
}
