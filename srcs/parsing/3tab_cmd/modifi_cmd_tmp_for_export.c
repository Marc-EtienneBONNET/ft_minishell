/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifi_cmd_tmp_for_export.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:35:42 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/14 18:38:17 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//export test=test test=test | salut non=non | export test=test

void	my_transforme_new_cmd_tmp(char **res, int index)
{
	char	*new;
	int		x;

	new = malloc(sizeof(char) * (ft_strlen(res) + 3));
	if (!new)
		return (-1);
	while (x < index)
		x++;
	while (ft_whitespace(res[x]) != 1 && my_check_redirection())
	
}

int	my_localise_egale(char *cmd_tmp)
{
	int		x;
	char	*res;

	x = 0;
	res = ft_strdup(cmd_tmp);
	while (cmd_tmp[x])
	{
		if (x == 0 || my_check_redirection(&(cmd_tmp[x])) > 0)
		{
			if (x != 0)
				x++;
			while (ft_whitespace(cmd_tmp[x]) == 1 && cmd_tmp[x])
				x++;
			if (ft_strncmp(&(cmd_tmp[x]), "export", 6) == 0)
			{
				while (cmd_tmp[x] && my_check_redirection(&(cmd_tmp[x])) < 0)
				{
					if (cmd_tmp[x] == '=')
						my_transforme_new_cmd_tmp(&res, x);
					x++;
				}
			}
		}
		x++;
	}
	return (1);
}

char	*my_modifi_for_export(char *cmd_tmp)
{
	char	*res;
	int		len;

	res = NULL;
	len = my_compte_rajoue(cmd_tmp);	
	return (res);
}
