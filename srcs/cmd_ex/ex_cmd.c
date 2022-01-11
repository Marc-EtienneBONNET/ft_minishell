/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:30:28 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/11 10:31:30 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_ex_building(t_cmd *cmd)
{
	char	*cpe;

	cpe = cmd->cmd;
	if (ft_strncmp(cpe, "cd", 10) == 0)
		printf("commande cd\n");
	else if (ft_strncmp(cpe, "pwd", 10) == 0)
		my_pwd(cmd);
	else if (ft_strncmp(cpe, "echo", 10) == 0)
		my_echo(cmd->arg);
	else if (ft_strncmp(cpe, "export", 10) == 0)
		printf("commande export\n");
	else if (ft_strncmp(cpe, "unset", 10) == 0)
		printf("commande unset\n");
	else if (ft_strncmp(cpe, "env", 5) == 0)
		my_env(cmd);
	else if (ft_strncmp(cpe, "exit", 5) == 0)
		printf("commande exit\n");
	else
		return (-1);
	return (1);
}

int	my_exe_cmd(t_term *term, t_cmd *cmd)
{
	char	*cpe;

	cpe = ft_strjoin(cmd->path, cmd->cmd);
	if (execve(cpe, cmd->arg, term->envp) == -1)
	{
		free(cpe);
		my_kill_tub();
		printf("%s: commande introuvable\n", cmd->cmd);
		exit (-1);
	}
	free(cpe);
	return (1);
}