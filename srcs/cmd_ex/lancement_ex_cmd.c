/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/13 09:09:25 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_lancement_building(void)
{
	if (ft_strncmp(term->cmd->cmd, "cd", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "unset", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "export", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "exit", 10) == 0
		|| ft_strncmp(term->cmd->previous->red, ">", 10) == 0
		|| ft_strncmp(term->cmd->previous->red, ">>", 10) == 0)
	{
		if (ft_strncmp(term->cmd->previous->red, ">", 10) == 0
			|| ft_strncmp(term->cmd->previous->red, ">>", 10) == 0)
			my_gestion_red_droite(term->cmd->previous->red);
		my_ex_building(term->cmd);
		return (1);
	}
	else
		return (-1);
}

int	my_lancement_fork(void)
{
	term->cmd->pid = fork();
	my_gestion_pip(term->cmd, 0);
	if (ft_strncmp(term->cmd->cmd, "pwd", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "echo", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "env", 10) == 0)
	{
		if (term->cmd->pid == 0)
			my_ex_building(term->cmd);
	}
	else if (ft_strncmp(term->cmd->previous->red, "<", 10) == 0)
	{
		if (term->cmd->pid == 0)
			exit (0);
		return (0);
	}
	else
	{
		//write(2, term->cmd->cmd, ft_strlen(term->cmd->cmd));
		if (ft_strncmp(term->cmd->red, "<", 3) == 0 && term->cmd->pid != 0)
		{
			my_gestion_red_gauche();
		}
		if (term->cmd->pid == 0)
		{
			write(2, "salut\n", ft_strlen("salut\n"));
			my_exe_cmd(term, term->cmd);
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
			printf("%s: commande introuvable\n", term->cmd->cmd);
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
	term->cmd = my_parsing(term->str_cmd);
	free(term->str_cmd);
	signal(SIGQUIT, handler_ctr_backslash);
	signal(SIGINT, handler_ctr_c_2);
	tmp = term->cmd;
	while (x++ < term->cmd->info_cmd->nb_maillons)
	{
		pipe(term->cmd->tub);
		if (my_lancement_building() == -1)
		{
			my_lancement_fork();
		}
	}
	term->cmd = tmp;
	my_attente_waitpid();
	my_kill_tub();
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(term->cmd);
	return (1);
}
