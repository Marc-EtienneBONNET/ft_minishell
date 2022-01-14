/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_building_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:28:56 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/14 16:48:26 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_var(char *key, char *var)
{
	int	i;

	i = 0;
	while (term->my_env[i].key)
	{
		if (ft_strncmp(term->my_env[i].key, key, ft_strlen(key)) == 0)
		{
			free(term->my_env[i].var);
			term->my_env[i].var = ft_strdup(var);
		}
		i++;
	}
	return (0);
}

int	check_dbl(char *key)
{
	int	i;

	i = 0;
	while (term->my_env[i].key)
	{
		if (ft_strncmp(term->my_env[i].key,
				key, ft_strlen(term->my_env[i].key)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check2(char *argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	mess_err2(char *str)
{
	write(2, "minishell: export: '", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	check_arg(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (mess_err2(str));
	i++;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_'
			&& !ft_isdigit(str[i]) && str[i] != '=')
			return (mess_err2(str));
		i++;
	}
	return (0);
}
