/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:05:42 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 15:15:59 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*recup_element(char *str, int *x)
{
	int		gu;
	char	*res;
	int		y;

	gu = 0;
	res = NULL;
	while (ft_whitespace(str[(*x)]) == 1)
		(*x)++;
	while (str[(*x)])
	{
		y = 0;
		y = my_check_guil(&gu, str[(*x)]);
		if (gu == 0 && (ft_whitespace(str[(*x)]) == 1
				|| my_check_redirection(&(str[(*x)])) > 0
				|| !str[(*x)]))
			break ;
		if (y == 0)
			res = ft_strmicrojoin(&res, str[(*x)]);
		(*x)++;
	}
	return (res);
}

t_cmd	*my_creat_tmp(char *str)
{
	t_cmd	*tmp;

	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return (NULL);
	bzero(tmp, sizeof(t_cmd));
	my_take_fichier_and_intra_red(str, tmp);
	my_take_cmd_and_path(str, tmp);
	my_take_arg(str, tmp);
	my_take_red(str, tmp);
	tmp->previous = NULL;
	tmp->next = NULL;
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
		g_term.cmd->previous = tmp;
	}
	else
	{
		tmp_1 = g_term.cmd;
		while (++x < g_term.nb_maillon)
			g_term.cmd = g_term.cmd->next;
		g_term.cmd->next = tmp;
		tmp_1->previous = tmp;
		tmp->previous = g_term.cmd;
		tmp->next = tmp_1;
		g_term.cmd = tmp_1;
	}
	g_term.nb_maillon++;
	return (1);
}

int	my_init_struct(char **tab_cmd)
{
	int		x;

	x = 0;
	g_term.nb_maillon = 0;
	while (tab_cmd[x])
	{
		if (my_add_liste_chene(my_creat_tmp(tab_cmd[x])) == -1)
			return (-1);
		x++;
	}
	return (1);
}
