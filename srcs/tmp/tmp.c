/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 07:55:42 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/31 18:12:59 by mbonnet          ###   ########.fr       */
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
	printf(ROUGE"\tDEBUT structure cmd, %d\n"BLANC, g_term.nb_maillon);
	while (g_term.nb_maillon > i)
	{
		my_print_maillon(cmd, i);
		i++;
		x = 0;
		cmd = cmd->next;
	}
	printf(ROUGE"\tFIN structure cmd\n\n"BLANC);
	return (1);
}

int	my_print_maillon(t_cmd *cmd, int i)
{
	int	x;

	x = 0;
	if (!cmd)
		return (1);
	dprintf(2, BLEU"\n\n\tMaillon N %d\n"BLANC, i);
	dprintf(2, BLEU"\tNombre maillon : %d\n"BLANC, g_term.nb_maillon);
	dprintf(2, VERT"cmd \t\t:\t(%s)\n"BLANC, cmd->cmd);
	dprintf(2, VERT"path \t\t:\t(%s)\n"BLANC, cmd->path);
	dprintf(2, VERT"intra_red\t:\t"BLANC);
	while (cmd->red && cmd->red[x].red)
	{
		dprintf(2, VERT"(%s)"BLANC, cmd->red[x].fichier);
		dprintf(2, VERT"(%s)\t"BLANC, cmd->red[x].red);
		x++;
	}
	dprintf(2,"\n");
	dprintf(2, VERT"arg\t\t:\t"BLANC);
	x = 0;
	if (cmd->arg)
		while (cmd->arg[x] != NULL)
			dprintf(2, VERT"(%s)\t"BLANC, cmd->arg[x++]);
	else
		dprintf(2, VERT"((null))"BLANC);
	dprintf(2, "\n");
	if (cmd->pip != NULL)
		dprintf(2, VERT"redirection\t:\t%s\n"BLANC, cmd->pip);
	else
		dprintf(2, VERT"redirection\t:\t((null))\n"BLANC);
	return (1);
}
