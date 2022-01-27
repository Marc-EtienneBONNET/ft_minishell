/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:16:53 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 15:26:07 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*my_copy_t_env(void)
{
	t_env	*env;
	int		x;

	x = 0;
	while (g_term.my_env[x].key)
		x++;
	env = malloc(sizeof(t_env) * (x + 1));
	if (!env)
		return (NULL);
	x = 0;
	while (g_term.my_env[x].key)
	{
		env[x].key = g_term.my_env[x].key;
		env[x].var = g_term.my_env[x].var;
		x++;
	}
	env[x].key = NULL;
	return (env);
}

int	my_sort(t_env **tmp)
{
	int		i;
	int		j;
	t_env	tmp_2;

	i = -1;
	while ((*tmp)[++i].key)
	{
		j = i;
		while ((*tmp)[++j].key)
		{
			if (ft_strncmp((*tmp)[i].key, (*tmp)[j].key,
				ft_strlen((*tmp)[j].key)) > 0)
			{
				tmp_2 = (*tmp)[i];
				(*tmp)[i] = (*tmp)[j];
				(*tmp)[j] = tmp_2;
			}
		}
	}
	return (0);
}

int	my_print_export(void)
{
	int		i;
	t_env	*tmp;

	i = -1;
	tmp = my_copy_t_env();
	if (!tmp)
		return (-1);
	my_sort(&tmp);
	i = -1;
	while (tmp[++i].key)
	{
		printf("declare -x %s", tmp[i].key);
		if (tmp[i].var)
			printf("\"%s\"", tmp[i].var);
		else if (tmp[i].key[ft_strlen(tmp[i].key) - 1] == '=')
			printf("\"\"");
		printf("\n");
	}
	free(tmp);
	return (0);
}
