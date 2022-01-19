/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1protocole_de_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 08:28:28 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/19 11:16:38 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_gestion_for_export(void)
{
	char		*tmp;

	tmp = ft_strdup(g_term.str_cmd);
	if (!tmp)
		return (-1);
	free(g_term.str_cmd);
	g_term.str_cmd = my_modif_for_export(tmp);
	free(tmp);
	if (g_term.str_cmd == NULL)
		return (-1);
	return (1);
}

int	my_lancement_struct(char **cmd_tmp_env)
{
	char		**tab_cmd;

	tab_cmd = my_malloc_chaine(*cmd_tmp_env);
	if (tab_cmd == NULL)
	{
		my_free_tab(*cmd_tmp_env);
		my_free_double_tab((void **)tab_cmd, -1);
		return (-1);
	}
	my_rempli_tab_cmd(tab_cmd, *cmd_tmp_env);
	my_free_tab((void *)*cmd_tmp_env);
	g_term.cmd = my_init_struct_cmd(tab_cmd);
	//printf("salut\n");
	return (1);
}

char	*my_gestion_var_env(char *cmd_tmp)
{
	int		x;
	char	*res;

	x = -1;
	res = ft_strdup(cmd_tmp);
	if (!res)
		return (NULL);
	while (res[++x] != '\0')
	{
		if (my_gestion_var_env_2(&res, &x) == NULL)
			return (NULL);
	}
	return (res);
}

int	my_parsing(void)
{
	char		*cmd_tmp_env;
	t_cmd		*cmd;

	cmd = NULL;
	if (my_gestion_for_export() == -1)
		return (-1);
	cmd_tmp_env = my_gestion_var_env(g_term.str_cmd);
	if (!cmd_tmp_env)
	{
		free(g_term.str_cmd);
		my_free_tab(cmd_tmp_env);
		return (2);
	}
	if (my_lancement_struct(&cmd_tmp_env) == -1 || !g_term.cmd)
	{
		//printf("coucou\n");
		return (-1);
		
	}
	//my_print_struct(g_term.cmd);
	if (!my_mouv_struct_for_red(&g_term.cmd))
	{
		my_free_liste_chene(g_term.cmd);
		return (-1);
	}
	return (1);
}
