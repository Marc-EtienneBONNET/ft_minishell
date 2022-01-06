/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/06 16:50:59 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			term->cmd = my_parsing(term->str_cmd);
			term->pid = fork();
			signal(SIGINT, handler_ctr_c_2);
			if (term->pid == 0 && term->cmd)
				my_exe_cmd(term);
			waitpid(term->pid, NULL, 0);
			signal(SIGINT, handler_ctr_c);
			my_print_list_chene(term->cmd);
			my_free_liste_chene(term->cmd);
		}
		free(term->str_cmd);
	}
	free(term);
	return (0);
}
