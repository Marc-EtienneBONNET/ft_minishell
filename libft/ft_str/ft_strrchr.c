/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:46:22 by mbonnet           #+#    #+#             */
/*   Updated: 2021/09/30 17:07:53 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*res;

	res = (0);
	while (*str)
	{
		if (*str == c)
			res = (char *)str;
		str++;
	}
	if (res)
		return (res);
	if (c == '\0')
		return ((char *)str);
	return (0);
}
