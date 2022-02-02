/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gestion_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:50:53 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/02 11:59:49 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_recup_cmd(char **str)
{
	char	*res;
	int		x;

	x = -1;
	res = NULL;
	while ((*str)[++x])
	{
		if (ft_whitespace((*str)[x]) == 1)
			continue ;
		res = my_recup_ellement(str, &x);
		break ;
	}
	return (res);
}

char	*my_recup_path(char **str)
{
	char	*res;
	char	*tmp;
	int		len;
	char	c;

	res = NULL;
	len = ft_strlen(*str);
	while (--len >= 0)
		if ((*str)[len] == '/')
			break ;
	if (len >= 0)
	{
		c = (*str)[len + 1];
		(*str)[len + 1] = '\0';
		res = ft_strdup(*str);
		(*str)[len + 1] = c;
		tmp = ft_strdup(&((*str)[len + 1]));
		(*str) = my_free_tab((void **)str);
		(*str) = tmp;
	}
	return (res);
}

char	**my_recup_path_env_2(void)
{
	char	**path;
	int		x;

	x = 0;
	if (!g_term.my_env)
		return (NULL);
	while (g_term.my_env[x].key)
	{
		if (ft_strncmp(g_term.my_env[x].key,
				"PATH=", ft_strlen(g_term.my_env[x].key)) == 0)
		{
			path = ft_split(g_term.my_env[x].var, ':');
			break ;
		}
		x++;
	}
	if (!g_term.my_env[x].key)
		return (NULL);
	return (path);
}

char	*my_recup_path_env(char *cmd)
{
	char	**path;
	char	*tmp_2;
	char	*tmp;
	int		x;

	tmp = NULL;
	path = my_recup_path_env_2();
	x = -1;
	while (cmd && path && path[++x])
	{
		tmp = ft_strjoin(path[x], "/");
		tmp_2 = ft_strjoin(tmp, cmd);
		if (access(tmp_2, F_OK) == 0)
		{
			tmp_2 = my_free_tab((void **)&tmp_2);
			break ;
		}
		tmp = my_free_tab((void **)&tmp);
		tmp_2 = my_free_tab((void **)&tmp_2);
	}
	path = my_free_double_tab((void **)path, -1);
	return (tmp);
}
