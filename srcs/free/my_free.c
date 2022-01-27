/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:01:20 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/26 10:59:05 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*my_free_tab(void *a_free)
{
	if (a_free)
		free(a_free);
	a_free = NULL;
	return (NULL);
}

void	*my_free_double_tab(void **tab_str, int nb_str)
{
	int	op;

	if (!tab_str)
		return (NULL);
	if (nb_str != -1)
		op = -1;
	else
	{
		nb_str = 0;
		op = 1;
	}
	while (nb_str >= 0 && tab_str[nb_str])
	{
		if (tab_str[nb_str])
			my_free_tab(tab_str[nb_str]);
		else
			break ;
		nb_str += (1 * op);
	}
	my_free_tab(tab_str);
	return (NULL);
}

void	*my_free_liste_chene(t_cmd *cmd)
{
	int			i;
	int			x;
	t_cmd		*tmp;

	x = 0;
	i = 1;
	my_free_tab(g_term.str_cmd);
	if (!cmd)
		return (NULL);
	i = g_term.nb_maillon;
	while (i > 0)
	{
		tmp = cmd->next;
		my_free_maillon(cmd);
		if (tmp == NULL)
			break ;
		i--;
		cmd = tmp;
	}
	g_term.nb_maillon = 0;
	g_term.cmd = NULL;
	return (NULL);
}

void	*my_free_maillon(t_cmd *tmp)
{
	int	x;

	x = -1;
	if (tmp == NULL)
		return (NULL);
	tmp->cmd = my_free_tab(tmp->cmd);
	tmp->path = my_free_tab(tmp->path);
	tmp->fichier_1 = my_free_tab(tmp->fichier_1);
	tmp->fichier_2 = my_free_tab(tmp->fichier_2);
	tmp->intra_red = my_free_tab(tmp->intra_red);
	while (tmp->arg && tmp->arg[++x])
		tmp->arg[x] = my_free_tab(tmp->arg[x]);
	tmp->arg = my_free_tab(tmp->arg);
	tmp->red = my_free_tab(tmp->red);
	tmp = my_free_tab(tmp);
	return (NULL);
}

int	my_free_all(int ret)
{
	int	x;

	x = 0;
	while (g_term.my_env && g_term.my_env[x].key != NULL)
	{
		my_free_tab(g_term.my_env[x].key);
		my_free_tab(g_term.my_env[x].var);
		x++;
	}
	rl_clear_history();
	if (g_term.my_env)
		my_free_tab(g_term.my_env);
	return (ret);
}
