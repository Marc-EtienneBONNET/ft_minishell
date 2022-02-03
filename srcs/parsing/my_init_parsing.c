/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 08:24:57 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/03 11:25:48 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_check_space_2(void)
{
	int	x;

	x = 0;
	while (ft_whitespace(g_term.str_cmd[x]) == 1)
		x++;
	if (!g_term.str_cmd[x])
		return (-1);
	return (1);
}

int	my_init_parsing_2(void)
{
	int	gu;

	gu = my_check_nb_guillemet(g_term.str_cmd);
	if (gu != 0)
	{
		g_term.str_cmd = my_free_tab((void **)&(g_term.str_cmd));
		if (gu == 2)
			g_term.str_cmd = ft_strdup("<<\"");
		else if (gu == 1)
			g_term.str_cmd = ft_strdup("<<\'");
	}
	if (my_check_bad_red(g_term.str_cmd) == -1)
		return (-1);
	return (0);
}

int	my_init_parsing(void)
{
	char	**tab_cmd;

	tab_cmd = NULL;
	if (my_check_space_2() == -1)
		return (2);
	if (my_init_parsing_2() == -1)
		return (-1);
	tab_cmd = my_init_tab_cmd(g_term.str_cmd);
	if (!tab_cmd)
	{
		tab_cmd = my_free_double_tab((void **)tab_cmd, -1);
		return (3);
	}
	if (my_create_cmd(tab_cmd) == -1)
	{
		printf(ROUGE"Erreur lor du malloc de la structur\n"BLANC);
		tab_cmd = my_free_double_tab((void **)tab_cmd, -1);
		return (-2);
	}
	tab_cmd = my_free_double_tab((void **)tab_cmd, -1);
	return (0);
}
