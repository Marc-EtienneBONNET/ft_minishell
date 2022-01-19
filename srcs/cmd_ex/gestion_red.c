/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:07:30 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/19 11:37:41 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_choose_fichier(t_cmd *cmd)
{
	char	*res;

	if (ft_strncmp(cmd->path, cmd->previous->path, 7) == 0)
	{
		res = ft_strjoin("./", cmd->cmd);
	}
	else
		res = ft_strjoin(cmd->path, cmd->cmd);
	if (!res)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

void	my_ecrase_fichier(t_cmd *cmd, char *fichier)
{
	int	fd;

	if (ft_strncmp(cmd->intra_red, ">", 3) == 0)
	{
		fd = open(fichier, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			remove(fichier);
		}
		else
			close(fd);
	}
	if (ft_strncmp(cmd->intra_red, ">", 3) == 0
		|| ft_strncmp(cmd->intra_red, ">>", 3) == 0)
	{
		fd = open(fichier, O_RDONLY);
		if (fd == -1)
			fd = open(fichier, O_CREAT);
		if (fd > -1)
			close(fd);
	}
}

int	my_gestion_fichier(t_cmd *cmd)
{
	int		fd;
	char	c;

	if (ft_strncmp(cmd->intra_red, "<", 3) == 0)
		return (open(cmd->fichier_1, O_RDWR));
	my_ecrase_fichier(cmd, cmd->fichier_1);
	if (ft_strncmp(cmd->intra_red, ">", 3) == 0
		|| ft_strncmp(cmd->intra_red, ">>", 3) == 0)
		fd = open(cmd->fichier_1, O_RDWR);
	if (ft_strncmp(cmd->intra_red, ">>", 3) == 0)
		while (read(fd, &c, 1) > 0)
			c = 'a';
	return (fd);
}

pid_t	my_gestion_red(void)
{
	int		fd;
	pid_t	pid;

	pid = -1;
	if (!g_term.cmd->intra_red)
		return (pid);
	if (ft_strncmp(g_term.cmd->intra_red, "<<", 3) == 0)
	{
		pipe(g_term.cmd->tub);
		pid = fork();
		my_heredoc(pid);
	}
	else if (ft_strncmp(g_term.cmd->intra_red, "<", 3) == 0
		|| ft_strncmp(g_term.cmd->intra_red, ">", 3) == 0
		|| ft_strncmp(g_term.cmd->intra_red, ">>", 3) == 0)
	{
		fd = my_gestion_fichier(g_term.cmd);
		if (ft_strncmp(g_term.cmd->intra_red, "<", 3) == 0)
			dup2(fd, 0);
		else if (ft_strncmp(g_term.cmd->intra_red, ">", 3) == 0
			|| ft_strncmp(g_term.cmd->intra_red, ">>", 3) == 0)
			dup2(fd, 1);
		close(fd);
	}
	return (pid);
}
