/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filehandles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <nbunn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 17:02:58 by nbunn             #+#    #+#             */
/*   Updated: 2017/05/05 10:45:43 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

char		**readfile(int fd, int *y)
{
	int		i;
	int		ret;
	char	**file;

	i = 0;
	file = (char**)malloc(sizeof(char*) * 1000000);
	while (1)
	{
		if ((ret = get_next_line(fd, &file[i])) <= 0)
			break ;
		i++;
	}
	if (ret == -1)
		return (NULL);
	file[i] = 0;
	*y = i;
	return (file);
}

static void	ft_free_double_char_array(char **buff, int size)
{
	while (size >= 0)
		free(buff[size--]);
	free(buff);
}

static int	**convertchartoint(char **buf, int y, int i)
{
	int		**array;
	int		j;
	int		a;
	int		b;
	char	**line;

	array = (int**)malloc(sizeof(int*) * y + 1);
	j = 0;
	a = 0;
	b = 0;
	while (i < y)
	{
		line = ft_strsplit(buf[i], ' ');
		array[a] = (int*)malloc(sizeof(int) * ft_word_count(buf[i], ' '));
		while (j < ft_word_count(buf[i], ' '))
			array[a][b++] = ft_atoi(line[j++]);
		b = 0;
		a++;
		ft_free_double_char_array(line, j);
		j = 0;
		i++;
	}
	array[a] = 0;
	return (array);
}

int			**fdfgetfile(char **argv, int *x, int *y)
{
	int		**fdf_file;
	char	**temp;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("open error();\n");
		exit(-1);
	}
	temp = readfile(fd, y);
	close(fd);
	if (temp == NULL)
	{
		ft_putstr("Error: failed to read file\n");
		exit(-1);
	}
	fd = 0;
	*x = ft_word_count(temp[fd], ' ');
	fdf_file = convertchartoint(temp, *y, fd);
	return (fdf_file);
}
