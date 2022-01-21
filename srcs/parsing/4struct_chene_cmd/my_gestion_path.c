/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gestion_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:48:58 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/21 15:52:18 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**my_recup_path_2(void)
{
	char	**path;
	int		y;

	y = 0;
	while (g_term.my_env[y].key
		&& ft_strncmp(g_term.my_env[y].key, "PATH", 5) != 0)
		y++;
	if (g_term.my_env[y].key == NULL)
		return (NULL);
	path = ft_split(g_term.my_env[y].var, ':');
	return (path);
}

char	*my_recup_path(t_cmd *cmd)
{
	char	**path;
	int		y;
	char	*tmp;
	char	*tmp_2;

	path = my_recup_path_2();
	if (!path)
		return (NULL);
	y = -1;
	while (path[++y])
	{
		tmp_2 = ft_strjoin(path[y], "/");
		tmp = ft_strjoin(tmp_2, cmd->cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(tmp);
			my_free_double_tab((void *)path, -1);
			return (tmp_2);
		}
		free(tmp_2);
		free(tmp);
	}
	my_free_double_tab((void *)path, -1);
	return (ft_strdup("sans_fichier"));
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
		res = my_recup_path(tmp);
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
