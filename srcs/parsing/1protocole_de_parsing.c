/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1protocole_de_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 08:28:28 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/06 17:47:46 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	/*
char *my_traitement_path(t_cmd *cmd)
{
	(void)cmd;
	char *res;
	int	x;
	int	y;

	y = 0;
	x = 0;
	printf("coucou\n");
	res = (char *)malloc(sizeof(char) * (6));
	if (!res)
		return (NULL);
	res = "/bin/";
	return (res);
	printf("coucou\n");
	while (term->cmd->cmd && term->cmd->cmd[x])
		x++;
	x--;
	while (x >= 0 && term->cmd->cmd[x] != '/')
		x--;
	if (term->cmd->cmd[x] == '/')
	{
		free(term->cmd->path);
		term->cmd->path = malloc(sizeof(char) * (x + 2));
		if (!term->cmd->path)
			return (-1);
		term->cmd->path[x+1] = '\0';
		while (x >= 0)
		{
			term->cmd->path[x] = term->cmd->cmd[x];
			x--;
		}
	}
	//return (1);
}
	*/

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
	return (cmd);
}
