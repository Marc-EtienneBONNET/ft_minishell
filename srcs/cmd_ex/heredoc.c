/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:12:17 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 18:06:53 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_concatonne(char **tmp, char **str)
{
	char	*tmp_2;

	tmp_2 = NULL;
	if (g_term->cmd->fichier_2 == NULL)
	{
		tmp_2 = ft_strdup((*tmp));
		if (!tmp_2 && *tmp != NULL)
			return (-1);
		free((*tmp));
		(*tmp) = ft_strjoin(tmp_2, (*str));
		if (!(*tmp))
			return (-1);
		free(tmp_2);
		tmp_2 = ft_strdup((*tmp));
		if (!tmp_2)
			return (-1);
		free((*tmp));
		(*tmp) = ft_strjoin(tmp_2, "\n");
		if (!(*tmp))
			return (-1);
		free(tmp_2);
	}
	else if (ft_strncmp((*str), g_term->cmd->fichier_2, 1000) == 0
		&& g_term->cmd->fichier_2)
	{
		free(g_term->cmd->fichier_2);
		g_term->cmd->fichier_2 = NULL;
	}
	free((*str));
	return (1);
}

void	my_heredoc(pid_t pid)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	if (pid != 0)
	{
		my_tub_sorti_entre_parent(g_term->cmd);
		return ;
	}
	while (1)
	{
		str = readline(">");
		if (ft_strncmp(str, g_term->cmd->fichier_1, 1000) == 0)
		{
			my_tub_entre_sorti_enfant(g_term->cmd);
			free(str);
			write(1, tmp, ft_strlen(tmp));
			if (tmp)
				free(tmp);
			exit (0);
		}
		if (my_concatonne(&tmp, &str) == -1)
			exit (-1);
	}
	exit (0);
}
