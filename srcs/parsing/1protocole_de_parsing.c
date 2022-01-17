/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1protocole_de_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 08:28:28 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 18:06:53 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_parsing(void)
{
	char		**tab_cmd;
	char		*cmd_tmp_env;
	t_cmd		*cmd;
	int			i;
	char		*tmp;

	i = 0;
	cmd = NULL;
	tmp = ft_strdup(g_term->str_cmd);
	if (!tmp)
		return (-1);
	free(g_term->str_cmd);
	g_term->str_cmd = my_modif_for_export(tmp);
	free(tmp);
	if (g_term->str_cmd == NULL)
		return (-1);
	cmd_tmp_env = my_gestion_var_env(g_term->str_cmd);
	if (!cmd_tmp_env)
	{
		free(g_term->str_cmd);
		my_free_tab(cmd_tmp_env);
		return (2);
	}
	tab_cmd = my_malloc_chaine(cmd_tmp_env);
	if (tab_cmd == NULL)
	{
		my_free_tab(cmd_tmp_env);
		my_free_double_tab((void **)tab_cmd, -1);
		return (-1);
	}
	my_rempli_tab_cmd(tab_cmd, cmd_tmp_env);
	my_free_tab((void *)cmd_tmp_env);
	g_term->cmd = my_init_struct_cmd(tab_cmd);
	if (!g_term->cmd)
		return (-1);
	if (!my_mouv_struct_for_red(&g_term->cmd))
	{
		my_free_liste_chene(g_term->cmd);
		return (-1);
	}
	return (1);
}
