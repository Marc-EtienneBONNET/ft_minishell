/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1init_tab_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:30:29 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/15 11:00:34 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_avance_chaine(char *cmd_tmp, int *i)
{
	int	red;
	int	c;

	while (ft_whitespace(cmd_tmp[*i]) == 1 && cmd_tmp[*i])
		(*i)++;
	red = my_check_redirection(&(cmd_tmp[*i]));
	if (((cmd_tmp[*i] == '\"' || cmd_tmp[*i] == '\'')
			&& cmd_tmp[*i] != 0) || red > 0)
	{
		c = cmd_tmp[*i];
		if (c == '\"' || c == '\'')
			while (red < 0 && cmd_tmp[++(*i)] != c)
				if (!cmd_tmp[*i])
					return (-1);
		(*i)++;
		if (red == 2)
			(*i)++;
	}
	else
		while (cmd_tmp[(*i)] != '\"' && cmd_tmp[(*i)] != '\''
			&& ft_whitespace(cmd_tmp[*i]) == 0 && cmd_tmp[*i]
			&& my_check_redirection(&(cmd_tmp[*i])) < 0)
			(*i)++;
	return (1);
}

int	my_compte_nb_chaine(char *cmd_tmp)
{
	int		i;
	int		conteur;

	i = 0;
	conteur = 0;
	while (cmd_tmp[i])
	{
		if (my_avance_chaine(cmd_tmp, &i) == -1)
			return (-1);
		conteur++;
	}
	return (conteur);
}

void	my_strlen_space_2(char *str, int *index, int *conteur)
{
	while ((ft_whitespace(str[*index]) != 1
			&& str[*index] && str[*index] != '\"' && str[*index] != '\'')
		&& my_check_redirection(&(str[(*index)])) == -1)
	{
		(*index)++;
		(*conteur)++;
	}
}

int	my_strlen_space(char *str, int *index)
{
	int	conteur;
	int	red;

	conteur = 0;
	while (ft_whitespace(str[*index]) == 1)
		*index += 1;
	red = my_check_redirection(&(str[*index]));
	if (str[*index] == '\"' || str[*index] == '\'')
	{
		if (str[*index] == '\'')
			while (str[++(*index)] != '\'' && str[*index])
				conteur++;
		else
			while (str[++(*index)] != '\"' && str[*index])
				conteur++;
		*index += 1;
	}
	else if (red > 0)
	{
		conteur = red;
		*index += red;
	}
	else
		my_strlen_space_2(str, index, &conteur);
	return (conteur);
}

char	**my_malloc_chaine(char *cmd_tmp)
{
	char	**tab_cmd;
	int		len;
	int		i;
	int		y;

	y = 0;
	i = 0;
	
	len = my_compte_nb_chaine(cmd_tmp);
	if (len == -1)
		return (NULL);
	tab_cmd = malloc(sizeof(char *) * (len + 1));
	if (tab_cmd == NULL)
		return (NULL);
	while (i < len)
	{
		tab_cmd[i] = malloc(sizeof(char) * (my_strlen_space(cmd_tmp, &y) + 1));
		if (tab_cmd[i] == NULL)
			return (my_free_double_tab((void **)tab_cmd, i));
		i++;
	}
	tab_cmd[i] = NULL;
	return (tab_cmd);
}
