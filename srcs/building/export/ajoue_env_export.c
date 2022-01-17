/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ajoue_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 09:48:53 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 18:13:28 by mbonnet          ###   ########.fr       */
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
	arg++;
	if (!(*arg))
		return (NULL);
	new = ft_strdup(arg);
	if (!new)
		return (NULL);
	return (new);
}

int	ft_strcmp(char *str1, char *str2)
{
	unsigned int	x;

	x = 0;
	while ((str1[x]) || (str2[x]))
	{
		if ((unsigned char)str1[x] < (unsigned char)str2[x])
			return (-1);
		else if ((unsigned char)str1[x] > (unsigned char)str2[x])
			return (1);
		x++;
	}
	return (0);
}

int	my_check_doublon_and_cara_key(char *key,	int tele)
{
	int	x;

	x = 0;
	if (tele == 1)
	{
		while (g_term.my_env[x].key)
		{
			if (ft_strcmp(g_term.my_env[x].key, key) == 0)
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

int	my_ajoue_arg(char **arg)
{
	int		y;
	char	*key;
	char	*var;
	int		index;

	y = 0;
	while (arg[y])
	{
		key = my_recup_str(arg[y], 0);
		if (!key || my_check_doublon_and_cara_key(key, 0) == -1)
			return (-1);
		var = my_recup_str(arg[y], 1);
		index = my_check_doublon_and_cara_key(key, 1);
		if (index >= 0)
		{
			free(g_term.my_env[index].var);
			g_term.my_env[index].var = var;
		}
		else
			if (my_ajoue_new_env(&key, &var) == -1)
			{
				free(var);
				free(key);
				return (-1);
			}
		free(arg[y]);
		y++;
	}
	free(arg);
	return (1);
}