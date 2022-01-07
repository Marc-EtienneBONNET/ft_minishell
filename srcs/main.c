/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/07 14:25:51 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_lancement_ex(void)
{
	t_cmd	*tmp;
	int		x;
	int		res;
	int		ret;

	x = 0;
	ret = 10;
	res = 0;
	term->cmd = my_parsing(term->str_cmd);
	free(term->str_cmd);
	//my_print_list_chene(term->cmd);
	tmp = term->cmd;
	signal(SIGQUIT, handler_ctr_backslash);
	signal(SIGINT, handler_ctr_c_2);
	while (x < term->cmd->info_cmd->nb_maillons)
	{
		term->pid = fork();
		if (term->pid == 0 && tmp)
		{
			res = my_exe_cmd(term, tmp);
			if (tmp->red[0] != ';' || tmp->next == NULL || res < 0)
			{
				exit(ret);
				break ;
			}
		}
		waitpid(term->pid, &ret, 0);
		if (WIFEXITED(ret))
			ret = WEXITSTATUS(ret);
		term->dernier_ret = ret;
		if (ret != 0 && ft_strncmp(tmp->red, "&&", 3) == 0)
			break ;
		if (ret == 0 && ft_strncmp(tmp->red, "||", 3) == 0)
			break ;
		tmp = tmp->next;
		x++;
	}
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	my_free_liste_chene(term->cmd);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (-1);
	term = malloc(sizeof(t_term));
	bzero(term, sizeof(t_term));
	term->envp = envp;
	term->pid = 1;
	printf("\e[1;32mBien venu dans le terminal\e\n[0m");
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	while (term->pid != 0 && 1)
	{
		term->str_cmd = NULL;
		term->str_cmd = readline("\e[1;34mMinishell> \e[0m");
		add_history(term->str_cmd);
		if (term->str_cmd == 0)
		{
			free(term->str_cmd);
			free(term);
			exit(0);
		}
		if (term->str_cmd[0])
			my_lancement_ex();
	}
	free(term);
	return (0);
}
