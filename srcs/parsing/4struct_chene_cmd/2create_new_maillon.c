/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2create_new_maillon.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:16:16 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/05 15:29:37 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_cmd_arg(char **tab_cmd, int *x, int *y)
{
	int		conteur;
	char	**tabe;
	int		x_tmp;

	x_tmp = *x;
	conteur = 1;
	while (tab_cmd[x_tmp] && my_check_redirection(tab_cmd[x_tmp++]) == -1)
		conteur++;
	tabe = malloc(sizeof(char *) * (conteur + 1));
	if (!tabe)
		return (NULL);
	(*y)++;
	while (tab_cmd[(*x)] && my_check_redirection(tab_cmd[*x]) == -1)
		tabe[(*y)++] = ft_strdup(tab_cmd[(*x)++]);
	tabe[*y] = NULL;
	return (tabe);
}

t_cmd	*bzero_tmp(void)
{
	t_cmd	*tmp;

	tmp = malloc(sizeof(t_cmd));
	if (tmp == NULL)
		return (NULL);
	tmp->cmd = NULL;
	tmp->arg = NULL;
	tmp->red = NULL;
	tmp->next = NULL;
	tmp->previous = NULL;
	return (tmp);
}

t_cmd	*new_maillons(char **tab_cmd, int *x)
{
	t_cmd	*tmp;
	int		y;

	y = 0;
	tmp = bzero_tmp();
	if (my_check_redirection(tab_cmd[*x]) == -1)
	tmp->cmd = ft_strdup(tab_cmd[(*x)++]);
	tmp->arg = init_cmd_arg(tab_cmd, x, &y);
	if (!tmp->arg)
		return (NULL);
	tmp->arg[0] = ft_strdup(tmp->cmd);
	if (my_check_redirection(tab_cmd[*x]) > 0)
		tmp->red = ft_strdup(tab_cmd[(*x)++]);
	return (tmp);
}
