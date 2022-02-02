/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gestion_gu_and_var_env.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:53:40 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/02 11:15:51 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_check_arg_var_env(char **tabe)
{
	int	x;

	x = -1;
	if (!tabe)
		return (1);
	while (tabe[++x])
	{
		my_check_var_env(&(tabe[x]));
		netoyage_guillemet(&(tabe[x]));
	}
	return (1);
}

int	my_check_red_var_env(t_intra_red *tabe)
{
	int	x;

	x = -1;
	if (!tabe)
		return (1);
	while (tabe[++x].red)
	{
		if (ft_strncmp(tabe[x].red, "<<", 3) == 0)
			continue ;
		my_check_var_env(&(tabe[x].red));
		my_check_var_env(&(tabe[x].fichier));
		netoyage_guillemet(&(tabe[x].red));
		netoyage_guillemet(&(tabe[x].fichier));
	}
	return (1);
}

int	my_gestion_var_env_and_gui(t_cmd *cmd)
{
	if (cmd->cmd)
	{
		my_check_var_env(&cmd->cmd);
		netoyage_guillemet(&cmd->cmd);
	}
	if (!cmd->path)
	{
		cmd->path = my_free_tab((void **)&(cmd->path));
		cmd->path = my_recup_path(&cmd->cmd);
		netoyage_guillemet(&cmd->path);
	}
	if (cmd->arg)
		my_check_arg_var_env(cmd->arg);
	if (cmd->red)
		my_check_red_var_env(cmd->red);
	return (1);
}
