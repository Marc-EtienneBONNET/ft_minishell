/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/06 09:39:56 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	*my_cloture_pid()
{
	pid_t	*pid;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!term->pid_cmd)
		return (NULL);
	while (term->pid_cmd[x] != -1)
		x++;
	if (x == 1)
	{
		free(term->pid_cmd);
		return (NULL);
	}
	x--;
	pid = malloc(sizeof(pid_t) * (x + 1));
	while (y < x)
	{
		pid[y] = term->pid_cmd[y];
		y++;
	}
	pid[y] = -1;
	free(term->pid_cmd);
	term->pid_cmd = pid;
	return (term->pid_cmd);
}

pid_t	*my_ajoue_pid()
{
	pid_t	*pid;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (term->pid_cmd && term->pid_cmd[x] != -1)
		x++;
	pid = malloc(sizeof(pid_t) * (x + 2));
	while (y < x)
	{
		pid[y] = term->pid_cmd[y];
		y++;
	}
	pid[y++] = getpid();
	pid[y] = -1;
	free(term->pid_cmd);
	term->pid_cmd = pid;
	return (term->pid_cmd);
}

void	*my_exe_cmd(t_term *term)
{
	char	*cpe;

	cpe = term->cmd->cmd;
	if (my_ajoue_pid() == NULL)
		return (NULL);
	while (1)
	{
		printf("enfant\n");
		usleep(1000000);
	}
	printf("process enfant\n");
	if (ft_strncmp(cpe, "ls", 10) == 0
		|| ft_strncmp(cpe, "cd", 10) == 0
		|| ft_strncmp(cpe, "pwd", 10) == 0
		|| ft_strncmp(cpe, "echo", 10) == 0
		|| ft_strncmp(cpe, "export", 10) == 0
		|| ft_strncmp(cpe, "unset", 10) == 0
		|| ft_strncmp(cpe, "env", 5) == 0
		|| ft_strncmp(cpe, "exit", 5) == 0)
	{
		printf("fonction en cours de codage\n");
	}
	else
		execve(ft_strjoin("/bin/", term->cmd->cmd), term->cmd->arg, term->envp);
	my_cloture_pid();
	return (NULL);
}
