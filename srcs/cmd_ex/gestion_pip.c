/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_pip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:34:21 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/20 09:40:18 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_tub_entre_sorti_enfant(t_cmd *cmd)
{
	if (ft_strncmp(cmd->red, "|", 3) == 0)
	{
		close(cmd->next->tub[SORTI]);
		dup2(cmd->next->tub[ENTRE], 1);
		close(cmd->next->tub[ENTRE]);
	}
	if (ft_strncmp(cmd->previous->red, "|", 3) == 0)
	{
		close(cmd->tub[ENTRE]);
		dup2(cmd->tub[SORTI], 0);
		close(cmd->tub[SORTI]);
	}
}

void	my_close_pip(t_cmd *cmd)
{
	close(cmd->tub[ENTRE]);
	close(cmd->tub[SORTI]);
}

/*
void	my_gestion_pip(t_cmd *cmd)
{
	if (ft_strncmp(cmd->red, "|", 3) == 0)
	{
		if (cmd->pid == 0)
			my_tub_entre_sorti_enfant(cmd);
		else
			my_tub_sorti_entre_parent(cmd);
	}
}
*/
void	my_kill_tub(void)
{
	int	x;

	x = 0;
	while (x < g_term.cmd->info_cmd->nb_maillons)
	{
		if (ft_strncmp(g_term.cmd->cmd, "cmd_vide", 9) == 0)
			return ;
		dup2(ENTRE, SORTI);
		//dup2(g_term.save_stdin, 0);
		//dup2(g_term.save_stdout, 1);
		g_term.cmd = g_term.cmd->next;
		x++;
	}
}
