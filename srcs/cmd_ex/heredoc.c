/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:12:17 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/14 12:12:57 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_concatonne(char **tmp, char **str)
{
	char	*tmp_2;

	tmp_2 = NULL;
	if (term->cmd->fichier_2 == NULL)
	{
		tmp_2 = ft_strdup((*tmp));
		free((*tmp));
		(*tmp) = ft_strjoin(tmp_2, (*str));
		free(tmp_2);
		tmp_2 = ft_strdup((*tmp));
		free((*tmp));
		(*tmp) = ft_strjoin(tmp_2, "\n");
		free(tmp_2);
	}
	else if (ft_strncmp((*str), term->cmd->fichier_2, 1000) == 0
		&& term->cmd->fichier_2)
	{
		free(term->cmd->fichier_2);
		term->cmd->fichier_2 = NULL;
	}
	free((*str));
}

void	my_heredoc(pid_t pid)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	if (pid != 0)
	{
		my_tub_sorti_entre_parent(term->cmd);
		return ;
	}
	while (1)
	{
		str = readline(">");
		if (ft_strncmp(str, term->cmd->fichier_1, 1000) == 0)
		{
			my_tub_entre_sorti_enfant(term->cmd);
			free(str);
			write(1, tmp, ft_strlen(tmp));
			if (tmp)
				free(tmp);
			exit (0);
		}
		my_concatonne(&tmp, &str);
	}
	exit (0);
}
