/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:18:33 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/08 08:46:01 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_create_tub(t_cmd *cmd)
{
	if (ft_strncmp(cmd->red, ";", 3) != 0
		&& ft_strncmp(cmd->red, "&&", 3) != 0
		&& ft_strncmp(cmd->red, "||", 3) != 0)
	{
		if (term->pid == 0)
		{
			close(term->tub[SORTI]);
			dup2(term->tub[ENTRE], 1);
			close(term->tub[ENTRE]);
		}
		else
		{
			close(term->tub[ENTRE]);
			dup2(term->tub[SORTI], 0);
			close(term->tub[SORTI]);
		}
	}
}


void	my_kill_tub(t_cmd *cmd)
{
	if (ft_strncmp(cmd->red, ";", 3) != 0
		&& ft_strncmp(cmd->red, "&&", 3) != 0
		&& ft_strncmp(cmd->red, "||", 3) != 0)
	{
		if (term->pid != 0)
		{
			dup2(ENTRE, SORTI);
		}
	}
}

