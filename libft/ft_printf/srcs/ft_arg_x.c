/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:42:55 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/09/30 17:04:31 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_spaces(t_prec *lst, char *arg)
{
	int		result;
	int		len;

	len = (int)ft_strlen(arg);
	result = 0;
	if (lst->sub == NOT_SET || lst->after_dot != NOT_SET)
	{
		if (lst->size > lst->after_dot && lst->size > len)
		{
			if (lst->after_dot > len)
			{
				result = lst->size - lst->after_dot;
				if (arg[0] == '-')
					result--;
			}
			else
				result = lst->size - len;
		}
	}
	return (result);
}

static int	ft_get_zeros(t_prec *lst, char *arg)
{
	int		result;
	int		len;

	len = (int)ft_strlen(arg);
	if (arg[0] == '-')
		len--;
	result = 0;
	if (lst->sub == 1 && lst->after_dot == NOT_SET)
	{
		if (lst->size > len)
		{
			result = lst->size - len;
			if (arg[0] == '-')
				result--;
		}
	}
	if (lst->after_dot != NOT_SET)
	{
		if (lst->after_dot > len)
		{
			result = lst->after_dot - len;
		}
	}
	return (result);
}

static int	ft_print_result(char *arg, int zeros, int spaces, int align_right)
{
	int		is_negative;
	int		total_len;

	total_len = 0;
	is_negative = 0;
	if (arg[0] == '-')
		is_negative = 1;
	if (align_right != 1)
		total_len += ft_print_char(' ', spaces);
	if (is_negative == 1)
		ft_putchar('-');
	total_len += ft_print_char('0', zeros);
	ft_putstr(arg + is_negative);
	if (align_right == 1)
		total_len += ft_print_char(' ', spaces);
	return (total_len + ft_strlen(arg));
}

static void	ft_treat_x_precision(char *arg, t_prec *lst, int *size)
{
	int		count;
	int		zeros;
	int		spaces;

	zeros = ft_get_zeros(lst, arg);
	spaces = ft_get_spaces(lst, arg);
	if ((int)ft_strlen(arg) == 1 && arg[0] == '0' && lst->after_dot == 0)
	{
		count = lst->size;
		ft_print_char(' ', lst->size);
	}
	else
		count = ft_print_result(arg, zeros, spaces, lst->align_right);
	*size += count;
}

void	ft_arg_x(va_list arg, char base, t_prec **lst, int *size)
{
	long		argument;
	char		*out;
	char		*base_to;

	if (base == 'x')
		base_to = HEXA_LOWER;
	if (base == 'X')
		base_to = HEXA_UPPER;
	if (base == 'o')
		base_to = "01234567";
	if (*lst)
	{
		argument = (unsigned int)va_arg(arg, unsigned int);
		out = ft_convert_hex(argument, base_to);
		ft_treat_x_precision(out, *lst, size);
		ft_lst_prec_delone(&(*lst));
	}
	else
	{
		argument = (unsigned int)va_arg(arg, unsigned int);
		out = ft_convert_hex(argument, base_to);
		ft_putstr(out);
		*size += ft_strlen(out);
	}
	free(out);
}
