/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_protocole_de_parsing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 08:28:28 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/26 11:27:51 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_parsing(void)
{
	char	**tab_cmd;

	if (my_check_guillemet() == -1)
		return (-1);
	if (my_check_var_env() == -1)
		return (-2);
	tab_cmd = my_creat_tab_cmd();
	if (!tab_cmd)
	{
		my_free_double_tab((void *)tab_cmd, -1);
		return (-3);
	}
	if (my_init_struct(tab_cmd) == -1)
		return (-4);
	return (1);
}
