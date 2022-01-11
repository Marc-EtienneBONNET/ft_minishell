/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 19:34:21 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/11 15:01:26 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_gestion_pip(t_cmd *cmd, int index)
{
	(void)index;
	if (ft_strncmp(cmd->red, "|", 3) == 0
		|| ft_strncmp(cmd->red, ">", 3) == 0)
	{
		if (cmd->pid == 0)
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

void	my_kill_tub(void)
{
	close(term->tub[ENTRE]);
	close(term->tub[SORTI]);
	dup2(ENTRE, SORTI);
}

