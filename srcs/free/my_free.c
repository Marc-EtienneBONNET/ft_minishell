/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:01:20 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 12:41:05 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*my_free_tab(void *a_free)
{
	if (a_free)
		free(a_free);
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
	while (tab_str[nb_str] && nb_str >= 0)
	{
		free(tab_str[nb_str]);
		nb_str += (1 * op);
	}
	free(tab_str[nb_str]);
	free(tab_str);
	return (NULL);
}

void	*my_free_liste_chene(t_cmd *cmd)
{
	int			i;
	int			x;
	t_cmd		*tmp;

	x = 0;
	i = 1;
	if (!cmd)
		return (NULL);
	if (cmd->info_cmd)
	{
		i = cmd->info_cmd->nb_maillons;
		free(cmd->info_cmd);
	}
	while (i > 0)
	{
		tmp = cmd->next;
		my_free_maillon(cmd);
		if (tmp == NULL)
			break ;
		i--;
		cmd = tmp;
	}
	return (NULL);
}

void	*my_free_maillon(t_cmd *tmp)
{
	int	x;

	x = 0;
	if (tmp == NULL)
		return (NULL);
	if (tmp->cmd)
		free(tmp->cmd);
	if (tmp->path)
		free(tmp->path);
	if (tmp->fichier_1)
		free(tmp->fichier_1);
	if (tmp->fichier_2)
		free(tmp->fichier_2);
	if (tmp->intra_red)
		free(tmp->intra_red);
	while (tmp->arg && tmp->arg[x])
		free(tmp->arg[x++]);
	if (tmp->arg)
		free(tmp->arg);
	if (tmp->red)
		free(tmp->red);
	if (tmp)
		free(tmp);
	return (NULL);
}

int	my_free_all(int ret)
{
	int	x;

	x = 0;
	while (term->my_env && term->my_env[x].key != NULL)
	{
		free(term->my_env[x].key);
		free(term->my_env[x].var);
		x++;
	}
	rl_clear_history();
	if (term->my_env)
		free(term->my_env);
	//if (term->envp)
	//	my_free_double_tab((void **)term->envp, -1);
	//if (term->str_cmd)
	//	free(term->str_cmd);
	//if (term->cmd)
	//	my_free_liste_chene(term->cmd);
	free(term);
	return (ret);
}
