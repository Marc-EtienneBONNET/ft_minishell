/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_rempli_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:19:51 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/25 12:40:52 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_check_guil(int	*gu, char c)
{
	if (c == '\'' && *gu == 0)
		*gu = 1;
	else if (c == '\"' && *gu == 0)
		*gu = 2;
	else if (c == '\"' && *gu == 2)
		*gu = 0;
	else if (c == '\'' && *gu == 1)
		*gu = 0;
}

int	my_take_nb_tab(void)
{
	int	x;
	int	len;
	int	gu;

	x = 0;
	len = 1;
	gu = 0;
	while (g_term.str_cmd[x])
	{
		my_check_guil(&gu, g_term.str_cmd[x]);
		if (my_check_redirection(&(g_term.str_cmd[x])) == 1
			&& gu == 0)
			len++;
		x++;
	}
	return (len);
}

int	my_strlen_cmd(char *str)
{
	int	len;
	int	gu;

	len = 1;
	gu = 0;
	while (*str)
	{
		my_check_guil(&gu, *str);
		if (my_check_redirection(str) == 1
			&& gu == 0)
			return (len);
		len++;
		str++;
	}
	return (len);
}

int	my_copie(char **tab_cmd, int y, int i, char *str)
{
	int	len;

	len = 0;
	if (i == 0)
	{
		len = my_strlen_cmd(str);
		tab_cmd[y] = malloc(sizeof(char) * (len + 1));
		tab_cmd[y][len] = '\0';
		if (!tab_cmd[y])
		{
			my_free_double_tab((void *)tab_cmd, -1);
			return (-1);
		}
	}
	tab_cmd[y][i] = *str;
	return (1);
}

int	my_rempli_tab_cmd(char **tab_cmd, char *str)
{
	int	i;
	int	y;
	int	gu;

	i = 0;
	y = 0;
	gu = 0;
	while (*str)
	{
		if (my_copie(tab_cmd, y, i, str) == -1)
			return (-1);
		my_check_guil(&gu, *str);
		i++;
		if (my_check_redirection(str) == 1 && gu == 0)
		{
			y++;
			i = 0;
		}
		str++;
	}
	if (i == 0)
		tab_cmd[y] = malloc(sizeof(char));
	tab_cmd[y][i] = '\0';
	tab_cmd[++y] = NULL;
	return (1);
}
