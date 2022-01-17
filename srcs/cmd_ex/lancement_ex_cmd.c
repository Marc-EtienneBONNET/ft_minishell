/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 17:44:26 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_lancement_building(void)
{
	if (ft_strncmp(term->cmd->red, "|", 3) == 0
		|| term->cmd->intra_red )
		return (-1);
	else if (ft_strncmp(term->cmd->cmd, "cd", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "unset", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "export", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "exit", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "pwd", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "echo", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "env", 10) == 0)
	{
		my_ex_building(term->cmd);
		term->cmd = term->cmd->next;
		return (1);
	}
	else
		return (-1);
}

int	my_lancement_fork(void)
{
	pid_t	pid;

	term->cmd->pid = fork();
	my_gestion_pip(term->cmd);
	if (ft_strncmp(term->cmd->cmd, "cd", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "unset", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "export", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "exit", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "pwd", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "echo", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "env", 10) == 0)
	{
		if (term->cmd->pid == 0)
		{
			pid = my_gestion_red();
			my_ex_building(term->cmd);
			if (ft_strncmp(term->cmd->intra_red, "<<", 3) == 0)
			{
				waitpid(pid, NULL, 0);
			}
		}
	}
	else
	{
		if (term->cmd->pid == 0)
		{
			pid = my_gestion_red();
			my_exe_cmd(term, term->cmd);
			if (ft_strncmp(term->cmd->intra_red, "<<", 3) == 0)
			{
				waitpid(pid, NULL, 0);
			}
		}
	}
	term->cmd = term->cmd->next;
	return (1);
}

void	my_attente_waitpid(void)
{
	int	x;

	x = 0;
	while (x < term->cmd->info_cmd->nb_maillons)
	{
		waitpid(term->cmd->pid, &term->dernier_ret, 0);
		if (WIFEXITED(term->dernier_ret))
			term->dernier_ret = WEXITSTATUS(term->dernier_ret);
		if (term->dernier_ret != 0)
			printf(ROUGE"%s: commande introuvable\n"BLANC, term->cmd->cmd);
		term->cmd = term->cmd->next;
		x++;
	}
}

int	my_lancement_ex(void)
{
	int		x;
	int		y;
	t_cmd	*tmp;

	y = 0;
	x = 0;
	if (my_parsing() == 2)
	{
		//my_free_liste_chene(term->cmd);
		return (1);
	}
	free(term->str_cmd);
	if (!term->cmd)
		return (-1);
	signal(SIGQUIT, handler_ctr_backslash);
	signal(SIGINT, handler_ctr_c_2);
	tmp = term->cmd;
	while (x++ < term->cmd->info_cmd->nb_maillons)
	{
		pipe(term->cmd->tub);
		if (my_lancement_building() == -1)
			my_lancement_fork();
	}
	term->cmd = tmp;
	my_attente_waitpid();
	my_kill_tub();
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(term->cmd);
	return (1);
}
