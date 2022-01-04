/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:42:39 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/09/30 16:58:13 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	ft_translatebase(char *str, char *base, int i, int size)
{
	long long	j;
	long long	k;
	long long	size1;

	j = 0;
	k = 0;
	size1 = (long long)size;
	while (*(base + j) != 0)
	{
		if (*(str + i) == *(base + j))
		{
			k = k * size1 + j;
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (k);
}

int	ft_analyse_base(char *base, int *base_size)
{
	int	i;
	int	h;

	i = 0;
	while (*(base + i) != 0)
	{
		h = 0;
		if (base[i] == '+' || base[i] == '-' || base[i] <= 32 || base[i] == 127)
			return (0);
		while (h < i)
		{
			if (*(base + i) == *(base + h))
				return (0);
			h++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	*base_size = i;
	return (1);
}

long long	ft_atoi_base(char *str, char *base, int base_size)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while ((*(str + i) >= 9 && *(str + i) <= 13) || *(str + i) == 32)
		i++;
	while (*(str + i) == '-' || *(str + i) == '+')
	{
		if (*(str + i) == '-')
			j = -j;
		i++;
	}
	return (j * ft_translatebase(str, base, i, base_size));
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	long long	number;
	int			base_size;
	int			*pt_base_size;
	int			base2_size;
	int			*pt_base2_size;

	pt_base_size = &base_size;
	pt_base2_size = &base2_size;
	if (ft_analyse_base(base_from, pt_base_size) == 0)
		return (0);
	if (ft_analyse_base(base_to, pt_base2_size) == 0)
		return (0);
	number = ft_atoi_base(nbr, base_from, base_size);
	return (convert_number(number, base_to));
}
