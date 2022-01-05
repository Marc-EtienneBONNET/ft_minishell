/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2rempli_tab_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:37:42 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/05 15:17:54 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_rempli_cmd(char **tab_cmd, char *cmd_tmp, int *i, int *y)
{
	int	x;
	int	c;
	int	red;

	x = 0;
	while (ft_whitespace(cmd_tmp[*i]) == 1)
		(*i)++;
	red = my_check_redirection(&(cmd_tmp[*i]));
	if (cmd_tmp[*i] == '\"' || cmd_tmp[*i] == '\'')
	{
		c = cmd_tmp[(*i)++];
		while (cmd_tmp[*i] != c && cmd_tmp[*i] != '\0')
			tab_cmd[*y][x++] = cmd_tmp[(*i)++];
		(*i)++;
	}
	else if (red > 0)
		while (red-- > 0)
			tab_cmd[*y][x++] = cmd_tmp[(*i)++];
	else
		while (ft_whitespace(cmd_tmp[(*i)]) == 0
			&& my_check_redirection(&(cmd_tmp[(*i)])) == -1
			&& cmd_tmp[(*i)] != '\"' && cmd_tmp[(*i)] != '\''
			&& cmd_tmp[(*i)] != '\0')
			tab_cmd[*y][x++] = cmd_tmp[(*i)++];
	tab_cmd[(*y)][x] = '\0';
}

void	my_rempli_tab_cmd(char **tab_cmd, char *cmd_tmp)
{
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (cmd_tmp[i] != '\0')
	{
		my_rempli_cmd(tab_cmd, cmd_tmp, &i, &y);
		y++;
	}
	tab_cmd[y] = NULL;
}
