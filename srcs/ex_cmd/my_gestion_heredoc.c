/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gestion_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:48:24 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/03 11:48:19 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_sorti_2(char **str, char **res, int option, int *tub)
{
	close(tub[SORTI]);
	dup2(tub[ENTRE], 1);
	close(tub[ENTRE]);
	if (option == 0)
		my_check_var_env(res);
	write(2, (*res), ft_strlen((*res)));
	write(2, ": commande introuvable\n", ft_strlen(": commande introuvable\n"));
	*str = my_free_tab((void **)str);
	*res = my_free_tab((void **)res);
	exit(0);
	return (1);
}

int	my_choose_option(char *fin, char *deb)
{
	int	x;

	x = -1;
	while (fin[++x])
		if (fin[x] == '\"' || fin[x] == '\'')
			return (1);
	x = -1;
	while (deb && deb[++x])
		if (deb[x] == '\"' || deb[x] == '\'')
			return (1);
	return (0);
}

int	my_lancement_heredoc(char *deb, char *fin)
{
	pid_t	pid;
	int		tub[2];

	pipe(tub);
	pid = fork();
	if (pid != 0)
	{
		close(tub[ENTRE]);
		dup2(tub[SORTI], 0);
		close(tub[SORTI]);
	}
	if (pid == 0)
		my_heredoc(deb, fin, my_choose_option(fin, deb), tub);
	if (pid != 0)
		waitpid(pid, NULL, 0);
	return (1);
}

int	my_connect_heredoc(void)
{
	int		x;
	char	*fin;
	char	*deb;

	x = 0;
	fin = NULL;
	deb = NULL;
	while (g_term.cmd->red && g_term.cmd->red[x].red)
	{
		if (ft_strncmp(g_term.cmd->red[x].red, "<<", 3) == 0
			&& (!g_term.cmd->red[x + 1].red
				|| ft_strncmp(g_term.cmd->red[x + 1].red, "<<", 3) != 0))
		{
			fin = g_term.cmd->red[x].fichier;
			break ;
		}
		if (ft_strncmp(g_term.cmd->red[x].red, "<<", 3) == 0
			&& g_term.cmd->red[x].red
			&& ft_strncmp(g_term.cmd->red[x + 1].red, "<<", 3) == 0)
			deb = g_term.cmd->red[x].fichier;
		x++;
	}
	if (fin)
		my_lancement_heredoc(deb, fin);
	return (1);
}
