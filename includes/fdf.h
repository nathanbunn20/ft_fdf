/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <nbunn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 16:27:44 by nbunn             #+#    #+#             */
/*   Updated: 2017/04/20 17:21:05 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../minilibx/mlx.h"
# include "get_next_line.h"
# include "../libft/includes/libft.h"
# include <math.h>
# define NUMBER(x) x >= 65 && x <= 90
# define WIDTH 1000
# define HEIGHT 1000
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_I 34
# define KEY_K 40
# define KEY_Z 6
# define KEY_X 7

typedef struct	s_adjust
{
	int				x_pixels;
	int				y_pixels;
	int				z_angle;
	int				x_angle;
	int				y_angle;
	float			x_radian;
	float			z_radian;
	float			y_radian;
	float			zoom;
	int				z_pixels;
}				t_adjust;

typedef struct	s_max
{
	int		x;
	int		y;
	int		z;
	size_t	point_tot;
	size_t	connections;
}				t_max;

typedef struct	s_draw
{
	int		x;
	int		y;
	int		z;
	int		direction;
	int		color;
}				t_draw;

typedef struct	s_value
{
	int	dx;
	int	dy;
	int	sx;
	int	err;
	int	sy;
	int	e2;
}				t_value;

typedef struct	s_env
{
	void		*mlx;
	void		*window;
	void		*img;
	void		*imgdata;
	int			x;
	int			y;
	t_draw		*points;
	t_max		max;
	t_adjust	camera;
}				t_env;

typedef struct	s_color
{
	float	coloradd;
	int		max;
	int		colorpick;
}				t_color;

int				**fdfgetfile(char **argv, int *x, int *y);
int				getlinecount(char *buf);
int				linelen(char *buf);
int				ft_word_count(char const *str, char c);
size_t			countconnections(int x, int y);
t_draw			setuppoint(int **fdf_file, int coord[], int direction,
							t_max max);
t_draw			*getpoints(int **fdf_file, size_t connections, t_max max);
int				getmaxz(int **fdf_file, t_max max);
void			rotate(t_draw *point, float z_radian, float x_radian,
						float y_radian);
char			**readfile(int fd, int *y);
int				call_keys(int keycode, void *param);
t_max			getmaxparam(int x, int y, int **fdf_file);
t_draw			*copypoints(t_draw *oldpoints, size_t point_tot);
void			draw(t_env *env, t_draw *points);
void			drawline(t_env *env, t_draw point, t_draw nextpoint);
int				drawlen(t_value values, t_draw copypoint, t_draw copynextpoint);
void			scale_points(t_draw *points, size_t point_tot, t_max max);
void			adjust_rotate(t_env *env, float z_radian, float x_radian,
								float y_radian, t_draw *points);
t_adjust		set_up_camera_angle(char *str);
void			isopoints(t_draw *points, size_t point_tot, t_adjust camera);
void			scale_points_again(t_draw *points, size_t point_tot, t_max max);
void			zoom(t_env *env, t_adjust *camera, t_draw *points, int add);
void			adjust_points_x(t_env *env, t_adjust *cam, t_draw *points,
									int add);
void			adjust_points_y(t_env *env, t_adjust *cam, t_draw *points,
									int add);
void			adjust_points_z(t_env *env, t_adjust *cam, t_draw *points,
									int add);
void			camera_control(int keycode, t_env *env, t_draw *points);
void			validatefdf(char *str, int **fdf, int width, int height);
t_adjust		parallel_view(void);

#endif
