/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2create_new_maillon.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:16:16 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/18 11:03:35 by mbonnet          ###   ########.fr       */
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
	while (tab_cmd[x_tmp] && tab_cmd[(*x)][0] && my_check_redirection(tab_cmd[x_tmp++]) == -1)
		conteur++;
	tabe = malloc(sizeof(char *) * (conteur + 1));
	if (!tabe)
	{
		free(tabe);
		return (NULL);
	}
	(*y)++;
	while (tab_cmd[(*x)] && my_check_redirection(tab_cmd[*x]) == -1)
	{
		if (!tab_cmd[(*x)][0])
			(*x)++;
		else
		{
			tabe[(*y)] = ft_strdup(tab_cmd[(*x)++]);
			if (!tabe[(*y)])
			{
				free(tabe);
				return (NULL);
			}
			(*y)++;
		}
	}
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
	if (ft_strncmp(tmp->path, "/bin/", 10) != 0)
		len = ft_strlen(tmp->path);
	res = (char *)malloc(sizeof(char) * ((ft_strlen(tmp->cmd) - len) + 1));
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

char	*my_gestion_path(t_cmd *tmp)
{
	int		x;
	char	*res;

	x = ft_strlen(tmp->cmd) - 1;
	while (x >= 0 && tmp->cmd[x] != '/')
		x--;
	if (x == -1)
	{
		res = ft_strdup("/bin/");
		if (!res)
			return (NULL);
	}
	else
	{
		res = (char *)malloc(sizeof(char) * (x + 2));
		if (!res)
			return (NULL);
		res[++x] = '\0';
		while (--x >= 0)
			res[x] = tmp->cmd[x];
	}
	return (res);
}

t_cmd	*new_maillons(char **tab_cmd, int *x)
{
	t_cmd	*tmp;
	int		y;

	y = 0;
	tmp = bzero_tmp();
	if (tmp == NULL)
		return (NULL);
	if (my_check_redirection(tab_cmd[*x]) == -1)
		tmp->cmd = ft_strdup(tab_cmd[(*x)++]);
	if (tmp->cmd == NULL)
		tmp->cmd = ft_strdup("cmd_vide");
	tmp->path = my_gestion_path(tmp);
	if (!tmp->path)
		return (my_free_maillon(tmp));
	tmp->cmd = my_modifie_cmd(tmp);
	if (!tmp->cmd)
		return (my_free_maillon(tmp));
	tmp->arg = init_cmd_arg(tab_cmd, x, &y);
	if (!tmp->arg)
		return (my_free_maillon(tmp));
	tmp->arg[0] = ft_strdup(tmp->cmd);
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
