/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:42:00 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/09/30 17:01:40 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_treat_char_precision(char arg, t_prec *lst)
{
	int		total_len;

	total_len = 0;
	if (lst->size != NOT_SET)
	{
		if (lst->align_right == NOT_SET)
		{
			if (lst->sub == 1)
				total_len += ft_print_char('0', lst->size - 1) + 1;
			else
				total_len += ft_print_char(' ', lst->size - 1) + 1;
			ft_putchar(arg);
		}
		else
		{
			ft_putchar(arg);
			total_len += 1;
			total_len += ft_print_char(' ', lst->size - 1);
		}
	}
	return (total_len);
}

void	ft_arg_c(va_list arg, char c, t_prec **lst, int *size)
{
	unsigned char	argument;

	if (*lst)
	{
		if (c == '%')
			argument = '%';
		else
			argument = (unsigned char)va_arg(arg, int);
		*size += ft_treat_char_precision(argument, *lst);
		ft_lst_prec_delone(&(*lst));
	}
	else
	{
		if (c == '%')
			argument = '%';
		else
			argument = (unsigned char)va_arg(arg, int);
		ft_putchar(argument);
		*size += 1;
	}
}
