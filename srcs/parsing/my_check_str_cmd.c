/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_check_str_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:17:25 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/03 09:16:38 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_check_nb_guillemet(char *str)
{
	int	x;
	int	gu;

	x = 0;
	gu = 0;
	while (str[x])
	{
		if (gu == 0 && str[x] == '\'')
			gu = 1;
		else if (gu == 0 && str[x] == '\"')
			gu = 2;
		else if (gu == 1 && str[x] == '\'')
			gu = 0;
		else if (gu == 2 && str[x] == '\"')
			gu = 0;
		x++;
	}
	return (gu);
}

int	my_check_bad_red(char *str)
{
	int	x;
	int	gu;
	int	tem;

	x = 0;
	gu = 0;
	tem = 0;
	while (str[x])
	{
		my_check_gu(&gu, str[x]);
		if (my_check_red(gu, str[x]) < 0)
			tem++;
		else
			tem = 0;
		if (tem == 3)
			return (-1);
		x++;
	}
	return (1);
}
