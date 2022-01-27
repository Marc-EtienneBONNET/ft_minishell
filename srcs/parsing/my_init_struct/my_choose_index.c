/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_choose_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:15:46 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/26 13:07:36 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_take_fichier_and_intra_red(char *str, t_cmd *tmp)
{
	int		x;
	int		gu;
	int		red;

	x = -1;
	gu = 0;
	while (str[++x])
	{
		my_check_guil(&gu, str[x]);
		red = my_check_redirection(&(str[x]));
		if (red > 1)
			tmp->intra_red = recup_red(&(str[x]));
		if (red == 3)
			x++;
		if (red > 1 && gu == 0 && !tmp->fichier_1)
			tmp->fichier_1 = recup_element(str, ++x);
		else if (red > 1 && gu == 0 && tmp->fichier_1)
			tmp->fichier_2 = recup_element(str, ++x);
	}
}

int	my_passe_fichier(int x, int red, char *str, int *gu)
{
	x++;

	if (red == 3)
		x++;
	while (ft_whitespace(str[x]) == 1)
		x++;
	while (str[x])
	{
		my_check_guil(gu, str[x]);
		if (*gu == 0 && (ft_whitespace(str[x]) == 1
				|| my_check_redirection(&(str[x])) > 0
				|| !str[x]))
			break ;
		x++;
	}
	return (x);
}

char	*my_choose_path(t_cmd *tmp)
{
	int		x;
	char	**path;
	char	*tmp_2;
	char	*tmp_3;

	x = 0;
	while (g_term.my_env[x].key
		&& ft_strncmp(g_term.my_env[x].key, "PATH=", 5) != 0)
		x++;
	if (!g_term.my_env[x].key)
		return (NULL);
	path = ft_split(g_term.my_env[x].var, ':');
	x = -1;
	while (path[++x])
	{
		tmp_2 = ft_strjoin(path[x], "/");
		tmp_3 = ft_strjoin(tmp_2, tmp->cmd);
		if (access(tmp_3, F_OK) != 0)
		{
			my_free_tab(tmp_2);
			my_free_tab(tmp_3);
			if (path[x + 1] == NULL)
			{
				my_free_double_tab((void **)path, -1);
				return (NULL);
			}
		}
		else
		{
			my_free_tab(tmp_3);
			break ;
		}
	}
	my_free_double_tab((void **)path, -1);
	return (tmp_2);
}

int	my_recup_path(t_cmd *tmp)
{
	int		len;
	char	*tmp_2;

	if (!tmp->cmd)
		return (1);
	len = ft_strlen(tmp->cmd);
	while (--len >= 0)
		if (tmp->cmd[len] == '/')
			break ;
	if (len == -1)
	{
		tmp->path = my_choose_path(tmp);
	}
	else
	{
		tmp_2 = ft_strdup(tmp->cmd);
		tmp_2[len + 1] = '\0';
		tmp->path = ft_strdup(tmp_2);
		if (access(tmp->path, F_OK) != 0)
			tmp->path = my_free_tab(tmp->path);
		tmp_2[len + 1] = 'a';
		my_free_tab(tmp_2);
		tmp_2 = ft_strdup(&(tmp->cmd[len + 1]));
		my_free_tab(tmp->cmd);
		tmp->cmd = ft_strdup(tmp_2);
		free(tmp_2);
	}
	return (1);
}

int	my_take_cmd_and_path(char *str, t_cmd *tmp)
{
	int	x;
	int	gu;
	int	red;

	x = -1;
	gu = 0;
	while (str[++x])
	{
		my_check_guil(&gu, str[x]);
		red = my_check_redirection(&(str[x]));
		if (ft_whitespace(str[x]) == 1)
			continue ;
		else if (red > 1 && gu == 0)
			x = my_passe_fichier(x, red, str, &gu);
		else
			break ;
	}
	tmp->cmd = recup_element(str, x);
	my_recup_path(tmp);
	return (1);
}
