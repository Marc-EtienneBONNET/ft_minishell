/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifi_cmd_tmp_for_export.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:35:42 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 11:50:58 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//export test=test test=test ; echo non=non ; export test=test

void	my_install_guillemet(char **new, char *cmd_tmp, int *i, int *x)
{
	(*x)++;
	while (cmd_tmp[*i] && *i < *x)
	{
		(*new)[*i] = cmd_tmp[*i];
		(*i)++;
	}
	(*new)[*i] = '\"';
	while (cmd_tmp[*i] && my_check_redirection(&(cmd_tmp[*i])) < 0)
	{
		if (cmd_tmp[*i] == '\"')
			(*new)[(*i) + 1] = (char)134;
		else
			(*new)[(*i) + 1] = cmd_tmp[*i];
		(*i)++;
	}
	(*new)[(*i) + 1] = '\"';
	*x = (*i) + 1;
}

char	*my_transforme_new_cmd_tmp(char *cmd_tmp, int *x)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(cmd_tmp) + 3));
	if (!new)
		return (NULL);
	my_install_guillemet(&new, cmd_tmp, &i, x);
	while (cmd_tmp[i])
	{
		new[i + 2] = cmd_tmp[i];
		i++;
	}
	new[i + 2] = '\0';
	return (new);
}

void	my_passe_guillemet(int *x, char *res)
{
	char	c;

	c = res[*x];
	if (c == '\'' || c == '\"')
	{
		while (res[*x] && res[*x] != c)
			(*x)++;
		(*x)++;
	}
}

int	my_modif_for_export_2(char **res, int *x)
{
	char	*tmp;

	while ((ft_whitespace((*res)[*x]) == 1
		|| my_check_redirection(&((*res)[*x])) > 0) && (*res)[*x])
		(*x)++;
	if (ft_strncmp(&((*res)[(*x)]), "export", 6) == 0)
	{
		while ((*res)[(*x)] && ft_whitespace((*res)[(*x)]) != 1)
			(*x)++;
		tmp = ft_strdup((*res));
		free(*res);
		(*res) = my_transforme_new_cmd_tmp(tmp, x);
		free(tmp);
		if (!(*res))
			return (-1);
	}
	return (1);
}

char	*my_modif_for_export(char *cmd_tmp)
{
	int		x;
	char	*res;

	x = -1;
	res = ft_strdup(cmd_tmp);
	while (res[++x])
	{
		my_passe_guillemet(&x, res);
		if (x == 0 || my_check_redirection(&(res[x])) > 0)
			if (my_modif_for_export_2(&res, &x) == -1)
				return (NULL);
	}
	return (res);
}
