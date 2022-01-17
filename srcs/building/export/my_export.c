/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:29:06 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 14:51:50 by mbonnet          ###   ########.fr       */
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
	char	**arg;

	arg = NULL;
	if (!argv[1])
	{
		if (my_print_export() == -1)
			return (-1);
	}
	else
	{
		arg = my_recup_arg(argv[1]);
		if (arg == NULL || my_ajoue_arg(arg) == -1)
		{
			my_free_double_tab((void **)arg, -1);
			return (-1);
		}
	}
	return (1);
}
