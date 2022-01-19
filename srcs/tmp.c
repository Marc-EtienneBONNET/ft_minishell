/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 10:40:58 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/19 10:47:43 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void my_print_struct(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf(ROUGE"debut lecture\n"BLANC);
	while (i < cmd->info_cmd->nb_maillons)
	{
		printf(VERT"maillon n : %d\n"BLANC, i);
		printf(BLEU"cmd : (%s)\n"BLANC, cmd->cmd);
		printf(BLEU"path : (%s)\n"BLANC, cmd->path);
		cmd = cmd->next;
		i++;
	}
	printf(ROUGE"FIN"BLANC);
}
