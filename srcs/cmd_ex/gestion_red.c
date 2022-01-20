/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:44:24 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/20 17:04:43 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_recup_fd_fichier(t_cmd *cmd)
{
	int		fd;
	char	c;

	if (ft_strncmp(g_term.cmd->intra_red, ">", 3) == 0)
	{
		fd = open(cmd->fichier_1, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			if (remove(cmd->fichier_1) != 0)
				return (-1);
		}
		fd = open(cmd->fichier_1, O_RDONLY);
		if (fd == -1)
			fd = open(cmd->fichier_1, O_CREAT);
		else
			close(fd);
	}
	if (ft_strncmp(g_term.cmd->intra_red, ">>", 3) == 0
		|| ft_strncmp(g_term.cmd->intra_red, ">", 3) == 0
		|| ft_strncmp(g_term.cmd->intra_red, "<", 3) == 0)
	{
		fd = open(cmd->fichier_1, O_RDWR);
		if (ft_strncmp(g_term.cmd->intra_red, "<", 3) != 0)
			while (read(fd, &c, 1) > 0)
				c = 'a';
		if (fd == -1)
			return (-1);
		return (fd);
	}
	return (fd);
}

pid_t	my_gestion_red(t_cmd *cmd)
{
	int		fd;
	int		tub[2];
	pid_t	pid;


	fd = 0;
	pid = -1;
	if (cmd->pid == 0 && cmd->intra_red)
	{
		if (ft_strncmp(g_term.cmd->intra_red, ">", 3) == 0
			|| ft_strncmp(g_term.cmd->intra_red, ">>", 3) == 0
			|| ft_strncmp(g_term.cmd->intra_red, "<", 3) == 0)
		{
			fd = my_recup_fd_fichier(cmd);
			if (ft_strncmp(g_term.cmd->intra_red, ">", 3) == 0
				|| ft_strncmp(g_term.cmd->intra_red, ">>", 3) == 0)
				dup2(fd, 1);
			else if (ft_strncmp(g_term.cmd->intra_red, "<", 3) == 0)
				dup2(fd, 0);
			close(fd);
		}
		else if (ft_strncmp(g_term.cmd->intra_red, "<<", 3) == 0)
		{
			pipe(tub);
			pid = fork();
			my_heredoc(pid, tub);
			return (pid);
		}
	}
	return (-1);
}
