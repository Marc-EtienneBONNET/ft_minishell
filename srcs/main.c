/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/07 15:06:13 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_free_all(int ret)
{
	int	x;

	x = 0;
	while (term->my_env[x].key != NULL)
	{
		free(term->my_env[x].key);
		free(term->my_env[x].var);
		x++;
	}
	free(term->my_env);
	if (term->str_cmd)
		free(term->str_cmd);
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
		add_history(term->str_cmd);
		if (term->str_cmd == 0)
			return (my_free_all(-1));
		if (term->str_cmd[0])
			my_lancement_ex();
	}
	return (my_free_all(0));
}
