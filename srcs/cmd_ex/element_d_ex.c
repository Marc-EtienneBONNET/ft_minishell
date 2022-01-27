/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_d_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:12:05 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 11:57:10 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	creat_pipe(void)
{
	int		x;
	t_cmd	*tmp;

	x = 0;
	tmp = g_term.cmd;
	while (x++ < g_term.nb_maillon)
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
	while (x < g_term.nb_maillon)
	{
		if ((my_check_building(g_term.cmd) != 1
				|| ft_strncmp(g_term.cmd->red, "|", 3) == 0
				|| g_term.cmd->intra_red)
			&& g_term.cmd->cmd)
		{
			g_term.cmd->pid = fork();
			if (g_term.cmd->pid == 0)
			{
				my_tub_entre_sorti_enfant(g_term.cmd);
				break ;
			}
		}
		else
			g_term.cmd->pid = -1;
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
	while (x < g_term.nb_maillon)
	{
		if (ft_strncmp(g_term.cmd->red, "|", 3) == 0)
			my_close_pip(g_term.cmd->next);
		g_term.cmd = g_term.cmd->next;
		x++;
	}
	g_term.cmd = cmd_tmp;
	return (1);
}

int	boucle_ex_fork(pid_t pid)
{
	if ((my_check_building(g_term.cmd) == 1
			&& (ft_strncmp(g_term.cmd->red, "|", 3) == 0
				|| g_term.cmd->intra_red)))
		my_ex_building(g_term.cmd);
	else
		my_exe_cmd(g_term, g_term.cmd);
	if (ft_strncmp(g_term.cmd->intra_red, "<<", 3) == 0)
		waitpid(pid, NULL, 0);
	return (1);
}

int	boucle_ex(void)
{
	int		x;
	t_cmd	*tmp;
	pid_t	pid;

	x = 0;
	tmp = g_term.cmd;
	while (x++ < g_term.nb_maillon)
	{
		pid = my_gestion_red(g_term.cmd);
		if ((my_check_building(g_term.cmd) == 1
				&& ft_strncmp(g_term.cmd->red, "|", 3) != 0
				&& !g_term.cmd->intra_red))
			g_term.dernier_ret = my_ex_building(g_term.cmd);
		else if (g_term.cmd->pid == 0)
			boucle_ex_fork(pid);
		g_term.cmd = g_term.cmd->next;
	}
	g_term.cmd = tmp;
	return (1);
}
