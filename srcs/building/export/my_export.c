/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:29:06 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 09:50:23 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	my_export(char **argv)
{
	char	**arg;

	arg = NULL;
	if (!argv[1])
		printf("impretion de export\n");
	else
	{
		arg = my_recup_arg(argv[1]);
		my_ajoue_arg(arg);
	}
	return (1);
}