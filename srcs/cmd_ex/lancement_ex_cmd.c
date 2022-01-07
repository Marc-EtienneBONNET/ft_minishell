/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/07 18:58:42 by mbonnet          ###   ########.fr       */
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
		cpe = ft_strjoin(cmd->path, cmd->cmd);
		if (execve(cpe, cmd->arg, term->envp) == -1)
		{
			free(cpe);
			if (ft_strncmp(cmd->red, "||", 3) == 0)
				return (-2);
			printf("%s : commande introuvable\n", cmd->cmd);
			return (-1);
		}
		free(cpe);
	}
	return (1);
}

void	my_lancement_ex2(t_cmd *tmp)
{
	int	res;

	term->pid = fork();
	if (term->pid == 0 && tmp)
	{
		res = my_exe_cmd(term, tmp);
		if (tmp->red[0] != ';' || tmp->next == NULL || res < 0)
			exit(res);
	}
	waitpid(term->pid, &res, 0);
	if (WIFEXITED(res))
		res = WEXITSTATUS(res);
	term->dernier_ret = res;
}

int	my_lancement_ex(void)
{
	t_cmd	*tmp;
	int		x;

	x = 0;
	term->cmd = my_parsing(term->str_cmd);
	free(term->str_cmd);
	my_print_list_chene(term->cmd);
	tmp = term->cmd;
	signal(SIGQUIT, handler_ctr_backslash);
	signal(SIGINT, handler_ctr_c_2);
	while (x < term->cmd->info_cmd->nb_maillons)
	{
		my_lancement_ex2(tmp);
		if (term->dernier_ret != 0 && ft_strncmp(tmp->red, "&&", 3) == 0)
			break ;
		if (term->dernier_ret == 0 && ft_strncmp(tmp->red, "||", 3) == 0)
			break ;
		tmp = tmp->next;
		x++;
	}
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(term->cmd);
	return (1);
}
