/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/08 12:22:05 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_lancement_building(t_cmd *cmd)
{
	char	*cpe;

	cpe = cmd->cmd;
	if (ft_strncmp(cpe, "cd", 10) == 0)
		printf("commande cd\n");
	else if (ft_strncmp(cpe, "pwd", 10) == 0)
		my_pwd(cmd);
	else if (ft_strncmp(cpe, "echo", 10) == 0)
		my_echo(cmd->arg);
	else if (ft_strncmp(cpe, "export", 10) == 0)
		printf("commande export\n");
	else if (ft_strncmp(cpe, "unset", 10) == 0)
		printf("commande unset\n");
	else if (ft_strncmp(cpe, "env", 5) == 0)
		my_env(cmd);
	else if (ft_strncmp(cpe, "exit", 5) == 0)
		printf("commande exit\n");
}


int	my_lancement_ex2_2(t_cmd *tmp)
{
	int	res;
	int	route;

	route = 0;
	pipe(term->tub);
	term->pid = fork();
	route = my_create_tub(tmp);
	if (route == -1)
		printf("%s : fichier introuvable\n", tmp->cmd);
	if (term->pid == 0 && tmp)
	{
		res = my_exe_cmd(term, tmp);
		exit(res);
	}
	waitpid(term->pid, &res, 0);
	if (WIFEXITED(res))
		res = WEXITSTATUS(res);
	term->dernier_ret = res;
	if (term->dernier_ret != 0)
		if ((tmp->previous && ft_strncmp(tmp->previous->red, ">>", 3) != 0))
			printf("%s : commande introuvable\n", tmp->cmd);
	if (term->dernier_ret != 0 && (ft_strncmp(tmp->red, "&&", 3) == 0
			|| ft_strncmp(tmp->red, "|", 3) == 0))
		return (-1);
	if (term->dernier_ret == 0 && ft_strncmp(tmp->red, "||", 3) == 0)
		return (-1);
	return (1);
}

int	my_exe_cmd(t_term *term, t_cmd *cmd)
{
	char	*cpe;

	cpe = cmd->cmd;
	if (ft_strncmp(cpe, "cd", 10) == 0
		|| ft_strncmp(cpe, "pwd", 10) == 0
		|| ft_strncmp(cpe, "echo", 10) == 0
		|| ft_strncmp(cpe, "export", 10) == 0
		|| ft_strncmp(cpe, "unset", 10) == 0
		|| ft_strncmp(cpe, "env", 5) == 0
		|| ft_strncmp(cpe, "exit", 5) == 0)
		my_lancement_building(cmd);
	else
	{
		cpe = ft_strjoin(cmd->path, cmd->cmd);
		if (execve(cpe, cmd->arg, term->envp) == -1)
		{
			free(cpe);
			if (ft_strncmp(cmd->red, "||", 3) == 0)
				return (-2);
			return (-1);
		}
		free(cpe);
	}
	return (0);
}

int	my_lancement_ex2(t_cmd *tmp, int *x)
{
	int	res;

	pipe(term->tub);
	term->pid = fork();
	my_create_tub(tmp);
	if (term->pid == 0 && tmp)
	{
		res = my_exe_cmd(term, tmp);
		exit(res);
	}
	waitpid(term->pid, &res, 0);
	if (WIFEXITED(res))
		res = WEXITSTATUS(res);
	term->dernier_ret = res;
	my_gestion_ou(res, tmp, x);
	my_gestion_et(res, tmp, x);
	my_gestion_pip(res, tmp);
	my_gestion_double_red_droite(res, tmp, x);
	my_gestion_virgule_point(res, tmp);
	
	return (1);
}

int	my_lancement_ex(void)
{
	t_cmd	*tmp;
	int		x;

	x = 0;
	term->cmd = my_parsing(term->str_cmd);
	free(term->str_cmd);
	tmp = term->cmd;
	signal(SIGQUIT, handler_ctr_backslash);
	signal(SIGINT, handler_ctr_c_2);
	while (x < term->cmd->info_cmd->nb_maillons)
	{
		my_lancement_ex2(term->cmd, &x);
		term->cmd = term->cmd->next;
		x++;
	}
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(term->cmd);
	my_kill_tub(tmp);
	return (1);
}
