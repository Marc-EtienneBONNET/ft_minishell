/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:45:20 by mbonnet           #+#    #+#             */
/*   Updated: 2021/12/10 11:58:03 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	unsigned int	len;
	unsigned int	x;
	unsigned int	i;

	i = 0;
	x = 0;
	if (!s2)
		return (0);
	if (!s1)
		len = ft_strlen((char *)s2);
	else
		len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!(res))
		return (NULL);
	while (s1 && s1[x])
	{
		res[x] = s1[x];
		x++;
	}
	while (s2[i])
	{
		res[x + i] = s2[i];
		i++;
	}
	res[x + i] = '\0';
	return (res);
}
