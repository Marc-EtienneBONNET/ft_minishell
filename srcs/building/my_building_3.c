/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_building_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:37:39 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/11 18:38:21 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	supp_var(char *argv)
{
	int	i;

	i = -1;
	while (term->my_env[++i].key)
	{
		if (ft_strncmp(term->my_env[i].key, argv, ft_strlen(argv)) == 0)
		{
			free(term->my_env[i].var);
			free(term->my_env[i].key);
			while (term->my_env[i].var)
			{
				term->my_env[i].var = term->my_env[i + 1].var;
				term->my_env[i].key = term->my_env[i + 1].key;
				i++;
			}
			break ;
		}
	}
}

int	mess_err(char *str)
{
	write(2, "minishell: unset: '", 19);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	check(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		mess_err(str);
	i++;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
			mess_err(str);
		i++;
	}
	return (0);
}

int	my_unset(char **argv)
{
	int	i;

	i = 0;
	if (!argv[1])
		return (0);
	while (argv[i])
	{
		if (check(argv[i]) == -1)
			return (-1);
		supp_var(argv[i]);
		i++;
	}
	return (0);
}
