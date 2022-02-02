/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gestion_tub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:24:41 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/02 12:16:04 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_close_pip(t_cmd *cmd)
{
	close(cmd->tub[ENTRE]);
	close(cmd->tub[SORTI]);
}

void	my_connect_tub(void)
{
	if (ft_strncmp(g_term.cmd->pip, "|", 3) == 0)
	{
		close(g_term.cmd->tub[SORTI]);
		dup2(g_term.cmd->tub[ENTRE], 1);
		close(g_term.cmd->tub[ENTRE]);
	}
	else
	{
		my_close_pip(g_term.cmd);
	}
	if (ft_strncmp(g_term.cmd->prev->pip, "|", 3) == 0)
	{
		close(g_term.cmd->prev->tub[ENTRE]);
		dup2(g_term.cmd->prev->tub[SORTI], 0);
		close(g_term.cmd->prev->tub[SORTI]);
	}
}

void	my_close_tub_parent(void)
{
	t_cmd	*tmp;
	int		x;

	x = 0;
	tmp = g_term.cmd;
	while (x++ < g_term.nb_maillon)
	{
		my_close_pip(g_term.cmd);
		g_term.cmd = g_term.cmd->next;
	}
	g_term.cmd = tmp;
}

void	my_creat_tub(void)
{
	t_cmd	*tmp;
	int		x;

	x = 0;
	tmp = g_term.cmd;
	while (x++ < g_term.nb_maillon)
	{
		pipe(g_term.cmd->tub);
		g_term.cmd = g_term.cmd->next;
	}
	g_term.cmd = tmp;
}
