/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <nbunn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 18:43:24 by nbunn             #+#    #+#             */
/*   Updated: 2017/04/19 16:40:57 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		getlinecount(char *buf)
{
	int i;
	int z;

	i = 0;
	z = 1;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			z++;
		i++;
	}
	return (z);
}

int		linelen(char *buf)
{
	int i;

	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	return (i);
}

int		ft_word_count(char const *str, char c)
{
	int word_count;
	int i;
	int j;

	i = 0;
	j = 0;
	word_count = 0;
	while (str[i] != '\0')
	{
		while ((str[i] == c) && (str[i] != '\0'))
			i++;
		while ((str[i] != c) && (str[i] != '\0'))
		{
			i++;
			j++;
		}
		while ((str[i] == c) && (str[i] != '\0'))
			i++;
		if (j != 0)
		{
			word_count++;
			j = 0;
		}
	}
	return (word_count);
}

size_t	countconnections(int x, int y)
{
	size_t connections;

	connections = 0;
	connections = connections + (size_t)((y - 1) * x);
	connections = connections + (size_t)((x - 1) * y);
	return (connections);
}

t_max	getmaxparam(int x, int y, int **fdf_file)
{
	t_max	newmax;

	newmax.point_tot = (size_t)(x * y);
	newmax.connections = countconnections(x, y);
	newmax.x = x;
	newmax.y = y;
	newmax.z = getmaxz(fdf_file, newmax);
	return (newmax);
}
