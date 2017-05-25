/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbunn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:21:16 by nbunn             #+#    #+#             */
/*   Updated: 2016/11/03 16:34:23 by nbunn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_tolower(int c)
{
	int a;

	a = c;
	if (a >= 65 && a <= 90)
		return (a + 32);
	else
		return (c);
}
