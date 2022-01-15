/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/15 11:00:22 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_free_all(int ret)
{
	int	x;

	x = 0;
	my_free_double_tab((void **)term->exp, -1);
	while (term->my_env && term->my_env[x].key != NULL)
	{
		free(term->my_env[x].key);
		free(term->my_env[x].var);
		x++;
	}
	rl_clear_history();
	free(term->my_env);
	free(term);
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (-1);
	term = malloc(sizeof(t_term));
	bzero(term, sizeof(t_term));
	term->envp = envp;
	my_init_struct_env();
	creat_export();
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
			my_lancement_ex();
		}
		else
			free(term->str_cmd);
	}
	return (my_free_all(0));
}
