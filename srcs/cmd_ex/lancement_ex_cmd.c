/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/11 11:19:23 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_realloc_tab()
{
	int		len;
	pid_t	*pid;

	len = 0;
	while (term->pid && term->pid[len] != -1)
		len++;
	pid = malloc(sizeof(pid_t) * (len + 2));
	if (!pid)
		return (-1);
	len = 0;
	while (term->pid && term->pid[len] != -1)
	{
		pid[len] = term->pid[len];
		len++;
	}
	if (term->pid)
		free(term->pid);
	len++;
	pid[len] = -1;
	term->pid = pid;
	return (--len);
}

int	my_lancement_fork(void)
{
	int		index;
	int		res;

	res = 0;
	index = my_realloc_tab();
	term->pid[index] = fork();
	my_gestion_pip(term->cmd, index);
	if (ft_strncmp(term->cmd->cmd, "cd", 10) == 0
		&& ft_strncmp(term->cmd->cmd, "pwd", 10) == 0
		&& ft_strncmp(term->cmd->cmd, "echo", 10) == 0
		&& ft_strncmp(term->cmd->cmd, "export", 10) == 0
		&& ft_strncmp(term->cmd->cmd, "unset", 10) == 0
		&& ft_strncmp(term->cmd->cmd, "env", 10) == 0
		&& ft_strncmp(term->cmd->cmd, "exit", 10) == 0)
	{
		if (term->pid[index] == 0)
			exit (0);
		res = 1;
		my_ex_building(term->cmd);
		term->cmd = term->cmd->next;
		return (1);
	}
	if (term->pid[index] == 0)
		my_exe_cmd(term, term->cmd);
	term->cmd = term->cmd->next;
	return (1);
}

int	my_lancement_ex(void)
{
	int		x;

	x = 0;
	term->cmd = my_parsing(term->str_cmd);
	term->pid = NULL;
	free(term->str_cmd);
	signal(SIGQUIT, handler_ctr_backslash);
	signal(SIGINT, handler_ctr_c_2);
	pipe(term->tub);
	while (x++ < term->cmd->info_cmd->nb_maillons)
		my_lancement_fork();
	x = 0;
	while (term->pid && term->pid[x] != -1)
	{
		waitpid(term->pid[x++], &term->dernier_ret, 0);
		if (WIFEXITED(term->dernier_ret))
			term->dernier_ret = WEXITSTATUS(term->dernier_ret);
	}
	free(term->pid);
	my_kill_tub();
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(term->cmd);
	return (1);
}
