/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:40:08 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/01 15:26:07 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*my_init_maillon(char *tab_cmd)
{
	t_cmd	*tmp;

	tmp = NULL;
	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return (NULL);
	bzero(tmp, sizeof(t_cmd));
	tmp->red = my_recup_red(&tab_cmd);
	tmp->cmd = my_recup_cmd(&tab_cmd);
	tmp->path = my_recup_path(&tmp->cmd);
	if (!tmp->path)
		tmp->path = my_recup_path_env(tmp->cmd);
	tmp->pip = my_recup_pip(&tab_cmd);
	tmp->arg = my_recup_arg(&tab_cmd, tmp);
	return (tmp);
}

int	my_add_liste_chene(t_cmd *tmp)
{
	int		x;
	t_cmd	*tmp_1;

	x = 0;
	if (!tmp)
		return (-1);
	if (!g_term.cmd)
	{
		g_term.cmd = tmp;
		g_term.cmd->next = tmp;
		g_term.cmd->prev = tmp;
	}
	else
	{
		tmp_1 = g_term.cmd;
		while (++x < g_term.nb_maillon)
			g_term.cmd = g_term.cmd->next;
		g_term.cmd->next = tmp;
		tmp_1->prev = tmp;
		tmp->prev = g_term.cmd;
		tmp->next = tmp_1;
		g_term.cmd = tmp_1;
	}
	g_term.nb_maillon++;
	return (1);
}

int	my_create_cmd(char **tab_cmd)
{
	int		x;

	x = 0;
	g_term.nb_maillon = 0;
	while (tab_cmd[x])
	{
		if (my_add_liste_chene(my_init_maillon(tab_cmd[x])) == -1)
			return (-1);
		x++;
	}
	return (1);
}
