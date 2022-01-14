/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_building_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:35:50 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/14 16:53:19 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	aj_env_to_exp(char *key, char *var)
{
	int		i;
	char	**tmp;
	char	*tmp_2;

	i = 0;
	while (term->exp[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (1);
	i = -1;
	while (term->exp[++i])
		tmp[i] = ft_strdup(term->exp[i]);
	tmp[i] = ft_strjoin(key, "=\"");
	tmp_2 = ft_strdup(tmp[i]);
	free(tmp[i]);
	tmp[i] = ft_strjoin(tmp_2, var);
	free(tmp_2);
	tmp_2 = ft_strdup(tmp[i]);
	free(tmp[i]);
	tmp[i] = ft_strjoin(tmp_2, "\"");
	free(tmp_2);
	i++;
	tmp[i] = NULL;
	i = -1;
	while (term->exp[++i])
		free(term->exp[i]);
	free(term->exp);
	term->exp = tmp;
	return (0);
}