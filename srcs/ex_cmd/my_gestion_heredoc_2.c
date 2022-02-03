/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gestion_heredoc_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:48:24 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/03 11:48:07 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	my_sorti(char **str, char **res, int option, int *tub)
{
	close(tub[SORTI]);
	dup2(tub[ENTRE], 1);
	close(tub[ENTRE]);
	if (option == 0)
		my_check_var_env(res);
	write(1, (*res), ft_strlen((*res)));
	*str = my_free_tab((void **)str);
	*res = my_free_tab((void **)res);
	exit(0);
	return (1);
}

int	my_concate(char **res, char *str)
{
	char	*tmp;

	tmp = ft_strdup(*res);
	*res = my_free_tab((void **)res);
	if (!tmp)
		*res = ft_strdup(str);
	else
		*res = ft_strjoin(tmp, str);
	tmp = my_free_tab((void **)&tmp);
	tmp = ft_strdup(*res);
	*res = my_free_tab((void **)res);
	*res = ft_strjoin(tmp, "\n");
	tmp = my_free_tab((void **)&tmp);
	return (1);
}

int	netoyage_guillemet_2(char **str)
{
	int	x;

	x = 0;
	if (!*str)
		return (0);
	if ((*str)[0] == '\"' && (*str)[1] == '\0')
		return (2);
	if ((*str)[0] == '\'' && (*str)[1] == '\0')
		return (2);
	while ((*str)[x])
	{
		if ((*str)[x] == '\"' || (*str)[x] == '\'')
			my_sup_char(str, x);
		else
			x++;
	}
	return (0);
}

int	my_heredoc(char *deb, char *fin, int option, int *tub)
{
	char	*str;
	char	*res;
	char	*tmp;
	int		verif;

	str = NULL;
	res = NULL;
	tmp = NULL;
	(void)option;
	verif = netoyage_guillemet_2(&fin);
	verif += netoyage_guillemet_2(&deb);
	while (1)
	{
		str = readline(VERT"Heredoc>"BLANC);
		if (deb == NULL && ft_strcmp(fin, str) == 0 && verif == 0)
			my_sorti(&str, &res, option, tub);
		else if (deb == NULL && ft_strcmp(fin, str) == 0 && verif != 0)
			my_sorti_2(&str, &res, option, tub);
		else if (deb == NULL && str)
			my_concate(&res, str);
		else if (deb != NULL && ft_strcmp(deb, str) == 0)
			deb = NULL;
		str = my_free_tab((void **)&str);
	}
}
