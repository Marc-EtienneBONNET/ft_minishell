/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init_tab_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:42:30 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/01 10:11:48 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_init_tab_cmd_3(char **tmp)
{
	int		w;

	w = 0;
	while ((*tmp)[w])
	{
		if (ft_whitespace((*tmp)[w]) == 0)
			break ;
		w++;
	}
	if (!(*tmp)[w] || (*tmp)[w] == '|' || (*tmp)[w] == ';'
		|| ((*tmp)[w] == '&' && (*tmp)[w + 1] == '&')
		|| ((*tmp)[w] == '|' && (*tmp)[w + 1] == '|'))
	{
		tmp = my_free_tab((void **)tmp);
		return (-1);
	}
	return (1);
}

char	**my_init_tab_cmd_2(char **tab_cmd, char *str, int *x, char **tmp)
{
	char	**tmp_2;
	int		gu;
	int		y;

	y = -1;
	gu = 0;
	*tmp = ft_strmicrojoin(tmp, str[*x]);
	while ((*tmp) && (*tmp)[++y])
	{
		my_check_gu(&gu, (*tmp)[y]);
		if (!str[(*x) + 1] || (gu == 0 && ((*tmp)[y] == '|'
				|| (*tmp)[y] == ';'
			|| ((*tmp)[y] == '&' && (*tmp)[y + 1] == '&')
				|| ((*tmp)[y] == '|' && (*tmp)[y + 1] == '|'))))
		{
			tmp_2 = ft_strdoubledup(tab_cmd);
			tab_cmd = my_free_double_tab((void **)tab_cmd, -1);
			tab_cmd = ft_strdoublejoin(tmp_2, *tmp);
			tmp_2 = my_free_double_tab((void **)tmp_2, -1);
			tmp = my_free_tab((void **)tmp);
			break ;
		}
	}
	return (tab_cmd);
}

char	**my_init_tab_cmd(char *str)
{
	char	**tab_cmd;
	int		x;
	char	*tmp;

	x = 0;
	tmp = NULL;
	tab_cmd = NULL;
	while (str[x])
	{
		tab_cmd = my_init_tab_cmd_2(tab_cmd, str, &x, &tmp);
		x++;
	}
	x = 0;
	while (tab_cmd[x])
	{
		if (my_init_tab_cmd_3(&(tab_cmd[x])) == -1 && tab_cmd[x + 1] != NULL)
			return (my_free_double_tab((void **)tab_cmd, -1));
		x++;
	}
	return (tab_cmd);
}
