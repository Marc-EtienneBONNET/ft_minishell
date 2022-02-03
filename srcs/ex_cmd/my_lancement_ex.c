/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_lancement_ex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 08:27:33 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/03 09:20:10 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_gestion_and_ou(int	*verif, int	*verif_2)
{
	if (g_term.cmd->pid != 0)
	{
		if (ft_strcmp(g_term.cmd->prev->pip, "&&") == 0)
		{
			waitpid(g_term.cmd->prev->pid, &(*verif), 0);
			if (WIFEXITED((*verif)))
				(*verif) = WEXITSTATUS((*verif));
		}
		if (ft_strcmp(g_term.cmd->prev->pip, "||") == 0)
		{
			waitpid(g_term.cmd->prev->pid, &(*verif_2), 0);
			if (WIFEXITED((*verif_2)))
				(*verif_2) = WEXITSTATUS((*verif_2));
		}
		usleep(1000);
	}
	if ((*verif != 0 || *verif_2 == 0)
		&& my_check_building(g_term.cmd) == 1
		&& g_term.cmd->pip[0] == ';'
		&& !g_term.cmd->red)
		g_term.cmd->cmd = my_free_tab((void **)&g_term.cmd->cmd);
	return (1);
}

void	my_creat_fork(void)
{
	t_cmd	*tmp;
	int		x;
	int		verif;
	int		verif_2;

	x = 0;
	verif = 0;
	verif_2 = -1;
	tmp = g_term.cmd;
	while (x++ < g_term.nb_maillon)
	{
		g_term.cmd->pid = -1;
		my_gestion_and_ou(&verif, &verif_2);
		if (verif == 0 && verif_2 != 0)
		{
			g_term.cmd->pid = fork();
			if (g_term.cmd->pid == 0)
				return ;
		}
		else
			g_term.dernier_ret = verif;
		g_term.cmd = g_term.cmd->next;
	}
	g_term.cmd = tmp;
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
