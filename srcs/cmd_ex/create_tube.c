/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:18:33 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/10 10:21:41 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_pipe(void)
{
	if (term->pid == 0)
	{
		close(term->tub[SORTI]);
		dup2(term->tub[ENTRE], 1);
		close(term->tub[ENTRE]);
	}
	else
	{
		close(term->tub[ENTRE]);
		dup2(term->tub[SORTI], 0);
		close(term->tub[SORTI]);
	}
}

char	*my_choose_fichier(t_cmd *cmd)
{
	char	*fichier;

	if (ft_strncmp(cmd->next->path, "/bin/", 6) != 0)
		fichier = ft_strjoin(cmd->next->path, cmd->next->cmd);
	else
		fichier = ft_strdup(cmd->next->cmd);
	return (fichier);
}

char	*my_choose_fichier_2(t_cmd *cmd)
{
	char	*fichier;

	if (ft_strncmp(cmd->path, "/bin/", 6) != 0)
		fichier = ft_strjoin(cmd->path, cmd->cmd);
	else
		fichier = ft_strdup(cmd->cmd);
	return (fichier);
}

void	my_double_red_droite(t_cmd *cmd)
{
	int		fd;
	int		x;
	char	c;
	char	*fichier;

	x = 0;
	c = 0;
	if (term->pid == 0)
	{
		close(term->tub[SORTI]);
		dup2(term->tub[ENTRE], 1);
		close(term->tub[ENTRE]);
	}
	else
	{
		fichier = my_choose_fichier(cmd);
		fd = open(fichier, O_RDWR);
		if (fd < 0)
		{
			fd = open(fichier, O_CREAT);
			close(fd);
			fd = open(fichier, O_RDWR);
		}
		close(term->tub[ENTRE]);
		while (read(fd, &c, 1) > 0);
		while (read(term->tub[SORTI], &c, 1) > 0)
			write(fd, &c, sizeof(char));
		close(term->tub[SORTI]);
		close(fd);
		free(fichier);
	}
}

void	my_simple_red_droite(t_cmd *cmd)
{
	int		fd;
	int		x;
	char	c;
	char	*fichier;

	x = 0;
	c = 0;
	if (term->pid == 0)
	{
		close(term->tub[SORTI]);
		dup2(term->tub[ENTRE], 1);
		close(term->tub[ENTRE]);
	}
	else
	{
		fichier = my_choose_fichier(cmd);
		fd = open(fichier, O_RDWR);
		if (fd >= 0)
			remove(fichier);
		fd = open(fichier, O_RDWR);
		if (fd < 0)
		{
			fd = open(fichier, O_CREAT);
			close(fd);
		}
		fd = open(fichier, O_RDWR);
		close(term->tub[ENTRE]);
		while (read(fd, &c, 1) > 0);
		while (read(term->tub[SORTI], &c, 1) > 0)
			write(fd, &c, sizeof(char));
		close(term->tub[SORTI]);
		close(fd);
		free(fichier);
	}
}

int	my_create_tub(t_cmd *cmd)
{
	if (ft_strncmp(cmd->red, "|", 3) == 0)
		my_pipe();
	else if (ft_strncmp(cmd->red, ">>", 3) == 0)
		my_double_red_droite(cmd);
	else if (ft_strncmp(cmd->red, ">", 3) == 0)
		my_simple_red_droite(cmd);
	return (1);
}

void	my_kill_tub(t_cmd *cmd)
{
	if (ft_strncmp(cmd->red, "|", 2) == 0)
		if (term->pid != 0)
			dup2(ENTRE, SORTI);
}

