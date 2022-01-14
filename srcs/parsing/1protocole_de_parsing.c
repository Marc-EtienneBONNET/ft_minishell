/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1protocole_de_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 08:28:28 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/14 14:24:08 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*my_parsing(char *cmd_tmp)
{
	char		**tab_cmd;
	char		*cmd_tmp_env;
	t_cmd		*cmd;
	int			i;

	i = 0;
	cmd = NULL;
	cmd_tmp_env = my_gestion_var_env(cmd_tmp);
	if (!cmd_tmp_env)
		return (my_free_tab(cmd_tmp_env));
	tab_cmd = my_malloc_chaine(cmd_tmp_env);
	if (tab_cmd == NULL)
	{
		my_free_tab(cmd_tmp_env);
		return (my_free_double_tab((void **)tab_cmd, -1));
	}
	my_rempli_tab_cmd(tab_cmd, cmd_tmp_env);
	my_free_tab((void *)cmd_tmp_env);
	cmd = my_init_struct_cmd(tab_cmd);
	if (!cmd)
		return (NULL);
	my_mouv_struct_for_red(&cmd);
	my_print_list_chene(cmd);
	return (cmd);
}
