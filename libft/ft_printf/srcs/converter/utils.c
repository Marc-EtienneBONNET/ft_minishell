/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:08:37 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/09/30 17:01:18 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_hex(long int var, char *base_to)
{
	char	*address;
	char	*dec;

	dec = "0123456789";
	address = ft_convert_base(ft_itoa(var), dec, base_to);
	return (address);
}

int	ft_part_putstr(const char *s, size_t len)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s && i < len)
	{
		write(1, s, 1);
		s++;
		i++;
	}
	return (i);
}

int	ft_print_char(char c, int nb)
{
	int	count;

	count = nb;
	while (nb-- > 0)
		ft_putchar(c);
	if (count > 0)
		return (count);
	return (0);
}
