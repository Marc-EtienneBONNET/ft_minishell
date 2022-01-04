/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:07:31 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/04 16:20:22 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*str;

	(void)av;
	(void)ac;
	printf("\e[1;32mBien venu dans le terminal\n\e[0m");
	while (1)
	{
		str = readline("\e[1;34mMinishell> \e[0m");
	}
	return (0);
}
