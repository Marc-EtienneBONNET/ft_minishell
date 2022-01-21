/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3mouv_struct_for_red copy.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 08:41:46 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/21 16:02:45 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
