/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_building.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:33:31 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/18 14:33:44 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_check_building(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "cd", 10) == 0
		|| ft_strncmp(cmd->cmd, "unset", 10) == 0
		|| ft_strncmp(cmd->cmd, "export", 10) == 0
		|| ft_strncmp(cmd->cmd, "exit", 10) == 0
		|| ft_strncmp(cmd->cmd, "pwd", 10) == 0
		|| ft_strncmp(cmd->cmd, "echo", 10) == 0
		|| ft_strncmp(cmd->cmd, "env", 10) == 0)
		return (1);
	return (0);
}