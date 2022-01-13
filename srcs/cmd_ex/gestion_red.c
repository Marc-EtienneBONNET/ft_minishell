/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:07:30 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/13 09:09:27 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_choose_fichier(void)
{
	char	*res;

	if (ft_strncmp(term->cmd->path, "/bin/", 7) == 0)
		res = ft_strjoin("./", term->cmd->cmd);
	else
		res = ft_strjoin(term->cmd->path, term->cmd->cmd);
	return (res);
}

int	my_gestion_red_droite(char *choose)
{
	int		fd;
	char	*fichier;
	char	c;
	
	fichier = my_choose_fichier();
	if (ft_strncmp(term->cmd->previous->red, ">", 10) != 0
		&& ft_strncmp(term->cmd->previous->red, ">>", 10) != 0)
		return (1);
	if (ft_strncmp(choose, ">", 3) == 0)
	{
		fd = open(fichier, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			remove(fichier);
		}
	}
	fd = open(fichier, O_RDONLY);
	if (fd == -1)
	{
		fd = open(fichier, O_CREAT);
		close(fd);
	}
	else
		close(fd);
	fd = open(fichier, O_RDWR);
	while (read(fd, &c, 1) > 0);
	while (read(term->tub[SORTI], &c, 1) > 0)
		write(fd, &c, 1);
	close(fd);
	free(fichier);
	return (1);
}

int	my_gestion_red_gauche(void)
{
	int		fd;
	char	*fichier;
	char	c;

	term->cmd = term->cmd->next;
	fichier = my_choose_fichier();
	term->cmd = term->cmd->previous;
	fd = open(fichier, O_RDWR);
	if (fd < 0)
		return (-1);
	while (read(fd, &c, 1) > 0)
		write(1, &c, 1);
	return (1);
}
