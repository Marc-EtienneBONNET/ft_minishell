/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hendler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/06 16:26:21 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_ctr_c(int code)
{
	(void)code;
	int	x;

	x = 0;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (term->str_cmd)
	{
		free(term->str_cmd);
		term->str_cmd = NULL;
	}
}

void	handler_ctr_c_2(int code)
{
	(void)code;
	int	x;

	x = 0;
	printf("\n");
	if (term->str_cmd)
	{
		free(term->str_cmd);
		term->str_cmd = NULL;
	}
}
