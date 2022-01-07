/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1chenage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:16:16 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/07 11:41:50 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*my_ajoute_maillon_2(t_cmd *cmd, t_cmd *tmp)
{
	int		i;
	t_cmd	*start;

	i = 0;
	start = cmd;
	if (cmd->info_cmd->nb_maillons == 1)
	{
		cmd->next = tmp;
		cmd->previous = tmp;
		cmd->next->next = cmd;
		cmd->next->previous = cmd;
		cmd->info_cmd->nb_maillons++;
	}
	else
	{
		while (cmd->info_cmd->nb_maillons > ++i)
			cmd = cmd->next;
		cmd->next = tmp;
		tmp->previous = cmd;
		tmp->next = start;
		start->previous = tmp;
		cmd->info_cmd->nb_maillons++;
	}
	cmd = start;
	return (cmd);
}

t_cmd	*my_ajoute_maillon(t_cmd *cmd, t_cmd *tmp)
{
	if (!cmd)
	{
		cmd = tmp;
		cmd->next = cmd;
		cmd->previous = cmd;
		cmd->info_cmd->nb_maillons = 1;
		return (cmd);
	}
	return (my_ajoute_maillon_2(cmd, tmp));
}

t_cmd	*my_init_struct_cmd(char **tab_cmd)
{
	t_cmd		*cmd;
	t_cmd		*tmp;
	int			x;
	t_info_cmd	*info_cmd;

	info_cmd = malloc(sizeof(t_info_cmd));
	if (!info_cmd)
		return (NULL);
	info_cmd->nb_maillons = 0;
	x = 0;
	cmd = NULL;
	while (tab_cmd[x] != NULL)
	{
		tmp = new_maillons(tab_cmd, &x);
		tmp->info_cmd = info_cmd;
		if (tmp == NULL)
		{
			my_free_liste_chene(cmd);
			return (my_free_double_tab((void **)tab_cmd, -1));
		}
		cmd = my_ajoute_maillon(cmd, tmp);
	}
	my_free_double_tab((void **)tab_cmd, -1);
	return (cmd);
}
