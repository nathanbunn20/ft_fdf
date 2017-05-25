/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <nbunn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:28:27 by igallego          #+#    #+#             */
/*   Updated: 2017/04/20 16:19:12 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1000000
# define VAL p = ft_strchr(s[fd], '\n')
# include "../libft/includes/libft.h"
# include "fdf.h"
# include <fcntl.h>

int	get_next_line(const int fd, char **line);

#endif
