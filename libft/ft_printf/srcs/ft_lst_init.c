/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 21:20:22 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/09/30 17:05:01 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_lst_prec_delone(t_prec **lst)
{
	if (!*lst)
		return ;
	(*lst)->after_dot = 0;
	(*lst)->align_right = 0;
	(*lst)->size = 0;
	(*lst)->sub = 0;
	(*lst)->type = 0;
	(*lst) = NULL;
	free(*lst);
}

int	ft_lst_new_prec(t_prec **lst)
{
	*lst = malloc(sizeof(t_prec));
	if (!(*lst))
		return (-1);
	(*lst)->after_dot = -1;
	(*lst)->align_right = -1;
	(*lst)->size = 0;
	(*lst)->sub = -1;
	(*lst)->type = 0;
	return (1);
}
