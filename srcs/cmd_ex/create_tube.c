/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:18:33 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/08 12:18:49 by mbonnet          ###   ########.fr       */
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

void	my_double_red_droite(t_cmd *cmd)
{
	int		fd;
	int		x;
	char	c;

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
		fd = open(cmd->next->cmd, O_RDWR);
		if (fd < 0)
		{
			fd = open(cmd->next->cmd, O_CREAT);
			close(fd);
			fd = open(cmd->next->cmd, O_RDWR);
		}
		close(term->tub[ENTRE]);
		while (read(fd, &c, 1) > 0);
		while (read(term->tub[SORTI], &c, 1) > 0)
			write(fd, &c, sizeof(char));
		close(term->tub[SORTI]);
		close(fd);
	}
}

void	my_simple_red_droite(t_cmd *cmd)
{
	int		fd;
	int		x;
	char	c;
	int		len;

	x = 0;
	c = 0;
	len = 0;
	if (term->pid == 0)
	{
		close(term->tub[SORTI]);
		dup2(term->tub[ENTRE], 1);
		close(term->tub[ENTRE]);
	}
	else
	{
		fd = open(cmd->next->cmd, O_RDWR);
		if (fd >= 0)
			remove(cmd->next->cmd);
		fd = open(cmd->next->cmd, O_RDWR);
		if (fd < 0)
		{
			fd = open(cmd->next->cmd, O_CREAT);
			close(fd);
		}
		fd = open(cmd->next->cmd, O_RDWR);
		close(term->tub[ENTRE]);
		while (read(fd, &c, 1) > 0);
		while (read(term->tub[SORTI], &c, 1) > 0)
			write(fd, &c, sizeof(char));
		close(term->tub[SORTI]);
		close(fd);
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
	if (ft_strncmp(cmd->red, ";", 3) != 0
		&& ft_strncmp(cmd->red, "&&", 3) != 0
		&& ft_strncmp(cmd->red, "||", 3) != 0)
	{
		if (term->pid != 0)
		{
			dup2(ENTRE, SORTI);
		}
	}
}

