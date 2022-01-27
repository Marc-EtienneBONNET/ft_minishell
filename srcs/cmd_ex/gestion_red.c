/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:44:24 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 14:10:57 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_check_type_red(char *str)
{
	if (ft_strncmp(str, ">>", 3) == 0
		|| ft_strncmp(str, ">", 3) == 0
		|| ft_strncmp(str, "<", 3) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (2);
	return (0);
}

int	my_ecrase_fichier(t_cmd *cmd)
{
	int		fd;

	if (ft_strncmp(cmd->intra_red, ">", 3) == 0)
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
	return (1);
}

int	my_recup_fd_fichier(t_cmd *cmd)
{
	int		fd;
	char	c;

	fd = -1;
	my_ecrase_fichier(cmd);
	if (my_check_type_red(g_term.cmd->intra_red) == 1)
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

pid_t	my_gestion_red_2(int *tub)
{
	pid_t	pid;

	pipe(tub);
	pid = fork();
	if (!g_term.cmd->fichier_2)
		my_heredoc(pid, tub, g_term.cmd->fichier_2,
			g_term.cmd->fichier_1);
	else if (g_term.cmd->fichier_2)
		my_heredoc(pid, tub, g_term.cmd->fichier_1,
			g_term.cmd->fichier_2);
	return (pid);
}

pid_t	my_gestion_red(t_cmd *cmd)
{
	int		fd;
	int		tub[2];

	if (cmd->pid == 0 && cmd->intra_red)
	{
		if (my_check_type_red(g_term.cmd->intra_red) == 1)
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
			return (my_gestion_red_2(tub));
	}
	return (-1);
}
