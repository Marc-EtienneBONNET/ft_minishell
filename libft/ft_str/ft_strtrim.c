/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:46:30 by mbonnet           #+#    #+#             */
/*   Updated: 2021/09/30 17:07:56 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_radar(char c, char *set)
{
	int	x;

	x = -1;
	while (set[++x])
		if (set[x] == c)
			return (1);
	return (0);
}

static int	ft_strlen1(char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

char	*ft_strtrim(char const *s, char const *set)
{
	unsigned int	len;
	char			*res;
	char			*str;
	int				x;

	x = -1;
	if (!s || !set)
		return (NULL);
	str = (char *)s;
	len = ft_strlen1((char *)s);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!(res))
		return (NULL);
	while (ft_radar(*str, (char *)set) == 1)
		str++;
	while (str[++x])
		res[x] = str[x];
	x -= 1;
	while (ft_radar(res[x], (char *)set) == 1)
	{
		res[x] = '\0';
		x--;
	}
	res[x + 1] = '\0';
	return (res);
}
