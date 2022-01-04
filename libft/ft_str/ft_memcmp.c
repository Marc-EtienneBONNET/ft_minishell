/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:42:32 by mbonnet           #+#    #+#             */
/*   Updated: 2021/09/30 17:06:26 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					x;
	unsigned const char		*str1;
	unsigned const char		*str2;

	x = 0;
	str1 = (unsigned const char *)s1;
	str2 = (unsigned const char *)s2;
	if (s1 == s2 || n == 0)
		return (0);
	while (x < n)
	{
		if (str1[x] != str2[x])
			return (str1[x] - str2[x]);
		x++;
	}
	return (0);
}
