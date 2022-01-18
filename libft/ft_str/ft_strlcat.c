/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:45:29 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/18 16:01:30 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, char *src, unsigned int size)
{
	unsigned int	x;
	unsigned int	i;
	unsigned int	z;

	i = 0;
	x = 0;
	z = 0;
	while (dst[x])
		x++;
	while (src[z])
		z++;
	if (size <= x)
		return (size + z);
	while (x + i < size - 1 && src[i])
	{
		dst[x + i] = src[i];
		i++;
	}
	dst[x + i] = '\0';
	return (z + x);
}
