/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimale_en_binaire.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:15:13 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/24 15:24:55 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_int(int nb)
{
	int	res;

	res = 1;
	if (nb < 0)
	{
		nb *= -1;
		res++;
	}
	while (nb >= 2)
	{
		res++;
		nb /= 2;
	}
	return (res);
}

char	*ft_convertisseur_decimale_en_binaire(int a)
{
	char	*res;
	int		len;

	errno = 0;
	res = 0;
	len = ft_len_int(a);
	if (a < 0)
		a *= -1;
	res = malloc(sizeof(char) * (len + 1));
	if (errno != 0)
		return (NULL);
	res[len] = '\0';
	while (a >= 2)
	{
		res[--len] = a % 2 + 48;
		a /= 2;
	}
	res[--len] = a % 2 + 48;
	if (len != 0)
		res[0] = '-';
	return (res);
}
