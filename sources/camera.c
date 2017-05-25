/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <nbunn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 14:49:40 by nbunn             #+#    #+#             */
/*   Updated: 2017/04/20 17:20:52 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_adjust	parallel_view(void)
{
	t_adjust	camera;

	camera.z_angle = 0;
	camera.x_angle = 10;
	camera.y_angle = 0;
	camera.z_radian = ((float)((float)camera.z_angle / 180.0) * M_PI);
	camera.x_radian = ((float)((float)camera.x_angle / 180.0) * M_PI);
	camera.y_radian = ((float)((float)camera.y_angle / 180.0) * M_PI);
	camera.x_pixels = 0;
	camera.y_pixels = 0;
	camera.zoom = 1.0;
	camera.z_pixels = 0;
	return (camera);
}

t_adjust	set_up_camera_angle(char *str)
{
	t_adjust	camera;

	if ((ft_strcmp(str, "iso")) == 0)
	{
		camera.z_angle = 25;
		camera.x_angle = 60;
		camera.y_angle = 42;
		camera.z_radian = ((float)((float)camera.z_angle / 180.0) * M_PI);
		camera.x_radian = ((float)((float)camera.x_angle / 180.0) * M_PI);
		camera.y_radian = ((float)((float)camera.y_angle / 180.0) * M_PI);
		camera.x_pixels = 0;
		camera.y_pixels = 0;
		camera.zoom = 1.0;
		camera.z_pixels = 0;
	}
	else if ((ft_strcmp(str, "parallel")) == 0)
		camera = parallel_view();
	else
	{
		ft_putstr("Error: Unrecognized camera\n");
		exit(-4);
	}
	return (camera);
}

void		adjust_points_x(t_env *env, t_adjust *cam, t_draw *points, int add)
{
	size_t	i;
	size_t	tot;

	cam->x_angle += add;
	cam->x_radian = ((float)((float)cam->x_angle / 180.0) * (float)M_PI);
	scale_points(points, env->max.point_tot, env->max);
	isopoints(points, env->max.point_tot, *cam);
	i = 0;
	tot = env->max.point_tot;
	while (i < tot)
	{
		points[i].z += cam->z_pixels;
		points[i].x += cam->x_pixels;
		points[i].y += cam->y_pixels;
		points[i].x = (int)((float)points[i].x * cam->zoom);
		points[i].y = (int)((float)points[i].y * cam->zoom);
		i++;
	}
	scale_points_again(points, env->max.point_tot, env->max);
	mlx_clear_window(env->mlx, env->window);
	draw(env, points);
}

void		adjust_points_y(t_env *env, t_adjust *cam, t_draw *points, int add)
{
	size_t	i;
	size_t	tot;

	cam->y_angle += add;
	cam->y_radian = ((float)((float)cam->y_angle / 180.0) * (float)M_PI);
	scale_points(points, env->max.point_tot, env->max);
	isopoints(points, env->max.point_tot, *cam);
	tot = env->max.point_tot;
	i = 0;
	while (i < tot)
	{
		points[i].z += cam->z_pixels;
		points[i].x += cam->x_pixels;
		points[i].y += cam->y_pixels;
		points[i].x = (int)((float)points[i].x * cam->zoom);
		points[i].y = (int)((float)points[i].y * cam->zoom);
		i++;
	}
	scale_points_again(points, env->max.point_tot, env->max);
	mlx_clear_window(env->mlx, env->window);
	draw(env, points);
}

void		adjust_points_z(t_env *env, t_adjust *cam, t_draw *points, int add)
{
	size_t	i;
	size_t	tot;

	cam->z_angle += add;
	cam->z_radian = ((float)((float)cam->z_angle / 180.0) * (float)M_PI);
	scale_points(points, env->max.point_tot, env->max);
	isopoints(points, env->max.point_tot, *cam);
	tot = env->max.point_tot;
	i = 0;
	while (i < tot)
	{
		points[i].z += cam->z_pixels;
		points[i].x += cam->x_pixels;
		points[i].y += cam->y_pixels - cam->z_pixels;
		points[i].x = (int)((float)points[i].x * cam->zoom);
		points[i].y = (int)((float)points[i].y * cam->zoom);
		i++;
	}
	scale_points_again(points, env->max.point_tot, env->max);
	mlx_clear_window(env->mlx, env->window);
	draw(env, points);
}
