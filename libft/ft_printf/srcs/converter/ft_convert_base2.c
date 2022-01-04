/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:43:12 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/09/30 17:00:00 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	ft_base_size(char *base)
{
	long long	i;

	i = 0;
	while (*(base + i))
		i++;
	return (i);
}

int	ft_get_new_size(long long nbr, long long base_size)
{
	int	size;

	size = 1;
	while (nbr >= base_size)
	{
		nbr = nbr / base_size;
		size++;
	}
	return (size);
}

char	*ft_create_tab(long long nbr, char *base, int i_neg, int size)
{
	char	*str;
	int		i;
	int		base_size;

	i = 0;
	base_size = ft_base_size(base);
	if (i_neg == 1)
		size++;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!(str))
		return (0);
	if (i_neg == 1)
	{
		*str = '-';
		i++;
	}
	while (i < size)
	{
		*(str + i) = *(base + (nbr % base_size));
		nbr = nbr / base_size;
		i++;
	}
	*(str + i) = 0;
	return (str);
}

char	*ft_reverse_tab(char *tab)
{
	int		i;
	int		size;
	char	*tab1;

	i = 0;
	size = ft_base_size(tab);
	tab1 = (char *)malloc(sizeof(char) * (size + 1));
	if (!(tab1))
		return (0);
	if (*tab == '-')
	{
		*tab1 = '-';
		i++;
	}
	while (*(tab + i))
	{
		*(tab1 + i) = *(tab + size - 1);
		size--;
		i++;
	}
	*(tab1 + i) = 0;
	return (tab1);
}

char	*convert_number(long long nbr, char *base)
{
	int			i_neg;
	long long	base_size;
	int			nbr_size;

	i_neg = 0;
	if (nbr < 0)
	{
		i_neg = 1;
		nbr = -nbr;
	}
	base_size = ft_base_size(base);
	nbr_size = ft_get_new_size(nbr, base_size);
	return (ft_reverse_tab(ft_create_tab(nbr, base, i_neg, nbr_size)));
}
