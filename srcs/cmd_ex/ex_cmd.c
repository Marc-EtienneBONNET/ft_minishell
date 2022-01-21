/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:30:28 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/21 11:37:24 by mbonnet          ###   ########.fr       */
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

int	my_exe_cmd(t_term g_term, t_cmd *cmd)
{
	char	*cpe;
	int		ret;

	cpe = ft_strjoin(cmd->path, cmd->cmd);
	if (!cpe)
	{
		free(cpe);
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
