/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_tmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:08:40 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/06 17:44:22 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_print_list_chene(t_cmd *cmd)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	if (!cmd)
		return (1);
	printf("\e[1;31m\tDEBUT structure cmd\n\e[0m");
	while (cmd->info_cmd->nb_maillons > i)
	{
		printf("\e[1;36m\n\n\tMaillon N %d\n\e[0m", i);
		printf("\e[1;31mpath \t\t:\t(%s)\n\e[0m", cmd->path);
		printf("\e[1;32mcmd \t\t:\t(%s)\n\e[0m", cmd->cmd);
		printf("\e[1;33marg\t\t:\t\e\e[0m");
		if (cmd->arg)
			while (cmd->arg[x] != NULL)
				printf("\e[1;33m(%s)\t\e[0m", cmd->arg[x++]);
		else
			printf("\e[1;33m((null))\e[0m");
		printf("\n");
		if (cmd->red != NULL)
			printf("\e[1;35mredirection\t:\t%s\n\e[0m", cmd->red);
		else
			printf("\e[1;35mredirection\t:\t((null))\n\e[0m");
		i++;
		x = 0;
		cmd = cmd->next;
	}
	printf("\e[1;31m\tFIN structure cmd\n\n\e[0m");
	return (1);
}