/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:29:06 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 14:13:30 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mess_err2(char *str)
{
	write(2, "minishell: export: '", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	my_export(char **argv)
{
	if (!argv[1])
	{
		if (my_print_export() == -1)
			return (-1);
	}
	else
	{
		if (my_ajoue_arg(&(argv[1])) == -1)
			return (-1);
	}
	return (1);
}
