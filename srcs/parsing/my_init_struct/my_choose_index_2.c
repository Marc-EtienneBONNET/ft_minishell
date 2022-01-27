/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_choose_index_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:15:46 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 16:19:18 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*recup_red(char *red)
{
	if (ft_strncmp(red, ">>", 2) == 0)
		return (ft_strdup(">>"));
	if (ft_strncmp(red, "<<", 2) == 0)
		return (ft_strdup("<<"));
	if (ft_strncmp(red, ">", 1) == 0)
		return (ft_strdup(">"));
	if (ft_strncmp(red, "<", 1) == 0)
		return (ft_strdup("<"));
	return (NULL);
}

int	my_ajoute_arg(char *str, int *x, char ***arg)
{
	char	*tmp_2;
	char	**tmp_3;

	tmp_2 = NULL;
	tmp_3 = NULL;
	tmp_2 = recup_element(str, x);
	tmp_3 = ft_strdoubledup(*arg);
	my_free_double_tab((void **)*arg, -1);
	*arg = ft_strdoublejoin(tmp_3, tmp_2);
	my_free_tab(tmp_2);
	return (1);
}

void	my_gomme_path(t_cmd *tmp)
{
	char	*tmp_2;
	int		x;

	x = ft_strlen(tmp->arg[0]);
	while (--x >= 0)
	{
		if (tmp->arg[0][x] == '/')
		{
			tmp_2 = ft_strdup(&(tmp->arg[0][x + 1]));
			my_free_tab(tmp->arg[0]);
			tmp->arg[0] = ft_strdup(tmp_2);
			my_free_tab(tmp_2);
			break ;
		}
	}
}

void	my_take_arg(char *str, t_cmd *tmp)
{
	int		x;
	int		gu;
	int		red;
	char	**arg;

	x = -1;
	gu = 0;
	red = 0;
	arg = NULL;
	while (str[++x])
	{
		my_check_guil(&gu, str[x]);
		red = my_check_redirection(&(str[x]));
		if (ft_whitespace(str[x]) == 1)
			continue ;
		else if (red > 1 && gu == 0)
			x = my_passe_fichier(x, red, str, &gu);
		else
			if (my_ajoute_arg(str, &x, &arg) == 1 && !str[x])
				break ;
	}
	tmp->arg = arg;
	my_gomme_path(tmp);
}

int	my_take_red(char *str, t_cmd *tmp)
{
	int	x;
	int	gu;

	x = -1;
	gu = 0;
	while (str[++x])
	{
		my_check_guil(&gu, str[x]);
		if (str[x] == '|' && gu == 0)
		{
			tmp->red = ft_strdup("|");
			return (1);
		}
		else if (str[x] == ';' && gu == 0)
		{
			tmp->red = ft_strdup(";");
			return (1);
		}
	}
	tmp->red = ft_strdup(";");
	return (1);
}
