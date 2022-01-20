/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_pip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:34:21 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/20 12:08:44 by mbonnet          ###   ########.fr       */
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
