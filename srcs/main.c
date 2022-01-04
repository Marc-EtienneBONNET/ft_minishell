/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:50:35 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/04 18:39:02 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int ac, char **av)
{
	char	*str;

	(void)av;
	(void)ac;
	printf("\e[1;32mBien venu dans le terminal\n\e[0m");
	signal(SIGINT, handler_ctr_c);
	while (1)
	{
		str = readline("\e[1;34mMinishell> \e[0m");
		add_history(str);
		free(str);
		if (str == 0)
		{
			printf("\nil faux encore :\n\t-free les variable aloue\n\t-fermer l'ensemble des processes\n");
			exit(0);
		}
	}
	return (0);
}
