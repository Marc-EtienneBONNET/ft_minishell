/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/18 12:22:28 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_lancement_building(void)
{
	if (ft_strncmp(g_term.cmd->red, "|", 3) == 0
		|| g_term.cmd->intra_red)
		return (-1);
	else if (ft_strncmp(g_term.cmd->cmd, "cd", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "unset", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "export", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "exit", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "pwd", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "echo", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "env", 10) == 0)
	{
		my_ex_building(g_term.cmd);
		g_term.cmd = g_term.cmd->next;
		return (1);
	}
	else
		return (-1);
}

int	my_lancement_fork(void)
{
	pid_t	pid;

	g_term.cmd->pid = fork();
	my_gestion_pip(g_term.cmd);
	if (ft_strncmp(g_term.cmd->cmd, "cd", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "unset", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "export", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "exit", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "pwd", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "echo", 10) == 0
		|| ft_strncmp(g_term.cmd->cmd, "env", 10) == 0)
	{
		if (g_term.cmd->pid == 0)
		{
			pid = my_gestion_red();
			my_ex_building(g_term.cmd);
			if (ft_strncmp(g_term.cmd->intra_red, "<<", 3) == 0)
			{
				waitpid(pid, NULL, 0);
			}
		}
	}
	else
	{
		if (g_term.cmd->pid == 0)
		{
			pid = my_gestion_red();
			my_exe_cmd(g_term, g_term.cmd);
			if (ft_strncmp(g_term.cmd->intra_red, "<<", 3) == 0)
			{
				waitpid(pid, NULL, 0);
			}
		}
	}
	g_term.cmd = g_term.cmd->next;
	return (1);
}

void	my_attente_waitpid(void)
{
	int	x;

	x = 0;
	while (x < g_term.cmd->info_cmd->nb_maillons)
	{
		waitpid(g_term.cmd->pid, &g_term.dernier_ret, 0);
		if (WIFEXITED(g_term.dernier_ret))
			g_term.dernier_ret = WEXITSTATUS(g_term.dernier_ret);
		if (g_term.dernier_ret != 0)
		{
			if (ft_strncmp(g_term.cmd->cmd, "cmd_vide", 9) == 0
				&& ft_strncmp(g_term.cmd->red, "|", 9) == 0)
			{
				while (ft_strncmp(g_term.cmd->red, ";", 3) != 0)
				{
					g_term.cmd = g_term.cmd->next;
					x++;
				}
				g_term.cmd = g_term.cmd->next;
				x++;
			}
			else
				printf(ROUGE"%s: commande introuvable\n"BLANC, g_term.cmd->cmd);
		}
		g_term.cmd = g_term.cmd->next;
		x++;
	}
}

int	my_gestion_cmd_vide(int *x)
{
	pid_t	pid;

	if (ft_strncmp(g_term.cmd->red, "|", 3) == 0)
	{
		printf("Minishell: erreur de syntaxe autoure du \"|\"\n");
		g_term.dernier_ret = -1;
		(*x) = g_term.cmd->info_cmd->nb_maillons;
		return (-1);
	}
	else if (ft_strncmp(g_term.cmd->intra_red, ">", 3) == 0
		|| ft_strncmp(g_term.cmd->intra_red, ">>", 3) == 0)
		my_ecrase_fichier(g_term.cmd, g_term.cmd->fichier_1);
	else if (ft_strncmp(g_term.cmd->intra_red, "<<", 3) == 0)
	{
		pipe(g_term.cmd->tub);
		pid = fork();
		my_heredoc(pid);
		waitpid(pid, &g_term.dernier_ret, 0);
	}
	g_term.cmd = g_term.cmd->next;
	return (1);
}

int	my_lancement_ex(void)
{
	int		x;
	int		y;
	t_cmd	*tmp;

	y = 0;
	x = 0;
	if (my_parsing() == 2)
		return (1);
	free(g_term.str_cmd);
	if (!g_term.cmd)
		return (-1);
	signal(SIGQUIT, handler_ctr_backslash);
	signal(SIGINT, handler_ctr_c_2);
	tmp = g_term.cmd;
	while (x++ < g_term.cmd->info_cmd->nb_maillons)
	{
		pipe(g_term.cmd->tub);
		if (ft_strncmp(g_term.cmd->cmd, "cmd_vide", 10) == 0)
			my_gestion_cmd_vide(&x);
		else
		{
			if (my_lancement_building() == -1)
				my_lancement_fork();
		}
	}
	g_term.cmd = tmp;
	my_attente_waitpid();
	my_kill_tub();
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(g_term.cmd);
	return (1);
}
