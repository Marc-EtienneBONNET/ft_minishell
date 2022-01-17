/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1protocole_de_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 08:28:28 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 16:12:21 by mbonnet          ###   ########.fr       */
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
	if (!tmp)
		return (NULL);
	free(term->str_cmd);
	term->str_cmd = my_modif_for_export(tmp);
	free(tmp);
	if (term->str_cmd == NULL)
		return (NULL);
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
	{
		//my_free_double_tab((void **)tab_cmd, -1);
		return (NULL);
	}
	if (!my_mouv_struct_for_red(&cmd))
		return (my_free_liste_chene(cmd));
	return (cmd);
}
