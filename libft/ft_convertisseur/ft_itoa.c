/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <webbonnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:40:28 by mbonnet           #+#    #+#             */
/*   Updated: 2020/11/20 11:54:01 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(long nb)
{
	int	res;

	res = 0;
	if (nb < 0)
	{
		nb *= -1;
		res = 1;
	}
	while (nb > 9)
	{
		nb /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	len;
	long long		nb;

	nb = (long long)n;
	len = 1;
	len += ft_len((long)n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!(res))
		return (NULL);
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	res[len] = '\0';
	while (nb > 9)
	{
		res[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	res[--len] = nb + '0';
	return (res);
}
