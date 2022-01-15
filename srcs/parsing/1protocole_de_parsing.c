/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1protocole_de_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 08:28:28 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/15 15:54:16 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*my_parsing(void)
{
	char		**tab_cmd;
	char		*cmd_tmp_env;
	t_cmd		*cmd;
	int			i;
	char		*tmp;

	i = 0;
	cmd = NULL;
	tmp = ft_strdup(term->str_cmd);
	free(term->str_cmd);
	term->str_cmd = my_modif_for_export(tmp);
	free(tmp);
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
	printf("ici : %s\n", tab_cmd[1]);
	my_free_tab((void *)cmd_tmp_env);
	cmd = my_init_struct_cmd(tab_cmd);
	if (!cmd)
		return (NULL);
	my_mouv_struct_for_red(&cmd);
	//my_print_list_chene(cmd);
	return (cmd);
}
