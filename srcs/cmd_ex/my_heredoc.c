/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:29:16 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/20 15:46:05 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	my_concatonne_2(char **tmp, char **str, char **tmp_2)
{
	*tmp_2 = ft_strdup((*tmp));
	if (!(*tmp_2) && *tmp != NULL)
		return (-1);
	free((*tmp));
	if ((*tmp_2))
	{
		(*tmp) = ft_strjoin((*tmp_2), (*str));
		if (!(*tmp))
			return (-1);
		free((*tmp_2));
	}
	else
		(*tmp) = ft_strdup((*str));
	(*tmp_2) = ft_strdup((*tmp));
	if (!(*tmp_2))
		return (-1);
	free((*tmp));
	(*tmp) = ft_strjoin((*tmp_2), "\n");
	if (!(*tmp))
		return (-1);
	free((*tmp_2));
	return (1);
}

int	my_concatonne(char **tmp, char **str)
{
	char	*tmp_2;

	tmp_2 = NULL;
	if (g_term.cmd->fichier_2 == NULL)
	{
		if (my_concatonne_2(tmp, str, &tmp_2) == -1)
			return (-1);
	}
	else if (ft_strncmp((*str), g_term.cmd->fichier_2, 1000) == 0
		&& g_term.cmd->fichier_2)
	{
		free(g_term.cmd->fichier_2);
		g_term.cmd->fichier_2 = NULL;
	}
	free((*str));
	return (1);
}

void	my_sorti(char **str, char **tmp, int *tub)
{
	(void)tub;
	free(*str);
	write(1, *tmp, ft_strlen(*tmp));
	if (*tmp)
		free(*tmp);
	exit (0);
}

void	my_heredoc(pid_t pid, int *tub)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	if (pid != 0)
	{
		close(tub[ENTRE]);
		dup2(tub[SORTI], 0);
		close(tub[SORTI]);
		return ;
	}
	while (1)
	{
		str = readline(VERT"heredoc>"BLANC);
		if (ft_strncmp(str, g_term.cmd->fichier_1, 1000) == 0)
		{
			close(tub[SORTI]);
			dup2(tub[ENTRE], 1);
			close(tub[ENTRE]);
			my_sorti(&str, &tmp, tub);
		}
		if (my_concatonne(&tmp, &str) == -1)
		{
			exit (-1);
		}
	}
	exit (0);
}
