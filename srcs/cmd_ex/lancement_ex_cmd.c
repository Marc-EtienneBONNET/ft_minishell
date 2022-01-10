/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/10 10:45:33 by mbonnet          ###   ########.fr       */
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
		if (cmd->previous && (ft_strncmp(cmd->previous->red, ">", 3) == 0
				|| ft_strncmp(cmd->previous->red, ">>", 3) == 0))
			return (1);
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

void	my_gestion_red_gauche(void)
{
	char	**tmp;
	int		len;

	len = 0;
	while (term->cmd->arg[len])
		len++;
	if (ft_strncmp(term->cmd->red, "<", 3) == 0)
	{
		tmp = ft_strdoublejoin(term->cmd->arg, term->cmd->next->cmd);
		my_free_double_tab((void **)term->cmd->arg, -1);
		term->cmd->arg = tmp;
	}
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
		my_gestion_red_gauche();
		my_lancement_ex2(term->cmd, &x);
		if (ft_strncmp(term->cmd->red, "<", 3) == 0)
		{
			term->cmd = term->cmd->next;
			x++;
		}
		term->cmd = term->cmd->next;
		x++;
	}
	term->cmd = tmp;
	my_kill_tub(term->cmd);
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(term->cmd);
	return (1);
}
