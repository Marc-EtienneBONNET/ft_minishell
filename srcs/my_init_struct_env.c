/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_init_struct_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 08:32:43 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/02 12:28:18 by mbonnet          ###   ########.fr       */
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
	res[x] = env[x];
	res[++x] = '\0';
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

int	my_init_struct_env(void)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (g_term.envp[y])
		y++;
	g_term.my_env = malloc(sizeof(t_env) * (y + 1));
	if (!g_term.my_env)
		return (-1);
	while (x < y)
	{
		g_term.my_env[x].key = my_env_key(g_term.envp[x]);
		g_term.my_env[x].var = my_env_var(g_term.envp[x]);
		if (!g_term.my_env[x].var || !g_term.my_env[x].key)
			return (-1);
		x++;
	}
	g_term.my_env[x].key = NULL;
	g_term.my_env[x].var = NULL;
	return (1);
}
