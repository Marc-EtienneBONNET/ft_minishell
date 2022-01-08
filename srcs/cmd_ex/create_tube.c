/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:18:33 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/08 10:33:27 by mbonnet          ###   ########.fr       */
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

int	my_double_red_droite(t_cmd *cmd)
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
			return (-1);
		close(term->tub[ENTRE]);
		while (read(fd, &c, 1) > 0);
		while (read(term->tub[SORTI], &c, 1) > 0)
			write(fd, &c, sizeof(char));
		close(term->tub[SORTI]);
		close(fd);
	}
	return (1);
}

int	my_create_tub(t_cmd *cmd)
{
	if (ft_strncmp(cmd->red, "|", 3) == 0)
		my_pipe();
	else if (ft_strncmp(cmd->red, ">>", 3) == 0)
	{
		if (my_double_red_droite(cmd) == -1)
			return (-1);
		else
			return (2);
	}
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

