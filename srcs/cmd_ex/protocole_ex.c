/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocole_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 15:39:01 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	message_error(void)
{
	if (g_term.dernier_ret == 255 || g_term.dernier_ret == 139)
		printf(ROUGE"Minishell: %s : command not found\n"BLANC,
			g_term.cmd->cmd);
	if (g_term.dernier_ret == -1)
		printf(ROUGE"Minishell: %s : arg incorecte\n"BLANC,
			g_term.cmd->cmd);
	return (1);
}

int	boucle_waitpid(void)
{
	int		x;
	t_cmd	*tmp;

	x = 0;
	tmp = g_term.cmd;
	while (x++ < g_term.nb_maillon)
	{
		if ((my_check_building(g_term.cmd) != 1
				|| ft_strncmp(g_term.cmd->red, "|", 3) == 0
				|| g_term.cmd->intra_red)
			&& g_term.cmd->cmd)
		{
			waitpid(g_term.cmd->pid, &g_term.dernier_ret, 0);
			if (WIFEXITED(g_term.dernier_ret))
				g_term.dernier_ret = WEXITSTATUS(g_term.dernier_ret);
		}
		message_error();
		g_term.cmd = g_term.cmd->next;
	}
	g_term.cmd = tmp;
	return (1);
}

int	my_lancement_ex(void)
{
	if (my_parsing() < 0)
		return (1);
	//my_print_list_chene(g_term.cmd);
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
