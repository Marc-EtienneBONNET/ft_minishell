/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_tmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:08:40 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/11 18:04:14 by mbonnet          ###   ########.fr       */
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
	printf(ROUGE"\tDEBUT structure cmd\n"BLANC);
	while (cmd->info_cmd->nb_maillons > i)
	{
		printf(BLEU"\n\n\tMaillon N %d\n"BLANC, i);
		printf(ROUGE"path \t\t:\t(%s)\n"BLANC, cmd->path);
		printf(VERT"cmd \t\t:\t(%s)\n"BLANC, cmd->cmd);
		printf(JAUNE"arg\t\t:\t"BLANC);
		if (cmd->arg)
			while (cmd->arg[x] != NULL)
				printf(JAUNE"(%s)\t"BLANC, cmd->arg[x++]);
		else
			printf(JAUNE"((null))"BLANC);
		printf("\n");
		if (cmd->red != NULL)
			printf(VIOLET"redirection\t:\t%s\n"BLANC, cmd->red);
		else
			printf(VIOLET"redirection\t:\t((null))\n"BLANC);
		i++;
		x = 0;
		cmd = cmd->next;
	}
	printf(ROUGE"\tFIN structure cmd\n\n"BLANC);
	return (1);
}