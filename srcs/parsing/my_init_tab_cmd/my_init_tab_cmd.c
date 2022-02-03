/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init_tab_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:42:30 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/03 11:47:02 by mbonnet          ###   ########.fr       */
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
		return (-1);
	return (1);
}

char	*my_init_tab_cmd_2(char **str, int *gu)
{
	char	*res;

	res = NULL;
	while (1)
	{
		my_check_gu(gu, *(*str));
		res = ft_strmicrojoin(&res, *(*str));
		if ((*gu == 0 && ((*(*str) == ';')
					|| (*(*str) == '&' && *((*str) - 1) == '&')
					|| (*(*str) == '|' && *((*str) - 1) == '|')
					|| (*(*str) == '|' && *((*str) + 1) != '|')))
			|| *(*str) == '\0')
			return (res);
		(*str)++;
	}
	return (res);
}

char	**my_init_tab_cmd(char *str)
{
	char	**tab_cmd;
	int		x;
	char	*tmp;
	char	**tmp_2;
	int		gu;

	gu = 0;
	x = -1;
	tab_cmd = NULL;
	while (*str)
	{
		tmp = my_init_tab_cmd_2(&str, &gu);
		tmp_2 = ft_strdoubledup(tab_cmd);
		tab_cmd = my_free_double_tab((void **)tab_cmd, -1);
		tab_cmd = ft_strdoublejoin(tmp_2, tmp);
		tmp_2 = my_free_double_tab((void **)tmp_2, -1);
		tmp = my_free_tab((void **)&tmp);
		if (!(*str))
			break ;
		str++;
	}
	while (tab_cmd[++x])
		if (my_init_tab_cmd_3(&(tab_cmd[x])) == -1 && tab_cmd[x + 1] != NULL)
			return (my_free_double_tab((void **)tab_cmd, -1));
	return (tab_cmd);
}
