/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_des_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 08:59:34 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/07 10:39:31 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//cette fonction permet de free n importe quel tab
void	*my_free_tab(void *a_free)
{
	if (a_free)
		free(a_free);
	return (NULL);
}

//cette fonction permet de free nimporte quel tableau et a tout momant : 
//	-1) para = le tableau en question
//	-2) para = le nombre de tableau present dans le double tableau
//	dans le cas d un free classique se parametre doit etre init a 0;
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
		my_free_maillon_2(cmd);
		if (tmp == NULL)
			break ;
		i--;
		cmd = tmp;
	}
	return (NULL);
}

void	*my_free_maillon_2(t_cmd *tmp)
{
	int	x;

	x = 0;
	if (tmp == NULL)
		return (NULL);
	if (tmp->cmd)
		free(tmp->cmd);
	while (tmp->arg && tmp->arg[x])
		free(tmp->arg[x++]);
	if (tmp->arg)
		free(tmp->arg);
	if (tmp->red)
		free(tmp->red);
	if (tmp->path)
		free(tmp->path);
	if (tmp)
		free(tmp);
	return (NULL);
}
