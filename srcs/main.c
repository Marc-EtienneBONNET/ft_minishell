/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/08 08:36:31 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_free_all(int ret)
{
	int	x;

	x = 0;
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
	term->pid = 1;
	printf("\e[1;32mBien venu dans le terminal\e\n[0m");
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	while (term->pid != 0 && 1)
	{
		term->str_cmd = NULL;
		term->str_cmd = readline("\e[1;34mMinishell> \e[0m");
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
