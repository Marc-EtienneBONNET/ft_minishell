/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 18:13:43 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_term g_term;

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (-1);
	g_term.envp = envp;
	if (my_init_struct_env() == -1)
		return (-1);
	printf(VERT"Bien venu dans le g_terminal\n"BLANC);
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_term.str_cmd = NULL;
		g_term.str_cmd = readline(BLEU_2"Minishell> "BLANC);
		if (g_term.str_cmd == 0)
		{
			free(g_term.str_cmd);
			rl_clear_history();
			return (my_free_all(-1));
		}
		if (g_term.str_cmd[0])
		{
			add_history(g_term.str_cmd);
			if (my_lancement_ex() == -1)
				return (my_free_all(-1));
		}
		else
			free(g_term.str_cmd);
	}
	return (my_free_all(0));
}
