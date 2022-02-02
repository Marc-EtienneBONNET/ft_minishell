/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gestion_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:42:14 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/02 16:23:56 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_double_tab(char **tabe, char **tmp)
{
	char	**new;
	int		x;

	x = 0;
	while (tabe && tabe[x])
		x++;
	new = malloc(sizeof(char *) * (x + 2));
	if (!new)
		return (NULL);
	x = 0;
	while (tabe && tabe[x])
	{
		new[x] = ft_strdup(tabe[x]);
		x++;
	}
	new[x++] = ft_strdup(*tmp);
	new[x] = NULL;
	tabe = my_free_double_tab((void **)tabe, -1);
	return (new);
}

char	**my_recup_arg(char **tab_cmd, t_cmd *cmd)
{
	int		x;
	char	**res;
	char	*tmp;

	x = -1;
	res = NULL;
	tmp = NULL;
	if (cmd->path)
		tmp = ft_strjoin(cmd->path, cmd->cmd);
	else if (cmd->cmd)
		tmp = ft_strdup(cmd->cmd);
	res = realloc_double_tab(res, &tmp);
	tmp = my_free_tab((void **)&tmp);
	while ((*tab_cmd)[++x])
	{
		while (ft_whitespace((*tab_cmd)[x]) == 1)
			x++;
		tmp = my_recup_ellement(tab_cmd, &x);
		res = realloc_double_tab(res, &tmp);
		tmp = my_free_tab((void **)&tmp);
		if (!(*tab_cmd)[x])
			break ;
	}
	return (res);
}

char	*my_recup_pip(char **cmd)
{
	char	*res;
	int		x;
	int		red;
	int		gu;

	x = -1;
	res = NULL;
	gu = 0;
	while ((*cmd)[++x])
	{
		my_check_gu(&gu, (*cmd)[x]);
		if (gu != 0)
			continue ;
		red = my_check_red_pip(&((*cmd)[x]));
		if (red > 0 && red < 5)
			res = my_take_red(red, &x, cmd);
		if (!(*cmd)[x])
			break ;
	}
	if (!res)
		res = ft_strdup(";");
	return (res);
}
