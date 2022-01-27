/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:11:57 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/26 08:23:30 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**my_creat_tab_cmd(void)
{
	char	**tab_cmd;
	char	**new_tab;
	int		nb_tab;

	tab_cmd = NULL;
	nb_tab = my_take_nb_tab();
	tab_cmd = malloc(sizeof(char *) * (nb_tab + 1));
	if (!tab_cmd)
		return (NULL);
	if (my_rempli_tab_cmd(tab_cmd, g_term.str_cmd) == -1)
		return (NULL);
	new_tab = my_sup_str_vide(tab_cmd);
	if (!new_tab)
		return (NULL);
	my_free_double_tab((void *)tab_cmd, -1);
	return (new_tab);
}
