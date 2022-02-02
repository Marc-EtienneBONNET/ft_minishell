/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_lancement_ex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 08:27:33 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/02 12:24:06 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_creat_fork(void)
{
	t_cmd	*tmp;
	int		x;

	x = 0;
	tmp = g_term.cmd;
	while (x++ < g_term.nb_maillon)
	{
		g_term.cmd->pid = fork();
		if (g_term.cmd->pid == 0)
			return ;
		else
			usleep(10);
		g_term.cmd = g_term.cmd->next;
	}
	g_term.cmd = tmp;
}

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

void	my_boucle_waitpid(void)
{
	t_cmd	*tmp;
	int		x;

	x = 0;
	tmp = g_term.cmd;
	if (g_term.cmd->pid != 0)
	{
		while (x++ < g_term.nb_maillon)
		{
			waitpid(g_term.cmd->pid, &g_term.dernier_ret, 0);
			if (WIFEXITED(g_term.dernier_ret))
				g_term.dernier_ret = WEXITSTATUS(g_term.dernier_ret);
			g_term.cmd = g_term.cmd->next;
		}
		message_error();
	}
	g_term.cmd = tmp;
}

int	my_lancement_ex_2(void)
{
	my_creat_tub();
	my_creat_fork();
	my_gestion_var_env_and_gui(g_term.cmd);
	if (g_term.cmd->pid == 0)
	{
		my_connect_tub();
		if (my_connect_red() == -1)
			return (-1);
		my_connect_heredoc();
	}
	my_close_tub_parent();
	my_exe_cmd();
	my_boucle_waitpid();
	return (1);
}

int	my_lancement_ex(void)
{
	int	parsing;

	parsing = my_init_parsing();
	if (parsing != 0)
	{
		if (parsing == 3 || parsing == -1)
			printf(ROUGE"Minishell: erreur de syntax\n"BLANC);
		my_free_liste_chene(g_term.cmd);
		return (1);
	}
	signal(SIGQUIT, handler_ctr_backslash);
	signal(SIGINT, handler_ctr_c_2);
	my_lancement_ex_2();
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(g_term.cmd);
	return (1);
}
