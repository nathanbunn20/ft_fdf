/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   morehelpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <nbunn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:36:32 by nbunn             #+#    #+#             */
/*   Updated: 2017/04/20 20:45:27 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_draw		*copypoints(t_draw *oldpoints, size_t point_tot)
{
	t_draw	*newpoints;
	size_t	i;

	newpoints = (t_draw*)malloc(sizeof(t_draw) * point_tot);
	i = 0;
	while (i < point_tot)
	{
		newpoints[i].x = oldpoints[i].x;
		newpoints[i].y = oldpoints[i].y;
		newpoints[i].z = oldpoints[i].z;
		newpoints[i].color = oldpoints[i].color;
		newpoints[i].direction = oldpoints[i].direction;
		i++;
	}
	return (newpoints);
}

void		zoom(t_env *env, t_adjust *camera, t_draw *points, int add)
{
	int		i;
	size_t	tot;

	i = -1;
	camera->zoom = (camera->zoom * (float)add) / 100.0;
	if (camera->zoom > 50.0)
		camera->zoom = 50.0;
	if (camera->zoom < 0.003)
		camera->zoom = 0.003;
	scale_points(points, env->max.point_tot, env->max);
	isopoints(points, env->max.point_tot, *camera);
	tot = env->max.point_tot;
	while (++i < (int)tot)
	{
		points[i].z += camera->z_pixels;
		points[i].x += camera->x_pixels;
		points[i].y += camera->y_pixels;
		points[i].x = (int)((float)points[i].x * camera->zoom);
		points[i].y = (int)((float)points[i].y * camera->zoom);
	}
	scale_points_again(points, env->max.point_tot, env->max);
	mlx_clear_window(env->mlx, env->window);
	draw(env, points);
}

void		camera_control(int keycode, t_env *env, t_draw *points)
{
	if (keycode == KEY_W)
		adjust_points_x(env, &env->camera, points, 3);
	if (keycode == KEY_S)
		adjust_points_x(env, &env->camera, points, -3);
	if (keycode == KEY_A)
		adjust_points_z(env, &env->camera, points, 3);
	if (keycode == KEY_D)
		adjust_points_z(env, &env->camera, points, -3);
	if (keycode == KEY_Q)
		adjust_points_y(env, &env->camera, points, -3);
	if (keycode == KEY_E)
		adjust_points_y(env, &env->camera, points, 3);
	if (keycode == KEY_I)
		zoom(env, &env->camera, points, 120);
	if (keycode == KEY_K)
		zoom(env, &env->camera, points, 80);
}

static int	checkfiletype(char *str)
{
	int i;

	i = 0;
	str = ft_strrchr(str, '.');
	if (*str == '.')
	{
		if ((ft_strcmp(str, ".fdf")) == 0)
			return (1);
	}
	return (0);
}

void		validatefdf(char *str, int **fdf, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((checkfiletype(str)) == 0)
	{
		ft_putstr("Error: incorrect file type\n");
		exit(-2);
	}
	while (i < height)
	{
		while (j < width)
		{
			if (fdf[i][j] > 2147483647 || fdf[i][j] < -2147483648)
			{
				ft_putstr("Error: file is corrupt\n");
				exit(-3);
			}
			j++;
		}
		j = 0;
		i++;
	}
}
