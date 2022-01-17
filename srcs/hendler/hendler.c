/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hendler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 18:06:53 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_ctr_c(int code)
{
	int	x;

	x = 0;
	(void)code;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	//my_free_liste_chene(g_term->cmd);
}

void	handler_ctr_c_2(int code)
{
	int	x;

	(void)code;
	x = 0;
	printf("\n");
}

void	handler_ctr_backslash(int code)
{
	(void)code;
	printf(ROUGE"Quitter (core dumped)\n"BLANC);
}
