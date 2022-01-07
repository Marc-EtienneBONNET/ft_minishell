/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_et_ft_utile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:26:09 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/07 12:59:01 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_check_redirection(char *str)
{
	if (!str)
		return (-1);
	if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<')
		|| (str[0] == '&' && str[1] == '&')
		|| (str[0] == '|' && str[1] == '|'))
		return (2);
	if (str[0] == '|' || str[0] == '>' || str[0] == '<' || str[0] == ';')
		return (1);
	return (-1);
}

char	*my_little_printf_char(char *str)
{
	printf("%s", str);
	return (NULL);
}