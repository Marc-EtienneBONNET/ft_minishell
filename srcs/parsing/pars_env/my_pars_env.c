/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pars_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:52:07 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 12:37:40 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_env_key(char *env)
{
	int		x;
	char	*res;

	x = 0;
	while (env[x] && env[x] != '=')
		x++;
	res = malloc(sizeof(char) * (x + 1));
	if (!res)
		return (NULL);
	x = 0;
	while (env[x] && env[x] != '=')
	{
		res[x] = env[x];
		x++;
	}
	res[x] = '\0';
	return (res);
}

char	*my_env_var(char *env)
{
	int		x;
	int		len;
	char	*res;

	x = 0;
	len = 0;
	while (env[x] && env[x] != '=')
		x++;
	x++;
	while (env[x + len])
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	len = 0;
	while (env[x + len])
	{
		res[len] = env[x + len];
		len++;
	}
	res[len] = '\0';
	return (res);
}

int	my_init_struct_env()
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (term->envp[y])
		y++;
	term->my_env = malloc(sizeof(t_env) * (y + 1));
	if (!term->my_env)
		return (-1);
	while (x < y)
	{
		term->my_env[x].key = my_env_key(term->envp[x]);
		term->my_env[x].var = my_env_var(term->envp[x]);
		if (!term->my_env[x].var || !term->my_env[x].key)
			return (-1);
		x++;
	}
	term->my_env[x].key = NULL;
	term->my_env[x].var = NULL;
	return (1);
}
