/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1chenage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:16:16 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/21 09:50:07 by mbonnet          ###   ########.fr       */
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

t_cmd	*new_maillons(char **tab_cmd, int *x)
{
	t_cmd	*tmp;
	char	*tmp_2;
	int		w;

	w = 0;
	tmp = bzero_tmp();
	if (tmp == NULL)
		return (NULL);
	if (my_check_redirection(tab_cmd[*x]) == -1)
		tmp->cmd = ft_strdup(tab_cmd[(*x)++]);
	if (tmp->cmd == NULL)
		tmp->cmd = ft_strdup("cmd_vide");
	tmp->path = my_gestion_path(tmp);
	w = ft_strlen(tmp->cmd);
	while (tmp->cmd[w] != '/' && w > 0)
		w--;
	if (tmp->cmd[w] != '/')
	{
		if (tmp->path)
		{
			tmp_2 = ft_strjoin(tmp->path, tmp->cmd);
			free(tmp->cmd);
			tmp->cmd = tmp_2;
		}
	}
	tmp->cmd = my_modifie_cmd(tmp);
	if (!tmp->cmd)
		return (my_free_maillon(tmp));
	tmp->arg = init_cmd_arg(tab_cmd, x);
	if (!tmp->path)
		return (my_free_maillon(tmp));
	tmp->arg[0] = ft_strdup(tmp->cmd);
	return (new_maillons_2(tab_cmd, x, tmp));
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
		if (tmp == NULL)
		{
			free(info_cmd);
			my_free_liste_chene(cmd);
			return (my_free_double_tab((void **)tab_cmd, -1));
		}
		tmp->info_cmd = info_cmd;
		cmd = my_ajoute_maillon(cmd, tmp);
	}
	my_free_double_tab((void **)tab_cmd, -1);
	return (cmd);
}
