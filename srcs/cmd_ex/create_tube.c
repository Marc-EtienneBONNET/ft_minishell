/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:18:33 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/07 18:56:45 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_creat_tub(void)
{
	if (term->pid == 0)
	{
		printf("coucou 1\n");
		pipe(term->tub);
		dup2(term->tub[ENTRE], 1);
		close(term->tub[ENTRE]);
	}
}

void	my_liaison_tub(void)
{
	if (term->pid == 0)
	{
		printf("coucou 2\n");
		dup2(term->tub[SORTI], 0);
		close(term->tub[SORTI]);
	}
}

void	my_kill_tub(t_cmd *cmd)
{
	(void)cmd;
	
}
