/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3mouv_struct_for_red.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 08:41:46 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 16:18:24 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_ajoute_arg(t_cmd **cmd, t_cmd **cmd_new_arg)
{
	int		x;
	char	**tmp;

	x = 1;
	while ((*cmd_new_arg)->arg[x])
	{
		tmp = ft_strdoubledup((*cmd)->arg);
		my_free_double_tab((void **)(*cmd)->arg, -1);
		(*cmd)->arg = ft_strdoublejoin(tmp, (*cmd_new_arg)->arg[x]);
		my_free_double_tab((void **)tmp, -1);
		x++;
	}
}

void	my_ajuste_pointeur(t_cmd **cmd)
{
	t_cmd	*cmd_tmp;
	t_cmd	*cmd_tmp_2;

	if (ft_strncmp((*cmd)->next->red, "<<", 3) == 0)
	{
		cmd_tmp_2 = (*cmd)->next->next;
		cmd_tmp = (*cmd)->next;
		(*cmd)->info_cmd->nb_maillons -= 2;
		(*cmd)->next = (*cmd)->next->next->next;
		(*cmd)->next->next->previous = (*cmd);
		my_free_maillon(cmd_tmp_2);
		my_free_maillon(cmd_tmp);
	}
	else
	{
		cmd_tmp = (*cmd)->next;
		(*cmd)->info_cmd->nb_maillons--;
		(*cmd)->next = (*cmd)->next->next;
		(*cmd)->next->previous = (*cmd);
		my_free_maillon(cmd_tmp);
	}
}

int	my_mouv_struct_for_red_droite(t_cmd **cmd)
{
	int		x;

	x = 1;

	(*cmd)->fichier_1 = my_choose_fichier((*cmd)->next);
	(*cmd)->intra_red = ft_strdup((*cmd)->red);
	if (!(*cmd)->intra_red)
		return (-1);
	free((*cmd)->red);
	(*cmd)->red = ft_strdup((*cmd)->next->red);
	if (!(*cmd)->red)
		return (-1);
	my_ajoute_arg(cmd, &((*cmd)->next));
	my_ajuste_pointeur(cmd);
	return (1);
}

int	my_mouv_struct_for_red_gauche(t_cmd **cmd)
{
	int		x;

	x = 1;
	if (ft_strncmp((*cmd)->next->red, "<<", 3) == 0)
	{
		(*cmd)->fichier_1 = ft_strdup((*cmd)->next->next->cmd);
		(*cmd)->fichier_2 = ft_strdup((*cmd)->next->cmd);
		if (!(*cmd)->fichier_2)
			return (-1);
	}
	else
		(*cmd)->fichier_1 = ft_strdup((*cmd)->next->cmd);
	(*cmd)->intra_red = ft_strdup((*cmd)->red);
	free((*cmd)->red);
	if (ft_strncmp((*cmd)->next->red, "<<", 3) == 0)
		(*cmd)->red = ft_strdup((*cmd)->next->next->red);
	else
		(*cmd)->red = ft_strdup((*cmd)->next->red);
	my_ajoute_arg(cmd, &((*cmd)->next));
	if (!(*cmd)->fichier_1
		|| !(*cmd)->intra_red || !(*cmd)->red)
		return (-1);
	if (ft_strncmp((*cmd)->next->red, "<<", 3) == 0)
		my_ajoute_arg(cmd, &((*cmd)->next->next));
	my_ajuste_pointeur(cmd);
	return (1);
}

t_cmd	*my_mouv_struct_for_red(t_cmd **cmd)
{
	int	x;

	x = 0;
	while (x < (*cmd)->info_cmd->nb_maillons)
	{
		if (ft_strncmp((*cmd)->red, ">", 3) == 0
			|| ft_strncmp((*cmd)->red, ">>", 3) == 0
			|| ft_strncmp((*cmd)->red, "<", 3) == 0)
		{
			if (my_mouv_struct_for_red_droite(cmd) == -1)
				return (NULL);
		}
		else if (ft_strncmp((*cmd)->red, "<<", 3) == 0)
			if (my_mouv_struct_for_red_gauche(cmd) == -1)
				return (NULL);
		(*cmd) = (*cmd)->next;
		x++;
	}
	return (*cmd);
}
