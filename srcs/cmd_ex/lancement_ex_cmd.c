/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/11 09:03:43 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_lancement_building(t_cmd *cmd)
{
	char	*cpe;

	cpe = cmd->cmd;
	if (ft_strncmp(cpe, "cd", 10) == 0)
		printf("commande cd\n");
	else if (ft_strncmp(cpe, "pwd", 10) == 0)
		my_pwd(cmd);
	else if (ft_strncmp(cpe, "echo", 10) == 0)
		my_echo(cmd->arg);
	else if (ft_strncmp(cpe, "export", 10) == 0)
		printf("commande export\n");
	else if (ft_strncmp(cpe, "unset", 10) == 0)
		printf("commande unset\n");
	else if (ft_strncmp(cpe, "env", 5) == 0)
		my_env(cmd);
	else if (ft_strncmp(cpe, "exit", 5) == 0)
		printf("commande exit\n");
}

int	my_exe_cmd(t_term *term, t_cmd *cmd)
{
	char	*cpe;

	cpe = cmd->cmd;
	if (ft_strncmp(cpe, "cd", 10) == 0
		|| ft_strncmp(cpe, "pwd", 10) == 0
		|| ft_strncmp(cpe, "echo", 10) == 0
		|| ft_strncmp(cpe, "export", 10) == 0
		|| ft_strncmp(cpe, "unset", 10) == 0
		|| ft_strncmp(cpe, "env", 5) == 0
		|| ft_strncmp(cpe, "exit", 5) == 0)
		my_lancement_building(cmd);
	else
	{
		cpe = ft_strjoin(cmd->path, cmd->cmd);
		if (execve(cpe, cmd->arg, term->envp) == -1)
		{
			free(cpe);
			exit (-1);
		}
		free(cpe);
	}
	return (1);
}

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

void	my_lancement_fork(void)
{
	int		index;

	index = my_realloc_tab();
	term->pid[index] = fork();
	my_gestion_pip(term->cmd, index);
	if (term->pid[index] == 0)
		my_exe_cmd(term, term->cmd);
	term->cmd = term->cmd->next;
}

int	my_lancement_ex(void)
{
	int		res;
	int		x;
	t_cmd *tmp;

	x = 0;
	res = 10;
	term->cmd = my_parsing(term->str_cmd);
	term->pid = NULL;
	free(term->str_cmd);
	signal(SIGQUIT, handler_ctr_backslash);
	signal(SIGINT, handler_ctr_c_2);
	pipe(term->tub);
	tmp = term->cmd;
	while (x++ < term->cmd->info_cmd->nb_maillons)
		my_lancement_fork();
	term->cmd = tmp;
	x = 0;
	while (term->pid[x] != -1)
	{
		waitpid(term->pid[x++], &res, 0);
		if (WIFEXITED(res))
			res = WEXITSTATUS(res);
		my_gestion_red(res, x);
	}
	free(term->pid);
	term->pid = NULL;
	my_kill_tub();
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(term->cmd);
	return (1);
}
