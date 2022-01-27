/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ajoue_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 09:48:53 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 15:29:23 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp_2(char *str1, char *str2, unsigned int size)
{
	unsigned int	x;

	x = 0;
	while (x < size && ((str1[x]) || (str2[x])))
	{
		if (str1[x] == '=' && (str2[x] == '=' || !str2[x]))
			return (0);
		if (str2[x] == '=' && (str1[x] == '=' || !str1[x]))
			return (0);
		else if ((unsigned char)str1[x] < (unsigned char)str2[x])
			return (-1);
		else if ((unsigned char)str1[x] > (unsigned char)str2[x])
			return (1);
		x++;
	}
	return (0);
}

int	my_check_doublon_and_cara_key(char *key, int tele)
{
	int		x;

	x = 0;
	if (tele == 1)
	{
		while (g_term.my_env[x].key)
		{
			if (ft_strncmp_2(g_term.my_env[x].key, key, 1000) == 0)
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
	int	check;

	check = my_check_doublon_and_cara_key(*key, 1);
	if (check >= 0)
	{
		if ((*key)[ft_strlen(*key) - 1] != '=')
			return (1);
		free(g_term.my_env[check].var);
		g_term.my_env[check].key = *key;
		g_term.my_env[check].var = *var;
	}
	if (my_check_doublon_and_cara_key(*key, 1) == -1)
	{
		if (my_ajoue_new_env(key, var) == -1)
		{
			free(*var);
			free(*key);
			return (-1);
		}
	}
	return (1);
}

int	my_ajoue_arg(char **arg)
{
	int		y;
	char	*key;
	char	*var;
	int		x;

	y = -1;
	x = -1;
	while (arg[++y])
	{
		key = my_recup_str(arg[y], 0);
		if (!key || my_check_doublon_and_cara_key(key, 0) == -1)
			return (-1);
		var = my_recup_str(arg[y], 1);
		if (my_ajoue_arg_ex(&key, &var) == -1)
			return (-1);
	}
	return (1);
}
