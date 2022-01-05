/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/05 12:01:57 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)av;
	term = malloc(sizeof(t_term));
	term->envp = envp;
	term->pid = 1;
	if (ac != 1)
		return (-1);
	printf("\e[1;32mBien venu dans le terminal\n\e[0m");
	//ce signale permet de controler l utilisation du ctr c (la fonction qu il qppel hendler_ctr_c n est pas encore fini)
	signal(SIGINT, handler_ctr_c);
	while (term->pid != 0 && 1)
	{
		term->str_cmd = NULL;
		term->str_cmd = readline("\e[1;34mMinishell> \e[0m");
		add_history(term->str_cmd);
		if (term->str_cmd == 0)
		{
			free(term->str_cmd);
			printf("\nil faux encore :\n\t-free les variable aloue\n\t-fermer l'ensemble des processes\n");
			exit(0);
		}
		term->cmd = term->cmd = my_parsing(term->str_cmd);
		free(term->str_cmd);
		my_print_list_chene(term->cmd);
		term->pid = fork();
		if (term->pid == 0)
			my_exe_cmd(term);
		waitpid(term->pid, NULL, 0);
		my_free_liste_chene(term->cmd);
	}
	return (0);
}
