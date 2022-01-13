/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:07:30 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/13 11:52:03 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_choose_fichier(t_cmd *cmd)
{
	char	*res;

	if (ft_strncmp(cmd->path, "/bin/", 7) == 0)
		res = ft_strjoin("./", cmd->cmd);
	else
		res = ft_strjoin(cmd->path, cmd->cmd);
	return (res);
}

void	my_ecrase_fichier(t_cmd *cmd, char *fichier)
{
	int	fd;

	if (ft_strncmp(cmd->previous->red, ">", 3) == 0)
	{
		fd = open(fichier, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			remove(fichier);
		}
		else
			close(fd);
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
	char	*fichier;
	char	c;

	fichier = my_choose_fichier(cmd);
	if (ft_strncmp(cmd->previous->red, "<", 3) == 0)
		return (open(fichier, O_RDWR));
	my_ecrase_fichier(cmd, fichier);
	if (ft_strncmp(cmd->previous->red, ">", 3) == 0
		|| ft_strncmp(cmd->previous->red, ">>", 3) == 0)
		fd = open(fichier, O_RDWR);
	if (ft_strncmp(cmd->previous->red, ">>", 3) == 0)
		while (read(fd, &c, 1) > 0);
	free(fichier);
	return (fd);
}

int	my_gestion_red(void)
{
	int		fd;

	if (ft_strncmp(term->cmd->red, "<", 3) == 0
		|| ft_strncmp(term->cmd->red, ">", 3) == 0
		|| ft_strncmp(term->cmd->red, ">>", 3) == 0)
	{
		fd = my_gestion_fichier(term->cmd->next);
		if (ft_strncmp(term->cmd->red, "<", 3) == 0)
			dup2(fd, 0);
		else if (ft_strncmp(term->cmd->red, ">", 3) == 0
			|| ft_strncmp(term->cmd->red, ">>", 3) == 0)
			dup2(fd, 1);
		close(fd);
	}
	return (1);
}
