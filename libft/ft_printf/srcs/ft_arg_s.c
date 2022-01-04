/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:42:39 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/09/30 17:04:20 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print(char *s, int nb_space, size_t after_dot, t_prec *lst)
{
	int		total_len;

	total_len = 0;
	if (lst->align_right == NOT_SET)
	{
		if (lst->sub == 1)
			total_len += ft_print_char('0', nb_space);
		else
			total_len += ft_print_char(' ', nb_space);
		total_len += ft_part_putstr(s, after_dot);
	}
	else
	{
		total_len += ft_part_putstr(s, after_dot);
		total_len += ft_print_char(' ', nb_space);
	}
	return (total_len);
}

static void	ft_treat_s_precision(char *arg, t_prec *lst, int *size)
{
	int		nb_space;
	int		len;

	len = ft_strlen(arg);
	nb_space = 0;
	if (lst->size != NOT_SET)
	{
		if (lst->after_dot != NOT_SET)
		{
			nb_space -= lst->after_dot;
			if (lst->after_dot < len)
				len = lst->after_dot;
		}
		if (lst->size > len)
			nb_space = lst->size - len;
	}
	*size += ft_print(arg, nb_space, lst->after_dot, lst);
}

void	ft_arg_s(va_list arg, t_prec **lst, int *size)
{
	char	*argument;

	if (*lst)
	{
		argument = (char *)va_arg(arg, char *);
		if (!argument)
			ft_treat_s_precision("(null)", *lst, size);
		else
			ft_treat_s_precision(argument, *lst, size);
		ft_lst_prec_delone(&(*lst));
	}
	else
	{
		argument = (char *)va_arg(arg, char *);
		if (!argument)
		{
			ft_putstr("(null)");
			*size += ft_strlen("(null)");
		}
		else
		{
			ft_putstr(argument);
			*size += ft_strlen(argument);
		}
	}
}
