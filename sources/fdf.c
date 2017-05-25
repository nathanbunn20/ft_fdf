/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <nbunn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 20:03:16 by nbunn             #+#    #+#             */
/*   Updated: 2017/04/20 20:38:45 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		main(int argc, char **argv)
{
	int		**grid;
	t_env	env;
	t_draw	*copy_points;

	if (argc != 2)
	{
		ft_putstr("Error: use one file\n");
		return (0);
	}
	grid = fdfgetfile(argv, &env.x, &env.y);
	validatefdf(argv[1], grid, env.x, env.y);
	env.max = getmaxparam(env.x, env.y, grid);
	env.points = getpoints(grid, env.max.point_tot, env.max);
	copy_points = copypoints(env.points, env.max.point_tot);
	env.mlx = mlx_init();
	env.window = mlx_new_window(env.mlx, WIDTH, HEIGHT, "fdf");
	scale_points(copy_points, env.max.point_tot, env.max);
	env.camera = set_up_camera_angle("parallel");
	isopoints(copy_points, env.max.point_tot, env.camera);
	scale_points_again(copy_points, env.max.point_tot, env.max);
	draw(&env, copy_points);
	mlx_hook(env.window, 2, 3, call_keys, &env);
	mlx_loop(env.mlx);
	return (0);
}
