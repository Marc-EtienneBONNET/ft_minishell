/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_preparatif_str_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:14:41 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 16:14:15 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_check_guillemet(void)
{
	int		x;
	char	c;
	int		double_g;
	int		simple_g;

	x = 0;
	double_g = 0;
	simple_g = 0;
	while (g_term.str_cmd[x])
	{
		c = g_term.str_cmd[x];
		if (c == '\"' && double_g == 0 && simple_g == 0)
			double_g = 1;
		else if (c == '\'' && double_g == 0 && simple_g == 0)
			simple_g = 1;
		else if (double_g == 1 && c == '\"')
			double_g = 0;
		else if (simple_g == 1 && c == '\'')
			simple_g = 0;
		x++;
	}
	if (simple_g == 1 || double_g == 1)
		return (-1);
	return (1);
}

char	*my_recup_key(char *cmd)
{
	int		x;
	char	*key;

	x = 0;
	key = NULL;
	while (cmd[x] == '_' || (cmd[x] >= '0' && cmd[x] <= '9')
		|| (cmd[x] >= 'a' && cmd[x] <= 'z') || (cmd[x] >= 'A' && cmd[x] <= 'Z')
		|| cmd[x] <= '?')
		x++;
	key = malloc(sizeof(char) * (x + 1));
	if (!key)
		return (NULL);
	x = 0;
	while (cmd[x] == '_' || (cmd[x] >= '0' && cmd[x] <= '9')
		|| (cmd[x] >= 'a' && cmd[x] <= 'z') || (cmd[x] >= 'A' && cmd[x] <= 'Z')
		|| cmd[x] <= '?')
	{
		key[x] = cmd[x];
		x++;
	}
	key[x] = '\0';
	return (key);
}

int	my_transforme_str_cmd_pour_var_env_2(int *x, char **new_cmd, char *var_env
		, char *key)
{
	int	y;

	y = -1;
	while (g_term.str_cmd[++y] && y < *x)
		(*new_cmd)[y] = g_term.str_cmd[y];
	while (*var_env)
	{
		(*new_cmd)[y++] = *var_env;
		var_env++;
	}
	*x += ft_strlen(key) + 1;
	while (g_term.str_cmd[*x])
		(*new_cmd)[y++] = g_term.str_cmd[(*x)++];
	(*new_cmd)[y] = '\0';
	my_free_tab(g_term.str_cmd);
	g_term.str_cmd = (*new_cmd);
	return (1);
}

int	my_transforme_str_cmd_pour_var_env(int *x, char *key)
{
	int		y;
	char	*var_env;
	char	*new_cmd;

	y = -1;
	var_env = NULL;
	if (ft_strncmp(key, "?", 3) == 0)
		var_env = ft_strdup(ft_itoa(g_term.dernier_ret));
	else
	{
		while (g_term.my_env[++y].key)
			if (ft_strncmp(key, g_term.my_env[y].key, ft_strlen(key)) == 0)
				var_env = g_term.my_env[y].var;
	}
	if (var_env == NULL)
		return (-1);
	new_cmd = malloc(sizeof(char) * ((ft_strlen(g_term.str_cmd)
					- (ft_strlen(key) + 1)) + ft_strlen(var_env) + 1));
	if (!new_cmd)
		return (-1);
	return (my_transforme_str_cmd_pour_var_env_2(x, &new_cmd, var_env, key));
}

int	my_check_var_env(void)
{
	int		x;
	int		double_g;
	char	*key;

	x = -1;
	double_g = 0;
	while (g_term.str_cmd[++x])
	{
		if (g_term.str_cmd[x] == '\"' && double_g == 0)
			double_g = 1;
		else if (double_g == 1 && g_term.str_cmd[x] == '\"')
			double_g = 0;
		else if (g_term.str_cmd[x] == '\'' && double_g == 0)
			while (g_term.str_cmd[++x] != '\'')
				double_g = 0;
		if (g_term.str_cmd[x] == '$')
		{
			key = my_recup_key(&(g_term.str_cmd[x + 1]));
			if (key == NULL
				|| my_transforme_str_cmd_pour_var_env(&x, key) == -1)
			{
				my_free_tab(key);
				return (-1);
			}
			my_free_tab(key);
		}
	}
	return (1);
}
