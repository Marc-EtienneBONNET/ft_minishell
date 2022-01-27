/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 14:07:15 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_term	g_term;

int	mise_en_place_de_lancement(int ac, char **envp)
{
	if (ac != 1)
		return (-1);
	printf(VERT"Bien venu dans le g_terminal\n"BLANC);
	signal(SIGINT, handler_ctr_c);
	signal(SIGQUIT, SIG_IGN);
	g_term.envp = envp;
	if (my_init_struct_env() == -1)
		return (-1);
	return (1);
}

int	my_check_space(char *str)
{
	int		x;
	int		tem;

	x = 0;
	tem = 0;
	while (str[x])
	{
		if (str[x] != ' ')
			tem = 1;
		x++;
	}
	if (tem != 1)
		return (-1);
	return (1);
}

int	my_check_guillemet_2(char *str)
{
	int		x;
	int		g_simple;
	int		g_double;

	x = -1;
	g_simple = 0;
	g_double = 0;
	while (str[++x])
	{
		if (str[x] == '\"' && g_double == 0 && g_simple == 0)
			g_double = 1;
		else if (str[x] == '\'' && g_simple == 0 && g_double == 0)
			g_simple = 1;
		else if (str[x] == '\"' && g_double == 1)
			g_double = 0;
		else if (str[x] == '\'' && g_simple == 1)
			g_simple = 0;
	}
	if (g_simple == 0 && g_double == 0)
		return (1);
	printf(VIOLET"minishell: (%s) erreur de sintaxe\n"BLANC,
		g_term.str_cmd);
	free(g_term.str_cmd);
	return (-1);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (mise_en_place_de_lancement(ac, envp) == -1)
		return (-1);
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
