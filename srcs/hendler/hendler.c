/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hendler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/06 09:47:47 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_ctr_c(int code)
{
	(void)code;
	int	x;

	x = 0;
	if (term->pid_cmd)
	{
		while (term->pid_cmd[x] != -1)
			x++;
		x--;
		kill(term->pid_cmd[x], SIGKILL);
		my_cloture_pid();
	}
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (term->str_cmd)
	{
		free(term->str_cmd);
		term->str_cmd = NULL;
	}
}


