/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_tmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:08:40 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/14 09:17:48 by mbonnet          ###   ########.fr       */
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
		printf(BLEU"\n\n\tNombre maillon : %d\n"BLANC, cmd->info_cmd->nb_maillons);
		printf(VERT"cmd \t\t:\t(%s)\n"BLANC, cmd->cmd);
		printf(VIOLET"fichier_1 \t:\t(%s)\n"BLANC, cmd->fichier_1);
		printf(VIOLET"fichier_2 \t:\t(%s)\n"BLANC, cmd->fichier_2);
		printf(VIOLET"intra_red \t:\t(%s)\n"BLANC, cmd->intra_red);
		printf(VERT"path \t\t:\t(%s)\n"BLANC, cmd->path);
		printf(VERT"arg\t\t:\t"BLANC);
		if (cmd->arg)
			while (cmd->arg[x] != NULL)
				printf(VERT"(%s)\t"BLANC, cmd->arg[x++]);
		else
			printf(VERT"((null))"BLANC);
		printf("\n");
		if (cmd->red != NULL)
			printf(VERT"redirection\t:\t%s\n"BLANC, cmd->red);
		else
			printf(VERT"redirection\t:\t((null))\n"BLANC);
		i++;
		x = 0;
		cmd = cmd->next;
	}
	printf(ROUGE"\tFIN structure cmd\n\n"BLANC);
	return (1);
}