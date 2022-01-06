/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/06 12:18:29 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_lancement_building()
{
	char	*cpe;

	cpe = term->cmd->cmd;
	if (ft_strncmp(cpe, "ls", 10) == 0)
		printf("commande ls\n");
	else if (ft_strncmp(cpe, "cd", 10) == 0)
		printf("commande cd\n");
	else if (ft_strncmp(cpe, "pwd", 10) == 0)
		printf("commande pwd\n");
	else if (ft_strncmp(cpe, "echo", 10) == 0)
		printf("commande echo\n");
	else if (ft_strncmp(cpe, "export", 10) == 0)
		printf("commande export\n");
	else if (ft_strncmp(cpe, "unset", 10) == 0)
		printf("commande unset\n");
	else if (ft_strncmp(cpe, "env", 5) == 0)
		printf("commande env\n");
	else if (ft_strncmp(cpe, "exit", 5) == 0)
		printf("commande exit\n");
}

void	*my_exe_cmd(t_term *term)
{
	char	*cpe;

	cpe = term->cmd->cmd;
	if (ft_strncmp(cpe, "ls", 10) == 0
		|| ft_strncmp(cpe, "cd", 10) == 0
		|| ft_strncmp(cpe, "pwd", 10) == 0
		|| ft_strncmp(cpe, "echo", 10) == 0
		|| ft_strncmp(cpe, "export", 10) == 0
		|| ft_strncmp(cpe, "unset", 10) == 0
		|| ft_strncmp(cpe, "env", 5) == 0
		|| ft_strncmp(cpe, "exit", 5) == 0)
	{
		my_lancement_building();
	}
	else
		execve(ft_strjoin("/bin/", term->cmd->cmd), term->cmd->arg, term->envp);
	return (NULL);
}
