/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:46:40 by mbonnet           #+#    #+#             */
/*   Updated: 2021/09/30 17:08:00 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen1(char *str)
{
	int	x;

	x = 0;
	while (str[x])
		x++;
	return (x);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	x;

	if (s == NULL)
		return (0);
	x = 0;
	res = (char *)malloc((sizeof(char)) * (len + 1));
	if (!(res))
		return (NULL);
	if ((int)start > ft_strlen1((char *)s))
		return (res);
	while (s[start + x] && x < len)
	{
		res[x] = s[start + x];
		x++;
	}
	res[x] = '\0';
	return (res);
}
