/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:34:21 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/12 09:37:01 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_gestion_pip(t_cmd *cmd, int index)
{
	(void)index;
	if (ft_strncmp(cmd->red, "|", 3) == 0
		|| ft_strncmp(cmd->red, ">", 3) == 0
		|| ft_strncmp(cmd->red, ">>", 3) == 0
		|| ft_strncmp(cmd->red, "<", 3) == 0)
	{
		if (cmd->pid == 0)
		{
			close(cmd->tub[SORTI]);
			dup2(cmd->tub[ENTRE], 1);
		}
		else
		{
			close(cmd->tub[ENTRE]);
			dup2(cmd->tub[SORTI], 0);
		}
	}
}

void	my_kill_tub(void)
{
	int	x;

	x = 0;
	while (x < term->cmd->info_cmd->nb_maillons)
	{
		close(term->tub[ENTRE]);
		close(term->tub[SORTI]);
		dup2(ENTRE, SORTI);
		term->cmd = term->cmd->next;
		x++;
	}
}

