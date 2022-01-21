/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2create_new_maillon.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:16:16 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/21 15:49:43 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_cmd_arg(char **tab_cmd, int *x)
{
	int		conteur;
	char	**tabe;
	int		y;

	y = 0;
	conteur = 0;
	while (tab_cmd[*x + conteur]
		&& my_check_redirection(tab_cmd[*x + conteur]) == -1)
		conteur++;
	tabe = malloc(sizeof(char *) * (conteur + 2));
	if (!tabe)
		return (my_free_tab((void *)tabe));
	y++;
	while (tab_cmd[(*x)]
		&& my_check_redirection(tab_cmd[*x]) == -1)
	{
		tabe[y++] = ft_strdup(tab_cmd[(*x)++]);
		if (!tabe[y - 1])
			return (my_free_tab((void *)tabe));
	}
	if (tab_cmd[(*x)] && !tab_cmd[*x][0])
		(*x)++;
	tabe[y] = NULL;
	return (tabe);
}

t_cmd	*bzero_tmp(void)
{
	t_cmd	*tmp;

	tmp = malloc(sizeof(t_cmd));
	if (tmp == NULL)
		return (NULL);
	tmp->cmd = NULL;
	tmp->path = NULL;
	tmp->fichier_1 = NULL;
	tmp->fichier_2 = NULL;
	tmp->intra_red = NULL;
	tmp->arg = NULL;
	tmp->red = NULL;
	tmp->next = NULL;
	tmp->previous = NULL;
	tmp->pid = -1;
	return (tmp);
}

char	*my_modifie_cmd(t_cmd *tmp)
{
	int		len;
	char	*res;
	int		x;

	x = 0;
	len = 0;
	len = ft_strlen(tmp->path);
	res = (char *)malloc(sizeof(char)
			* ((ft_strlen(tmp->cmd) - len) + 1));
	if (!res)
		return (NULL);
	while (tmp->cmd[len])
	{
		res[x] = tmp->cmd[len];
		x++;
		len++;
	}
	res[x] = '\0';
	free(tmp->cmd);
	return (res);
}

t_cmd	*new_maillons_2(char **tab_cmd, int *x, t_cmd *tmp)
{
	if (my_check_redirection(tab_cmd[*x]) > 0)
		tmp->red = ft_strdup(tab_cmd[(*x)++]);
	else
	{
		tmp->red = malloc(sizeof(char) * 2);
		if (!tmp->red)
			return (my_free_maillon(tmp));
		tmp->red[0] = ';';
		tmp->red[1] = '\0';
	}
	if (!tmp->cmd || !tmp->arg[0] || !tmp->red)
	{
		my_free_maillon(tmp);
		return (NULL);
	}
	return (tmp);
}
