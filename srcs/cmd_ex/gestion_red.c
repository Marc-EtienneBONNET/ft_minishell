/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:34:21 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/11 09:06:59 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_gestion_pip(t_cmd *cmd, int index)
{
	if (ft_strncmp(cmd->red, "|", 3) == 0)
	{
		if (term->pid[index] == 0)
		{
			close(term->tub[SORTI]);
			dup2(term->tub[ENTRE], 1);
		}
		else
		{
			close(term->tub[ENTRE]);
			dup2(term->tub[SORTI], 0);
		}
	}
}

void	my_kill_tub()
{
	close(term->tub[ENTRE]);
	close(term->tub[SORTI]);
	dup2(ENTRE, SORTI);
}

void	my_gestion_red(int res, int x)
{
	int		y;
	t_cmd *cmd_tmp;

	y = 0;
	cmd_tmp = term->cmd;
	if (res != 0)
	{
		while (y < x -1)
		{
			y++;
			cmd_tmp = cmd_tmp->next;
		}
		printf("%s : commande introuvable\n", cmd_tmp->cmd);
	}
}
