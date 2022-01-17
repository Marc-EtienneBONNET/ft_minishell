/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:16:53 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/17 18:06:53 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*my_copy_t_env(void)
{
	t_env	*env;
	int		x;

	x = 0;
	while (g_term->my_env[x].key)
		x++;
	env = malloc(sizeof(t_env) * (x + 1));
	if (!env)
		return (NULL);
	x = 0;
	while (g_term->my_env[x].key)
	{
		env[x].key = g_term->my_env[x].key;
		env[x].var = g_term->my_env[x].var;
		x++;
	}
	env[x].key = NULL;
	return (env);
}

int	my_print_export(void)
{
	int		i;
	int		j;
	t_env	tmp_2;
	t_env	*tmp;

	i = -1;
	tmp = my_copy_t_env();
	if (!tmp)
		return (-1);
	while (tmp[++i].key)
	{
		j = i;
		while (tmp[++j].key)
		{
			if (ft_strcmp(tmp[i].key, tmp[j].key) > 0)
			{
				tmp_2 = tmp[i];
				tmp[i] = tmp[j];
				tmp[j] = tmp_2;
			}
		}
	}
	i = -1;
	while (tmp[++i].key)
		printf("declare -x %s=\"%s\"\n", tmp[i].key, tmp[i].var);
	free(tmp);
	return (0);
}
