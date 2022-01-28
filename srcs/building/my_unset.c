/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:37:39 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/28 16:11:21 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	supp_var_2(char *argv, t_env **new, int j, int len)
{
	int		len_2;
	char	*tmp;

	len_2 = ft_strlen(g_term.my_env[len].key) - 1;
	if (g_term.my_env[len].key[len_2] == '=')
	{
		g_term.my_env[len].key[len_2] = '\0';
		tmp = ft_strdup(g_term.my_env[len].key);
		g_term.my_env[len].key[len_2] = '=';
	}
	else
		tmp = ft_strdup(g_term.my_env[len].key);
	if (ft_strncmp(tmp, argv, ft_strlen(tmp)) == 0)
	{
		free(tmp);
		free(g_term.my_env[len].key);
		if (g_term.my_env[len].var)
			free(g_term.my_env[len].var);
		return (1);
	}
	free(tmp);
	(*new)[j].key = g_term.my_env[len].key;
	(*new)[j].var = g_term.my_env[len].var;
	return (0);
}

void	supp_var(char *argv)
{
	int		len;
	t_env	*new;
	int		j;

	len = 0;
	while (g_term.my_env[len].key)
		len++;
	new = malloc(sizeof(t_env) * (len + 1));
	if (!new)
		return ;
	j = 0;
	len = -1;
	while (g_term.my_env[++len].key != NULL)
	{
		if (supp_var_2(argv, &new, j, len) == 1)
			continue ;
		j++;
	}
	new[j].key = NULL;
	new[j].var = NULL;
	free(g_term.my_env);
	g_term.my_env = new;
	return ;
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
