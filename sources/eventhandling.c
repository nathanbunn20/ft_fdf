/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <nbunn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 18:09:14 by nbunn             #+#    #+#             */
/*   Updated: 2017/04/20 17:19:12 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

static void		movepointsup(t_env *env, t_adjust *camera, t_draw *points)
{
	size_t	i;
	size_t	tot;

	scale_points(points, env->max.point_tot, env->max);
	isopoints(points, env->max.point_tot, *camera);
	tot = env->max.point_tot;
	i = 0;
	camera->y_pixels = camera->y_pixels - 15;
	while (i < tot)
	{
		points[i].z += camera->z_pixels;
		points[i].x += camera->x_pixels;
		points[i].y += camera->y_pixels;
		points[i].x = (int)((float)points[i].x * camera->zoom);
		points[i].y = (int)((float)points[i].y * camera->zoom);
		i++;
	}
	scale_points_again(points, env->max.point_tot, env->max);
	mlx_clear_window(env->mlx, env->window);
	draw(env, points);
}

static void		movepointsdown(t_env *env, t_adjust *camera, t_draw *points)
{
	size_t	i;
	size_t	tot;

	scale_points(points, env->max.point_tot, env->max);
	isopoints(points, env->max.point_tot, *camera);
	tot = env->max.point_tot;
	i = 0;
	camera->y_pixels = camera->y_pixels + 15;
	while (i < tot)
	{
		points[i].z += camera->z_pixels;
		points[i].x += camera->x_pixels;
		points[i].y += camera->y_pixels;
		points[i].x = (int)((float)points[i].x * camera->zoom);
		points[i].y = (int)((float)points[i].y * camera->zoom);
		i++;
	}
	scale_points_again(points, env->max.point_tot, env->max);
	mlx_clear_window(env->mlx, env->window);
	draw(env, points);
}

static void		movepointsleft(t_env *env, t_adjust *camera, t_draw *points)
{
	size_t	i;
	size_t	tot;

	scale_points(points, env->max.point_tot, env->max);
	isopoints(points, env->max.point_tot, *camera);
	tot = env->max.point_tot;
	i = 0;
	camera->x_pixels = camera->x_pixels - 15;
	while (i < tot)
	{
		points[i].z += camera->z_pixels;
		points[i].x += camera->x_pixels;
		points[i].y += camera->y_pixels;
		points[i].x = (int)((float)points[i].x * camera->zoom);
		points[i].y = (int)((float)points[i].y * camera->zoom);
		i++;
	}
	scale_points_again(points, env->max.point_tot, env->max);
	mlx_clear_window(env->mlx, env->window);
	draw(env, points);
}

static void		movepointsright(t_env *env, t_adjust *camera, t_draw *points)
{
	size_t	i;
	size_t	tot;

	scale_points(points, env->max.point_tot, env->max);
	isopoints(points, env->max.point_tot, *camera);
	tot = env->max.point_tot;
	i = 0;
	camera->x_pixels = camera->x_pixels + 15;
	while (i < tot)
	{
		points[i].z += camera->z_pixels;
		points[i].x += camera->x_pixels;
		points[i].y += camera->y_pixels;
		points[i].x = (int)((float)points[i].x * camera->zoom);
		points[i].y = (int)((float)points[i].y * camera->zoom);
		i++;
	}
	scale_points_again(points, env->max.point_tot, env->max);
	mlx_clear_window(env->mlx, env->window);
	draw(env, points);
}

int				call_keys(int keycode, void *param)
{
	t_env	*env;
	t_draw	*points;

	env = (t_env*)param;
	points = copypoints(env->points, env->max.point_tot);
	if (keycode == 53)
	{
		mlx_destroy_window(env->mlx, env->window);
		exit(0);
	}
	if (keycode == KEY_UP)
		movepointsup(env, &env->camera, points);
	if (keycode == KEY_LEFT)
		movepointsleft(env, &env->camera, points);
	if (keycode == KEY_DOWN)
		movepointsdown(env, &env->camera, points);
	if (keycode == KEY_RIGHT)
		movepointsright(env, &env->camera, points);
	camera_control(keycode, env, points);
	return (0);
}
