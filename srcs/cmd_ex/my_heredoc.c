/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:29:16 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 18:59:57 by mbonnet          ###   ########.fr       */
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

int	my_concatonne(char **tmp, char **str, char **fd_ouv)
{
	char	*tmp_2;

	tmp_2 = NULL;
	if (*fd_ouv == NULL)
	{
		if (my_concatonne_2(tmp, str, &tmp_2) == -1)
			return (-1);
	}
	else if (ft_strncmp((*str), *fd_ouv, 1000) == 0
		&& fd_ouv)
		*fd_ouv = my_free_tab(*fd_ouv);
	free((*str));
	return (1);
}

void	my_sorti(char **str, char **tmp, int *tub, int x)
{
	(void)tub;
	free(*str);
	if (x == 0)
		my_gestion_env_heredoc(tmp);
	write(1, *tmp, ft_strlen(*tmp));
	if (*tmp)
		free(*tmp);
	exit (0);
}

void	my_tub(int tele, int *tub)
{
	if (tele == 0)
	{
		close(tub[ENTRE]);
		dup2(tub[SORTI], 0);
		close(tub[SORTI]);
	}
	else
	{
		close(tub[SORTI]);
		dup2(tub[ENTRE], 1);
		close(tub[ENTRE]);
	}
}

void	my_heredoc(pid_t pid, int *tub, char *fd_ouv, char	*fd_ferm)
{
	char	*str;
	char	*tmp;
	int		x;

	str = NULL;
	tmp = NULL;
	if (pid != 0)
	{
		my_tub(0, tub);
		return ;
	}
	x = ft_modif_fd(&fd_ouv);
	x += ft_modif_fd(&fd_ferm);
	while (1)
	{
		str = readline(VERT"heredoc>"BLANC);
		if (ft_strncmp(str, fd_ferm, 1000) == 0 && fd_ouv == NULL)
		{
			my_tub(1, tub);
			my_sorti(&str, &tmp, tub, x);
		}
		if (my_concatonne(&tmp, &str, &fd_ouv) == -1)
			exit (-1);
	}
	exit (0);
}
