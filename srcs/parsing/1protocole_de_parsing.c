/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1protocole_de_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 08:28:28 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/15 11:02:47 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*my_parsing(void)
{
	char		**tab_cmd;
	char		*cmd_tmp_env;
	t_cmd		*cmd;
	int			i;

	i = 0;
	cmd = NULL;
	term->str_cmd = my_modif_for_export(term->str_cmd);
	cmd_tmp_env = my_gestion_var_env(term->str_cmd);
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
