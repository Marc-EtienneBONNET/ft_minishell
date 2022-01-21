/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifi_cmd_tmp_for_export.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:35:42 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/21 15:32:46 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((*res)[y++] == '\"')
			tmp[y] = (char)134;
	}
	tmp[y + 1] = '\"';
	*x = y + 1;
	y--;
	while ((*res)[++y])
		tmp[y + 2] = (*res)[y];
	tmp[y + 2] = '\0';
	free((*res));
	*res = tmp;
	return (1);
}

void	my_passe_guillemet(char *res, int *x)
{
	char	c;

	if (res[*x] == '\"')
	{
		while (res[++(*x)] != '\"')
			c = 'a';
		(*x)++;
	}
	if (res[(*x)] == '\'')
	{
		while (res[++(*x)] != '\'')
			c = 'a';
		(*x)++;
	}
}

char	*my_modif_for_export(char *cmd_tmp)
{
	char	*res;
	int		x;

	x = -1;
	res = ft_strdup(cmd_tmp);
	while (res[++x])
	{
		my_passe_guillemet(res, &x);
		if (my_check_redirection(&(res[x])) != 1 && x != 0)
			continue ;
		while (ft_whitespace(res[x]) == 1
			|| my_check_redirection(&(res[x])) == 1)
			x++;
		if (ft_strncmp(&(res[x]), "export", ft_strlen("export")) != 0)
			continue ;
		while (ft_whitespace(res[x]) != 1 && res[x]
			&& my_check_redirection(&(res[x])) != 1)
			x++;
		while (ft_whitespace(res[x]) == 1)
			x++;
		if (my_check_redirection(&(res[x])) == 1 || !res[x])
			return (res);
		my_install_guillemet(&res, &x);
	}
	return (res);
}

void	my_avance_whitespace(char *str, int *i)
{
	while (ft_whitespace(str[*i]) == 1 && str[*i])
		(*i)++;
}
