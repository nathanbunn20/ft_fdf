/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawingtools2_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <nbunn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:42:24 by nbunn             #+#    #+#             */
/*   Updated: 2017/04/20 15:05:03 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		getmaxz(int **fdf_file, t_max max)
{
	int x;
	int y;
	int maximum;

	x = 0;
	y = 0;
	maximum = fdf_file[0][0];
	while (y < max.y)
	{
		while (x < max.x)
		{
			if (fdf_file[y][x] > maximum)
				maximum = fdf_file[y][x];
			x++;
		}
		x = 0;
		y++;
	}
	return (maximum);
}

void	rotate(t_draw *point, float z_radian, float x_radian, float y_radian)
{
	int temp_x;
	int temp_y;
	int temp_z;

	temp_x = point->x;
	temp_y = point->y;
	temp_z = point->z;
	point->x = (point->x * cos(z_radian) - (point->z * sin(z_radian)));
	point->y = (point->y * cos(x_radian) - (point->z * sin(x_radian)));
	point->z = (point->z * cos(z_radian) + (temp_x * sin(z_radian)));
	point->z = (temp_z * cos(x_radian) + (temp_y * sin(x_radian)));
	if (y_radian != 0.0)
	{
		temp_x = point->x;
		point->x = (point->x * cos(y_radian) - (point->y * sin(y_radian)));
		point->y = (point->y * cos(y_radian) + (temp_x * sin(y_radian)));
	}
}

void	isopoints(t_draw *points, size_t point_tot, t_adjust camera)
{
	size_t	i;

	i = 0;
	while (i < point_tot)
	{
		rotate(&points[i], camera.z_radian, camera.x_radian, camera.y_radian);
		i++;
	}
}
