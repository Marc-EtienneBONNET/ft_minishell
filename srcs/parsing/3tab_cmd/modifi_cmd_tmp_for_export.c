/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifi_cmd_tmp_for_export.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:35:42 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/21 13:45:50 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	my_install_guillemet(char **new, char *cmd_tmp, int *i, int *x)
{
	int	verif;

	(*x)++;
	while (*i < (*x)++ &&cmd_tmp[*i])
	{
		(*new)[*i] = cmd_tmp[*i];
		(*i)++;
	}
	(*new)[*i] = '\"';
	verif = *i;
	while (cmd_tmp[*i] && my_check_redirection(&(cmd_tmp[*i])) < 0)
	{
		if (cmd_tmp[*i] == '\"')
			(*new)[(*i) + 1] = (char)134;
		else
			(*new)[(*i) + 1] = cmd_tmp[*i];
		(*i)++;
	}
	(*new)[(*i) + 1] = '\"';
	if (verif + 1 == (*i) + 1)
	{
		free(*new);
		*new = NULL;
	}
	*x = (*i) + 1;
	return (verif);
}

char	*my_transforme_new_cmd_tmp(char *cmd_tmp, int *x)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(cmd_tmp) + 3));
	if (!new)
	{
		free(new);
		return (NULL);
	}
	my_install_guillemet(&new, cmd_tmp, &i, x);
	if (!new)
	{
		new = ft_strdup(cmd_tmp);
		return (new);
	}
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
		while (ft_whitespace((*res)[(*x)]) == 1)
			(*x)++;
		if (!(*res)[(*x)])
			return (-2);
		else
			(*x)--;
		tmp = ft_strdup((*res));
		if (!tmp)
			return (-1);
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
	int		stopper;

	x = 0;
	res = ft_strdup(cmd_tmp);
	if (!res)
		return (NULL);
	x = -1;
	while (res && res[++x])
	{
		my_passe_guillemet(&x, res);
		if (x == 0 || my_check_redirection(&(res[x])) > 0)
		{
			stopper = my_modif_for_export_2(&res, &x);
			if (stopper == -1)
			{
				free(res);
				return (NULL);
			}
			if (stopper == -2)
				break ;
		}
	}
	return (res);
}
*/

int	my_install_guillemet(char **res, int *x)
{
	int		y;
	char	*tmp;

	y = -1;
	tmp = malloc(sizeof(char) * (ft_strlen((*res)) + 3));
	if (!tmp)
		return (-1);
	while (++y < *x)
		tmp[y] = (*res)[y];
	tmp[y] = '\"';
	while ((*res)[y] && my_check_redirection(&((*res)[y])) != 1)
	{
		tmp[y + 1] = (*res)[y];
		if ((*res)[y] == '\"')
			tmp[y + 1] = (char)134;
		y++;
	}
	tmp[y + 1] = '\"';
	*x = y + 1;
	while ((*res)[y])
	{
		tmp[y + 2] = (*res)[y];
		y++;
	}
	tmp[y + 2] = '\0';
	free((*res));
	*res = tmp;
	return (1);
}

char	*my_modif_for_export(char *cmd_tmp)
{
	char	*res;
	int		x;

	res = NULL;
	res = ft_strdup(cmd_tmp);
	x = 0;
	while (res[x])
	{
		if (res[x] == '\"')
		{
			while (res[++x] != '\"');
			x++;
		}
		if (res[x] == '\'')
		{
			while (res[++x] != '\'');
			x++;
		}
		if (my_check_redirection(&(res[x])) == 1 || x == 0)
		{
			while (ft_whitespace(res[x]) == 1 || my_check_redirection(&(res[x])) == 1)
				x++;
			if (ft_strncmp(&(res[x]), "export", ft_strlen("export")) == 0)
			{
				while (ft_whitespace(res[x]) != 1 && res[x]
					&& my_check_redirection(&(res[x])) != 1)
					x++;
				while (ft_whitespace(res[x]) == 1)
					x++;
				if (my_check_redirection(&(res[x])) == 1 || !res[x])
				{
					return (res);
				}
				else
				{
					my_install_guillemet(&res, &x);
				}
			}
		}
		x++;
	}
	printf("res : (%s)\n", res);
	return (res);
}
