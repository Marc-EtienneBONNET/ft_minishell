/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:21:22 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/09/30 17:00:46 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nb_len(unsigned int nb)
{
	int		len;

	len = 0;
	if (nb <= 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_utoa(unsigned int nb)
{
	char			*str;
	unsigned int	nbr;
	int				len;

	nbr = nb;
	len = ft_nb_len(nbr);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	str[len--] = '\0';
	if (nbr == 0)
		str[0] = 48;
	while (nbr > 0)
	{
		str[len] = '0' + (nbr % 10);
		nbr = nbr / 10;
		len--;
	}
	return (str);
}
