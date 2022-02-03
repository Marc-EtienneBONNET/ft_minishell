/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gestion_gu_and_var_env_utile.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:53:40 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/03 11:49:52 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_recup_key(char *str, int *x)
{
	char	*res;

	res = NULL;
	(*x)++;
	while (str[*x] == '_'
		|| (str[*x] >= 'a' && str[*x] <= 'z')
		|| (str[*x] >= 'A' && str[*x] <= 'Z')
		|| (str[*x] >= '0' && str[*x] <= '9')
		|| str[*x] >= '?')
	{
		res = ft_strmicrojoin(&res, str[*x]);
		(*x)++;
	}
	res = ft_strmicrojoin(&res, '=');
	return (res);
}

char	*my_recup_var_env(char *str, int x)
{
	char	*key;
	char	*res;
	int		y;

	y = 0;
	key = my_recup_key(str, &x);
	if (key[0] == '?' && key[1] == '=' && key[2] == '\0')
	{
		return (ft_itoa(g_term.dernier_ret));
	}
	while (g_term.my_env && g_term.my_env[y].key)
	{
		if (ft_strncmp(g_term.my_env[y].key, key
				, ft_strlen(g_term.my_env[y].key)) == 0)
		{
			res = ft_strdup(g_term.my_env[y].var);
			key = my_free_tab((void **)&key);
			return (res);
		}
		y++;
	}
	key = my_free_tab((void **)&key);
	return (NULL);
}

int	my_change_cmd(char **str, char *var_env, int x)
{
	char	*tmp;
	char	*tmp_2;

	(*str)[x] = '\0';
	tmp = ft_strdup(*str);
	(*str)[x] = '$';
	if (var_env)
		tmp_2 = ft_strjoin(tmp, var_env);
	else
		tmp_2 = ft_strdup(tmp);
	tmp = my_free_tab((void **)&tmp);
	while ((*str)[x] && ((*str)[x] == '_' || (*str)[x] == '$'
		|| ((*str)[x] >= 'a' && (*str)[x] <= 'z')
		|| ((*str)[x] >= 'A' && (*str)[x] <= 'Z')
		|| ((*str)[x] >= '0' && (*str)[x] <= '9')
		|| (*str)[x] == '?'))
		x++;
	if ((*str)[x])
		tmp = ft_strjoin(tmp_2, &((*str)[x]));
	else
		tmp = ft_strdup(tmp_2);
	tmp_2 = my_free_tab((void **)&tmp_2);
	*str = my_free_tab((void **)str);
	*str = tmp;
	return (1);
}

int	my_check_var_env(char **str)
{
	int		x;
	int		gu;
	char	*var_env;

	gu = 0;
	x = 0;
	var_env = NULL;
	while ((*str)[x])
	{
		my_check_gu(&gu, (*str)[x]);
		if ((gu == 0 || gu == 2) && (*str)[x] == '$')
		{
			var_env = my_recup_var_env(*str, x);
			my_change_cmd(str, var_env, x);
			var_env = my_free_tab((void **)&var_env);
			if (!(*str)[0])
			{
				(*str) = my_free_tab((void **)str);
				return (-1);
			}
		}
		x++;
	}
	return (1);
}

int	netoyage_guillemet(char **str)
{
	int	x;
	int	gu;

	x = -1;
	gu = 0;
	if (!*str)
		return (1);
	while ((*str)[++x])
	{
		my_check_gu(&gu, (*str)[x]);
		if (gu == 2 && (*str)[x] == '\'')
			continue ;
		else if (gu == 1 && (*str)[x] == '\"')
			continue ;
		else if (((*str)[x] == '\"' || (*str)[x] == '\''))
		{
			my_sup_char(str, x);
			x--;
		}
	}
	return (1);
}
