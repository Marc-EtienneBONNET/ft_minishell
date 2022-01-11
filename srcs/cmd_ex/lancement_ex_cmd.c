/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/11 15:02:32 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_choose_fichier()
{
	char	*res;

	if (ft_strncmp(term->cmd->path, "/bin/", 7) == 0)
		res = ft_strjoin("./",term->cmd->cmd);
	else
		res = ft_strjoin(term->cmd->path, term->cmd->cmd);
	return (res);
}

int	my_gestion_red_droite(int choose)
{
	int		fd;
	char	*fichier;
	char	c;

	fichier = my_choose_fichier();
	if (choose == 0)
	{
		fd = open(fichier, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			if (remove(fichier) == 0)
				printf("supretion fichier\n");
		}
		if (open(fichier, O_RDONLY) == -1)
		{
			fd = open(fichier, O_CREAT);
			close(fd);
		}
		fd = open(fichier, O_WRONLY);
		while (read(term->tub[SORTI], &c, 1) > 0)
			write(fd, &c, 1);
		close(fd);
	}
	free(fichier);
	return (1);
}

int	my_lancement_fork(void)
{
	int		res;

	res = 0;
	term->cmd->pid = fork();
	my_gestion_pip(term->cmd, 0);
	if (ft_strncmp(term->cmd->previous->red, ">", 10) == 0)
	{
		if (term->cmd->pid == 0)
			exit (0);
		else
			my_gestion_red_droite(0);
	}
	else if (ft_strncmp(term->cmd->cmd, "cd", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "pwd", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "echo", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "export", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "unset", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "env", 10) == 0
		|| ft_strncmp(term->cmd->cmd, "exit", 10) == 0)
	{
		if (term->cmd->pid == 0)
			exit (0);
		res = 1;
		my_ex_building(term->cmd);
	}
	else if (term->cmd->pid == 0)
	{
		my_exe_cmd(term, term->cmd);
	}
	term->cmd = term->cmd->next;
	return (1);
}

void	my_attente_waitpid(void)
{
	int	x;

	x = 0;
	while (x < term->cmd->info_cmd->nb_maillons)
	{
		waitpid(term->cmd->pid, &term->dernier_ret, 0);
		if (WIFEXITED(term->dernier_ret))
			term->dernier_ret = WEXITSTATUS(term->dernier_ret);
		if (term->dernier_ret != 0)
			printf("%s: commande introuvable\n", term->cmd->cmd);
		term->cmd = term->cmd->next;
		x++;
	}
}

int	my_lancement_ex(void)
{
	int		x;
	int		y;
	t_cmd	*tmp;

	y = 0;
	x = 0;
	term->cmd = my_parsing(term->str_cmd);
	free(term->str_cmd);
	signal(SIGQUIT, handler_ctr_backslash);
	signal(SIGINT, handler_ctr_c_2);
	tmp = term->cmd;
	pipe(term->tub);
	while (x++ < term->cmd->info_cmd->nb_maillons)
		my_lancement_fork();
	term->cmd = tmp;
	my_attente_waitpid();
	my_kill_tub();
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(term->cmd);
	return (1);
}
