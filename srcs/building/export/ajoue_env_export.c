/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ajoue_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 09:48:53 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/24 09:54:40 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_recup_str(char *arg, int tele)
{
	int		x;
	char	*new;

	x = 0;
	if (tele == 0)
	{
		while (arg[x] && arg[x] != '=')
			x++;
		new = malloc(sizeof(char) * (x + 1));
		if (!new)
			return (NULL);
		x = -1;
		while (arg[++x] && arg[x] != '=')
			new[x] = arg[x];
		new[x] = '\0';
		return (new);
	}
	while (*arg && *arg != '=')
		arg++;
	if (!(*arg) || !(*(++arg)))
		return (NULL);
	new = ft_strdup(arg);
	if (!new)
		return (NULL);
	return (new);
}

int	my_check_doublon_and_cara_key(char *key,	int tele)
{
	int	x;

	x = 0;
	if (tele == 1)
	{
		while (g_term.my_env[x].key)
		{
			if (ft_strncmp(g_term.my_env[x].key, key, 1000) == 0)
				return (x);
			x++;
		}
		return (-1);
	}
	if (!ft_isalpha(key[x]) && key[x] != '_')
		return (mess_err2(key));
	x++;
	while (key[x])
	{
		if (!ft_isalpha(key[x]) && key[x] != '_'
			&& !ft_isdigit(key[x]) && key[x] != '=')
			return (mess_err2(key));
		x++;
	}
	return (0);
}

int	my_ajoue_new_env(char **key, char **var)
{
	int		len;
	t_env	*new;

	len = 0;
	while (g_term.my_env[len].key)
		len++;
	new = malloc(sizeof(t_env) * (len + 2));
	if (!new)
		return (-1);
	len = 0;
	while (g_term.my_env[len].key)
	{
		new[len].key = g_term.my_env[len].key;
		new[len].var = g_term.my_env[len].var;
		len++;
	}
	new[len].key = *key;
	new[len].var = *var;
	len++;
	new[len].key = NULL;
	new[len].var = NULL;
	free(g_term.my_env);
	g_term.my_env = new;
	return (1);
}

int	my_ajoue_arg_ex(char **key, char **var)
{
	if (my_check_doublon_and_cara_key(*key, 1) >= 0)
	{
		free(g_term.my_env[my_check_doublon_and_cara_key(*key, 1)].var);
		g_term.my_env[my_check_doublon_and_cara_key(*key, 1)].var = *var;
		free(*key);
	}
	else if (my_ajoue_new_env(key, var) == -1)
	{
		free(*var);
		free(*key);
		return (-1);
	}
	return (1);
}

int	my_ajoue_arg(char **arg)
{
	int		y;
	char	*key;
	char	*var;

	y = -1;
	while (arg[++y])
	{
		key = my_recup_str(arg[y], 0);
		if (!key || my_check_doublon_and_cara_key(key, 0) == -1)
			return (-1);
		var = my_recup_str(arg[y], 1);
		if (my_ajoue_arg_ex(&key, &var) == -1)
			return (-1);
	}
	my_free_double_tab((void **)arg, -1);
	return (1);
}
