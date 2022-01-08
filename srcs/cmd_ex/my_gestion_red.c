/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gestion_red.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 11:17:49 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/08 12:22:25 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_gestion_ou(int res, t_cmd *cmd, int *x)
{
	if (ft_strncmp(cmd->red, "||", 3) == 0 && res != 0)
		printf("%s : commande introuvable\n", cmd->cmd);
	else if (ft_strncmp(cmd->red, "||", 3) == 0 && res == 0)
	{
		while (term->cmd->next
			&& ft_strncmp(term->cmd->next->red, "||", 3) == 0)
		{
			term->cmd = term->cmd->next;
			(*x)++;
		}
		if (term->cmd->next)
		{
			term->cmd = term->cmd->next;
			(*x)++;
		}
	}
}

void	my_gestion_et(int res, t_cmd *cmd, int *x)
{
	if (ft_strncmp(cmd->red, "&&", 3) == 0 && res != 0)
	{
		printf("%s : commande introuvable\n", cmd->cmd);
		while (term->cmd->next
			&& ft_strncmp(term->cmd->next->red, "&&", 3) == 0)
		{
			term->cmd = term->cmd->next;
			(*x)++;
		}
		if (term->cmd->next)
		{
			term->cmd = term->cmd->next;
			(*x)++;
		}
	}
}

void	my_gestion_pip(int res, t_cmd *cmd)
{
	if (cmd->previous && ft_strncmp(cmd->previous->red, "|", 3) == 0
		&& res != 0)
		printf("%s : commande introuvable\n", cmd->cmd);
}

void	my_gestion_double_red_droite(int res, t_cmd *cmd, int *x)
{
	if ((ft_strncmp(cmd->red, ">>", 3) == 0
			|| ft_strncmp(cmd->red, ">", 3) == 0) && res != 0)
	{
		printf("%s : commande introuvable\n", cmd->cmd);
		term->cmd = term->cmd->next;
		(*x)++;
	}
}

void	my_gestion_virgule_point(int res, t_cmd *cmd)
{
	if (ft_strncmp(cmd->red, ";", 3) == 0 && res != 0)
		printf("%s : commande introuvable\n", cmd->cmd);
}
