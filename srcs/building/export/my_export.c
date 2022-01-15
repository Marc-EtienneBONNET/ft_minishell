/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:29:06 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/15 17:51:18 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_export(char **argv)
{
	char	**arg;

	if (!argv[1])
		printf("impretion de export\n");
	else
	{
		arg = my_recup_arg(argv[1]);
	}
	return (1);
}