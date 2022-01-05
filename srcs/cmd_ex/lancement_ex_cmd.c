/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lancement_ex_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:00:12 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/05 15:17:01 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_path_commande(void)
{
	char	**res;
	res = malloc(sizeof(char) * 10);
	if (!res)
		return NULL;
	printf("1\n");
	res[0] = "Bonjour";
	printf("2\n");
	return (res);
}

void	*my_exe_cmd(t_term *term)
{
	(void)term;
//	char **tab_path;

	//tab_path = init_path_commande();
	printf("process enfant\n");
	execve("/bin/ls", term->cmd->arg, term->envp);
	return (NULL);
}
