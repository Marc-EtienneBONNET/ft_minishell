/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/07 12:53:33 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_lancement_building(t_cmd *cmd)
{
	char	*cpe;

	cpe = cmd->cmd;
	if (ft_strncmp(cpe, "cd", 10) == 0)
		printf("commande cd\n");
	else if (ft_strncmp(cpe, "pwd", 10) == 0)
		my_pwd();
	else if (ft_strncmp(cpe, "echo", 10) == 0)
		my_echo(cmd->arg);
	else if (ft_strncmp(cpe, "export", 10) == 0)
		printf("commande export\n");
	else if (ft_strncmp(cpe, "unset", 10) == 0)
		printf("commande unset\n");
	else if (ft_strncmp(cpe, "env", 5) == 0)
		my_env(term->envp);
	else if (ft_strncmp(cpe, "exit", 5) == 0)
		printf("commande exit\n");
}

int	my_exe_cmd(t_term *term, t_cmd *cmd)
{
	char	*cpe;

	cpe = cmd->cmd;
	if (ft_strncmp(cpe, "cd", 10) == 0
		|| ft_strncmp(cpe, "pwd", 10) == 0
		|| ft_strncmp(cpe, "echo", 10) == 0
		|| ft_strncmp(cpe, "export", 10) == 0
		|| ft_strncmp(cpe, "unset", 10) == 0
		|| ft_strncmp(cpe, "env", 5) == 0
		|| ft_strncmp(cpe, "exit", 5) == 0)
	{
		my_lancement_building(cmd);
	}
	else
	{
		if (execve(ft_strjoin(cmd->path, cmd->cmd), cmd->arg, term->envp) == -1)
		{
			if (ft_strncmp(cmd->red, "||", 3) == 0)
				return (-2);
			printf("%s : commande introuvable\n", cmd->cmd);
			return (-1);
		}
	}
	return (1);
}
