/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 09:22:31 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/31 20:38:55 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_check_gu(int *gu, char c)
{
	int	x;

	x = *gu;
	if (*gu == 0 && c == '\'')
		*gu = 1;
	else if (*gu == 0 && c == '\"')
		*gu = 2;
	else if (*gu == 1 && c == '\'')
		*gu = 0;
	else if (*gu == 2 && c == '\"')
		*gu = 0;
	if (x != *gu)
		return (-1);
	return (1);
}

int	my_check_red(int gu, char c)
{
	if (c == '>' && gu == 0)
		return (-1);
	else if (c == '<' && gu == 0)
		return (-2);
	return (1);
}

int	my_sup_char(char **str, int x)
{
	char	*tmp;
	char	*tmp_2;
	char	c;

	c = (*str)[x];
	(*str)[x] = '\0';
	tmp = ft_strdup((*str));
	(*str)[x] = c;
	tmp_2 = ft_strjoin(tmp, &((*str)[x + 1]));
	*str = my_free_tab((void **)str);
	*str = tmp_2;
	return (1);
}
