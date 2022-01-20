/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocole_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/20 12:12:32 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_lancement_ex(void)
{
	int		x;

	x = 0;
	if (my_parsing() == 2)
		return (1);
	free(g_term.str_cmd);
	if (!g_term.cmd)
		return (-1);
	g_term.save_stdin = dup(0);
	g_term.save_stdout = dup(1);
	signal(SIGQUIT, handler_ctr_backslash);
	signal(SIGINT, handler_ctr_c_2);
	creat_pipe();
	creat_fork();
	boucle_close_tub();
	boucle_ex();
	if (g_term.cmd->pid != 0)
		boucle_waitpid();
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(g_term.cmd);
	return (1);
}
