/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:50:08 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/28 15:47:01 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_recup_var(char *key)
{
	int	x;

	x = -1;
	if (key[0] == '?')
		return (ft_strdup(ft_itoa(g_term.dernier_ret)));
	while (g_term.my_env[++x].key)
		if (ft_strncmp(g_term.my_env[x].key, key, ft_strlen(key)) == 0)
			return (ft_strdup(g_term.my_env[x].var));
	return (NULL);
}

int	my_gestion_env_heredoc_2(char **tmp, char **tmp_2, char **var, int x)
{
	char	*tmp_1;

	tmp_1 = ft_strjoin((*tmp_2), (*var));
	(*tmp_2) = my_free_tab((*tmp_2));
	(*tmp_2) = ft_strdup(tmp_1);
	tmp_1 = my_free_tab(tmp_1);
	tmp_1 = ft_strjoin((*tmp_2), &((*tmp)[x]));
	(*tmp_2) = my_free_tab((*tmp_2));
	*tmp = my_free_tab(*tmp);
	*tmp = ft_strdup(tmp_1);
	tmp_1 = my_free_tab(tmp_1);
	return (1);
}

int	my_check_red_gauche_avant_env(char *str, int x)
{
	x--;
	while (ft_whitespace(str[x]) == 1 || str[x] == '\"' || str[x] == '\'')
		x--;
	if (str[x] == '<' && str[x - 1] == '<')
		return (1);
	return (0);
}

int	my_gestion_env_heredoc(char **tmp)
{
	int		x;
	char	*key;
	char	*var;
	char	*tmp_2;
	int		gu;

	x = -1;
	key = NULL;
	gu = 0;
	while ((*tmp)[++x])
	{
		my_check_guil(&gu, (*tmp)[x]);
		if (((*tmp)[x] != '$' || gu == 1))
			continue ;
		if ((*tmp)[x] == '$' && my_check_red_gauche_avant_env(*tmp, x) == 1 && (gu == 0 || gu == 2))
			continue ;
		(*tmp)[x] = '\0';
		tmp_2 = ft_strdup(*tmp);
		(*tmp)[x] = '$';
		while (ft_whitespace((*tmp)[++x]) != 1 && (*tmp)[x]
			&& (*tmp)[x] != '\"')
		{
			my_check_guil(&gu, (*tmp)[x]);
			key = ft_strmicrojoin(&key, (*tmp)[x]);
		}
		var = my_recup_var(key);
		key = my_free_tab(key);
		if (!var)
		{
			tmp_2 = my_free_tab(tmp_2);
			return (-1);
		}
		my_gestion_env_heredoc_2(tmp, &tmp_2, &var, x);
	}
	return (1);
}

int	ft_modif_fd(char **tmp)
{
	char	*tmp_2;
	char	c;

	if (!(*tmp))
		return (0);
	if (((*tmp)[ft_strlen(*tmp) - 1] == '\"'
		&& (*tmp)[ft_strlen(*tmp) - 2] == '\"')
		|| ((*tmp)[ft_strlen(*tmp) - 1] == '\''
			&& (*tmp)[ft_strlen(*tmp) - 2] == '\''))
	{
		c = *tmp[ft_strlen(*tmp) - 2];
		(*tmp)[ft_strlen(*tmp) - 2] = '\0';
		tmp_2 = ft_strdup(*tmp);
		(*tmp)[ft_strlen(*tmp) - 2] = c;
		*tmp = my_free_tab(*tmp);
		*tmp = ft_strdup(tmp_2);
		return (1);
	}
	return (0);
}
