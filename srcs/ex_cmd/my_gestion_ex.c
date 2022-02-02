/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gestion_ex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:52:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/02 12:15:26 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_ex_building(t_cmd *cmd)
{
	char	*cpe;
	int		c;

	c = 0;
	cpe = cmd->cmd;
	if (ft_strncmp(cpe, "cd", 10) == 0)
		c = my_cd(g_term.cmd->arg);
	else if (ft_strncmp(cpe, "pwd", 10) == 0)
		c = my_pwd(cmd);
	else if (ft_strncmp(cpe, "echo", 10) == 0)
		c = my_echo(cmd->arg);
	else if (ft_strncmp(cpe, "export", 10) == 0)
		c = my_export(cmd->arg);
	else if (ft_strncmp(cpe, "unset", 10) == 0)
		c = my_unset(cmd->arg);
	else if (ft_strncmp(cpe, "env", 5) == 0)
		c = my_env(cmd);
	else if (ft_strncmp(cpe, "exit", 5) == 0)
		my_exit(cmd->arg);
	else
		return (-1);
	if (c == -1)
		return (-1);
	return (0);
}

int	my_exe(t_cmd *cmd)
{
	char	*cpe;
	int		ret;

	ret = 0;
	if (cmd->path == NULL)
		cpe = ft_strdup(cmd->cmd);
	else
		cpe = ft_strjoin(cmd->path, cmd->cmd);
	if (!cpe)
	{
		exit (-1);
		return (-1);
	}
	ret = execve(cpe, cmd->arg, g_term.envp);
	if (ret == -1)
	{
		free(cpe);
		exit (ret);
	}
	free(cpe);
	return (1);
}

void	my_exe_cmd_2(void)
{
	if (!g_term.cmd->cmd)
	{
		if (g_term.cmd->pid == 0)
			exit (0);
		return ;
	}
	if (g_term.cmd->pid == 0)
	{
		if (my_check_building(g_term.cmd) == 1)
			g_term.dernier_ret = my_ex_building(g_term.cmd);
		else
			g_term.dernier_ret = my_exe(g_term.cmd);
	}
}

int	my_exe_cmd(void)
{
	if (my_check_building(g_term.cmd) == 1
		&& g_term.cmd->pip[0] == ';'
		&& !g_term.cmd->red)
	{
		if (g_term.cmd->pid == 0)
			exit (0);
		g_term.dernier_ret = my_ex_building(g_term.cmd);
		return (1);
	}
	else
		my_exe_cmd_2();
	return (1);
}
