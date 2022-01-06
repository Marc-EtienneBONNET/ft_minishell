/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2create_new_maillon.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:16:16 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/06 18:16:00 by mbonnet          ###   ########.fr       */
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

char	*my_modifie_cmd(t_cmd *tmp)
{
	int		len;
	char	*res;
	int		x;

	x = 0;
	len = ft_strlen(tmp->path);
	res = malloc(sizeof(char) * (ft_strlen(tmp->cmd) - len) + 1);
	while (tmp->cmd[len])
	{
		res[x] = tmp->cmd[len];
		x++;
		len++;
	}
	res[x]= '\0';
	free(tmp->cmd);
	return (res);
}

int	my_gestion_path(t_cmd *tmp)
{
	int	x;
	int	y;

	y = 0;
	x = ft_strlen(tmp->cmd) - 1;
	while (x >= 0 && tmp->cmd[x] != '/')
		x--;
	if (x == -1)
	{
		tmp->path = (char *)malloc(sizeof(char) * (6));
		if (!tmp->path)
			return (-1);
		tmp->path = "/bin/";
	}
	else if (tmp->cmd[x] == '/')
	{
		tmp->path = malloc(sizeof(char) * (x + 2));
		if (!tmp->path)
			return (-1);
		tmp->path[x + 1] = '\0';
		while (x >= 0)
		{
			tmp->path[x] = tmp->cmd[x];
			x--;
		}
		tmp->cmd = my_modifie_cmd(tmp);
	}
	return (1);
}

t_cmd	*new_maillons(char **tab_cmd, int *x)
{
	t_cmd	*tmp;
	int		y;

	y = 0;
	tmp = bzero_tmp();
	if (my_check_redirection(tab_cmd[*x]) == -1)
	tmp->cmd = ft_strdup(tab_cmd[(*x)++]);
	my_gestion_path(tmp);
	tmp->arg = init_cmd_arg(tab_cmd, x, &y);
	if (!tmp->arg)
		return (NULL);
	tmp->arg[0] = ft_strdup(tmp->cmd);
	if (my_check_redirection(tab_cmd[*x]) > 0)
		tmp->red = ft_strdup(tab_cmd[(*x)++]);
	return (tmp);
}
