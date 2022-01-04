/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:43:13 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/09/30 17:03:52 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_precision(int zero, int space, char *arg, t_prec *lst)
{
	int		total_len;

	total_len = 0;
	if (lst->align_right != 1)
	{
		total_len += ft_print_char(' ', space - 2);
		ft_putstr("0x");
		total_len += 2;
		total_len += ft_print_char('0', zero);
		ft_putstr(arg);
	}
	else
	{
		ft_putstr("0x");
		total_len += 2;
		total_len += ft_print_char('0', zero);
		ft_putstr(arg);
		total_len += ft_print_char(' ', space - 2);
	}
	return (total_len + ft_strlen(arg));
}

static void	ft_treat_p_precision(char *arg, t_prec *lst, int *size)
{
	int	space;
	int	zeros;

	space = 0;
	zeros = 0;
	if (lst->size != NOT_SET)
		zeros = lst->after_dot - ft_strlen(arg);
	if (lst->size > (int)ft_strlen(arg))
		space = lst->size - ft_strlen(arg);
	*size += ft_print_precision(zeros, space, arg, lst);
}

void	ft_arg_p(va_list arg, t_prec **lst, int *size)
{
	long int	argument;
	char		*out;
	char		*dest;

	if (*lst)
	{
		argument = (long int)va_arg(arg, long int);
		out = ft_convert_hex(argument, HEXA_LOWER);
		if ((*lst)->after_dot == 0)
			ft_treat_p_precision("", *lst, size);
		else
			ft_treat_p_precision(out, *lst, size);
		ft_lst_prec_delone(&(*lst));
	}
	else
	{
		argument = (long int)va_arg(arg, long int);
		out = ft_convert_hex(argument, HEXA_LOWER);
		dest = ft_strjoin("0x", out);
		ft_putstr(dest);
		*size += ft_strlen(dest);
		free(dest);
	}
	free(out);
}
