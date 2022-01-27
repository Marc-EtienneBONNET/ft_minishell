/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:50:08 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 17:57:21 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_recup_var(char *key)
{
	int	x;

	x = -1;
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

int	my_gestion_env_heredoc(char **tmp)
{
	int		x;
	char	*key;
	char	*var;
	char	*tmp_2;

	x = -1;
	key = NULL;
	while ((*tmp)[++x])
	{
		if ((*tmp)[x] != '$')
			continue ;
		(*tmp)[x] = '\0';
		tmp_2 = ft_strdup(*tmp);
		(*tmp)[x] = '$';
		while (ft_whitespace((*tmp)[++x]) != 1 && (*tmp)[x])
			key = ft_strmicrojoin(&key, (*tmp)[x]);
		var = my_recup_var(key);
		key = my_free_tab(key);
		my_gestion_env_heredoc_2(tmp, &tmp_2, &var, x);
	}
	return (1);
}
