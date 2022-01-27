/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_pip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:34:21 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 11:46:36 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_tub_entre_sorti_enfant(t_cmd *cmd)
{
	if (ft_strncmp(cmd->red, "|", 3) == 0)
	{
		//dprintf(2,"cmd\n");
		//my_print_maillon(cmd, 0);
		close(cmd->next->tub[SORTI]);
		dup2(cmd->next->tub[ENTRE], 1);
		close(cmd->next->tub[ENTRE]);
	}
	if (ft_strncmp(cmd->previous->red, "|", 3) == 0)
	{
		//dprintf(2,"previous\n");
		//my_print_maillon(cmd, 0);
		close(cmd->tub[ENTRE]);
		dup2(cmd->tub[SORTI], 0);
		close(cmd->tub[SORTI]);
	}
	else
		my_close_pip(cmd);
}

void	my_close_pip(t_cmd *cmd)
{
	//dprintf(2,"cmd : %s\t pid : %d\n", cmd->cmd, cmd->pid);
	close(cmd->tub[ENTRE]);
	close(cmd->tub[SORTI]);
}
