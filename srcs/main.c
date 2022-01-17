/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 16:57:39 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (-1);
	term = malloc(sizeof(t_term));
	if (!term)
		return (-1);
	bzero(term, sizeof(t_term));
	term->envp = envp;
	if (my_init_struct_env() == -1)
		return (-1);
	printf(VERT"Bien venu dans le terminal\n"BLANC);
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		term->str_cmd = NULL;
		term->str_cmd = readline(BLEU_2"Minishell> "BLANC);
		if (term->str_cmd == 0)
		{
			free(term->str_cmd);
			rl_clear_history();
			return (my_free_all(-1));
		}
		if (term->str_cmd[0])
		{
			add_history(term->str_cmd);
			if (my_lancement_ex() == -1)
				return (my_free_all(-1));
		}
		else
			free(term->str_cmd);
	}
	return (my_free_all(0));
}
