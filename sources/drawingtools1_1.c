/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawingtools1_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <nbunn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 15:56:16 by nbunn             #+#    #+#             */
/*   Updated: 2017/04/20 15:06:21 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int				drawlen(t_value values, t_draw copypoint, t_draw copynextpoint)
{
	int len;

	len = 0;
	while (1)
	{
		if (copypoint.x == copynextpoint.x && copynextpoint.y == copypoint.y)
			break ;
		values.e2 = values.err;
		if (values.e2 > -values.dx)
		{
			values.err = values.err - values.dy;
			copypoint.x = copypoint.x + values.sx;
		}
		if (values.e2 < values.dy)
		{
			values.err = values.err + values.dx;
			copypoint.y = copypoint.y + values.sy;
		}
		len++;
	}
	return (len);
}

static int		getcoloradd(t_draw point, t_draw nextpoint, int len)
{
	int diff;

	diff = nextpoint.color - point.color;
	if (len == 0)
		return (0);
	diff /= len;
	return (diff);
}

static t_value	fill_values(t_draw point, t_draw nextpoint)
{
	t_value	values;

	values.dy = abs(nextpoint.y - point.y);
	values.dx = abs(nextpoint.x - point.x);
	values.sx = point.x < nextpoint.x ? 1 : -1;
	values.sy = point.y < nextpoint.y ? 1 : -1;
	values.err = (values.dx > values.dy ? values.dx : -values.dy) / 2;
	return (values);
}

void			drawline(t_env *env, t_draw point, t_draw nextpoint)
{
	t_value	values;
	int		len;
	int		coloradd;

	values = fill_values(point, nextpoint);
	len = drawlen(values, point, nextpoint);
	coloradd = getcoloradd(point, nextpoint, len);
	while (len > 0)
	{
		mlx_pixel_put(env->mlx, env->window, point.x, point.y, point.color);
		values.e2 = values.err;
		if (values.e2 > -values.dx)
		{
			values.err = values.err - values.dy;
			point.x = point.x + values.sx;
		}
		if (values.e2 < values.dy)
		{
			values.err = values.err + values.dx;
			point.y = point.y + values.sy;
		}
		point.color = point.color + coloradd;
		len--;
	}
}

void			draw(t_env *env, t_draw *points)
{
	size_t	connections;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	connections = countconnections(env->x, env->y);
	while (j < connections)
	{
		if (points[i].direction == 10)
			drawline(env, points[i], points[i + env->x]);
		else if (points[i].direction == 11)
		{
			drawline(env, points[i], points[i + env->x]);
			j++;
			drawline(env, points[i], points[i + 1]);
		}
		else
			drawline(env, points[i], points[i + 1]);
		i++;
		j++;
	}
}
