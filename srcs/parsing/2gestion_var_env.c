/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_var_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:42:21 by mbonnet           #+#    #+#             */
/*   Updated: 2021/12/16 11:16:08 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_take_key_env(char *cmd_tmp, int x)
{
	int		len;
	char	*key_env;

	len = 0;
	if (!cmd_tmp[x++])
		return (NULL);
	while (cmd_tmp[x + len] && cmd_tmp[x + len] != '\''
		&& ft_whitespace(cmd_tmp[x + len]) != 1
		&& my_check_redirection(&cmd_tmp[x + len]) != 1
		&& cmd_tmp[x + len] != '\"' && cmd_tmp[x + len] != '$')
		len++;
	key_env = malloc(sizeof(char) * (len + 1));
	if (key_env == NULL)
		return (NULL);
	len = -1;
	while (++len > -1 && cmd_tmp[x + len] && cmd_tmp[x + len] != '\''
		&& ft_whitespace(cmd_tmp[x + len]) != 1
		&& my_check_redirection(&cmd_tmp[x + len]) != 1
		&& cmd_tmp[x + len] != '\"'
		&& cmd_tmp[x + len] != '$')
		key_env[len] = cmd_tmp[x + len];
	key_env[len] = '\0';
	return (key_env);
}

void	my_inclus_res_var_env_2(char **tmp, int x, char **res, char *str_env)
{
	int		index_res;
	int		index_env;
	int		index_tmp;

	index_res = 0;
	index_env = 0;
	index_tmp = 0;
	while ((*tmp)[index_tmp] && index_tmp < x)
		(*res)[index_res++] = (*tmp)[index_tmp++];
	(*res)[index_res++] = '\'';
	while (str_env[index_env])
		(*res)[index_res++] = str_env[index_env++];
	(*res)[index_res++] = '\'';
	index_tmp++;
	while ((*tmp)[index_tmp] && ft_whitespace((*tmp)[index_tmp]) != 1
		&& my_check_redirection(&((*tmp)[index_tmp])) != 1
		&& (*tmp)[index_tmp] != '\'' && (*tmp)[index_tmp] != '\"'
		&& (*tmp)[index_tmp] != '$')
		index_tmp++;
	while ((*tmp)[index_tmp])
		(*res)[index_res++] = (*tmp)[index_tmp++];
	(*res)[index_res] = '\0';
}

char	*my_inclus_res_var_env(char **tmp, char *key_env, int x)
{
	char	*str_env;
	char	*res;

	if (key_env == NULL)
		return (my_free_tab(*tmp));
	str_env = getenv(key_env);
	if (str_env == NULL)
	{
		free(key_env);
		free(*tmp);
		return (my_little_printf_char("ERROR: variable d env inconnue\n"));
	}
	res = malloc(sizeof(char) * ((ft_strlen(str_env) + 2)
				+ (ft_strlen(*tmp) - (ft_strlen(key_env) + 1)) + 1));
	free(key_env);
	if (res == NULL)
		return (my_free_tab(*tmp));
	my_inclus_res_var_env_2(tmp, x, &res, str_env);
	free(*tmp);
	return (res);
}

char	*my_gestion_var_env(char *cmd_tmp)
{
	int		x;
	char	*res;

	x = -1;
	res = ft_strdup(cmd_tmp);
	while (res[++x] != '\0')
	{
		if (res[x] == '\'')
		{
			x++;
			while (res[x] != '\'')
				if (!res[x++])
					return (my_free_tab(res));
		}
		else if (res[x] && res[x] == '$')
		{
			res = my_inclus_res_var_env(&res, my_take_key_env(res, x), x);
			if (res == NULL)
				return (NULL);
			while (res[x] && res[x] != '\'' && res[x] != '$')
				x++;
			x--;
		}
	}
	return (res);
}