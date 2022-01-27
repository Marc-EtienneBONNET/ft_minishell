/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sup_tab_cmd_vide.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:13:32 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/26 08:21:42 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_compte(char **tab_cmd)
{
	int	x;
	int	y;
	int	len;

	x = 0;
	len = 0;
	while (tab_cmd[x])
	{
		if (!tab_cmd[x][0])
		{
			len++;
			x++;
			continue ;
		}
		y = 0;
		while (ft_whitespace(tab_cmd[x][y]) == 1)
			y++;
		if (!tab_cmd[x][y])
			len++;
		x++;
	}
	return (x - len);
}

char	*my_copi_tab_cmd(char *str)
{
	char	*tmp;

	while (ft_whitespace(*str) == 1)
		str++;
	if (!(*str))
		return (NULL);
	tmp = ft_strdup(str);
	return (tmp);
}

char	**my_sup_str_vide(char **tab_cmd)
{
	int		len;
	char	**new_tab;
	int		x;
	int		y;

	x = 0;
	y = 0;
	len = ft_compte(tab_cmd);
	if (len == 0)
		return (NULL);
	new_tab = malloc(sizeof(char *) * (len + 1));
	if (!new_tab)
		return (NULL);
	while (tab_cmd[x])
	{
		if (tab_cmd[x][0])
		{
			new_tab[y] = my_copi_tab_cmd(tab_cmd[x]);
			if (new_tab[y] != NULL)
				y++;
		}
		x++;
	}
	new_tab[y] = NULL;
	return (new_tab);
}
