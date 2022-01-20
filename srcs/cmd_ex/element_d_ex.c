/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_d_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:12:05 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/20 18:04:07 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	creat_pipe(void)
{
	int		x;
	t_cmd	*tmp;

	x = 0;
	tmp = g_term.cmd;
	while (x++ < g_term.cmd->info_cmd->nb_maillons)
	{
		pipe(g_term.cmd->tub);
		g_term.cmd = g_term.cmd->next;
	}
	g_term.cmd = tmp;
	return (1);
}

int	creat_fork(void)
{
	int		x;
	t_cmd	*cmd_tmp;

	x = 0;
	cmd_tmp = g_term.cmd;
	while (x < g_term.cmd->info_cmd->nb_maillons)
	{
		if ((my_check_building(g_term.cmd) != 1
				|| ft_strncmp(g_term.cmd->red, "|", 3) == 0
				|| g_term.cmd->intra_red)
			&& ft_strncmp(g_term.cmd->cmd, "cmd_vide", 9) != 0)
		{
			g_term.cmd->pid = fork();
			if (g_term.cmd->pid == 0)
			{
				my_tub_entre_sorti_enfant(g_term.cmd);
				break ;
			}
		}
		g_term.cmd = g_term.cmd->next;
		x++;
	}
	g_term.cmd = cmd_tmp;
	return (1);
}

int	boucle_close_tub(void)
{
	int		x;
	t_cmd	*cmd_tmp;

	x = 0;
	cmd_tmp = g_term.cmd;
	while (x < g_term.cmd->info_cmd->nb_maillons)
	{
		if (g_term.cmd->pid != 0)
		{
			if (x == 0)
				my_close_pip(g_term.cmd);
			if (ft_strncmp(g_term.cmd->red, "|", 3) == 0)
				my_close_pip(g_term.cmd->next);
		}
		g_term.cmd = g_term.cmd->next;
		x++;
	}
	g_term.cmd = cmd_tmp;
	return (1);
}

int	boucle_ex(void)
{
	int		x;
	t_cmd	*tmp;
	pid_t	pid;

	x = 0;
	tmp = g_term.cmd;
	while (x++ < g_term.cmd->info_cmd->nb_maillons)
	{
		pid = my_gestion_red(g_term.cmd);
		if ((my_check_building(g_term.cmd) == 1
				&& ft_strncmp(g_term.cmd->red, "|", 3) != 0
				&& !g_term.cmd->intra_red))
			g_term.dernier_ret = my_ex_building(g_term.cmd);
		else if (g_term.cmd->pid == 0)
		{
			if ((my_check_building(g_term.cmd) == 1
					&& (ft_strncmp(g_term.cmd->red, "|", 3) == 0
						|| g_term.cmd->intra_red)))
				my_ex_building(g_term.cmd);
			else
			{
				my_exe_cmd(g_term, g_term.cmd);
				if (ft_strncmp(g_term.cmd->intra_red, "<<", 3) == 0)
					waitpid(pid, NULL, 0);
			}
		}
		g_term.cmd = g_term.cmd->next;
	}
	g_term.cmd = tmp;
	return (1);
}

int	boucle_waitpid(void)
{
	int		x;
	t_cmd	*tmp;

	x = 0;
	tmp = g_term.cmd;
	while (x++ < g_term.cmd->info_cmd->nb_maillons)
	{
		if ((my_check_building(g_term.cmd) != 1
				|| ft_strncmp(g_term.cmd->red, "|", 3) == 0
				|| g_term.cmd->intra_red)
			&& ft_strncmp(g_term.cmd->cmd, "cmd_vide", 9) != 0)
		{
			waitpid(g_term.cmd->pid, &g_term.dernier_ret, 0);
			if (WIFEXITED(g_term.dernier_ret))
				g_term.dernier_ret = WEXITSTATUS(g_term.dernier_ret);
			if (g_term.dernier_ret == 255 || g_term.dernier_ret == 139)
				printf(ROUGE"Minishell: %s : command not found\n"BLANC, g_term.cmd->cmd);
		}
		g_term.cmd = g_term.cmd->next;
	}
	g_term.cmd = tmp;
	return (1);
}