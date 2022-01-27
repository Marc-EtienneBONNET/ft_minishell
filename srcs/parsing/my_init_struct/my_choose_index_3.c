/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_choose_index_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:15:46 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 14:01:21 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (len != -1)
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
	tmp->path = my_choose_path(tmp);
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
