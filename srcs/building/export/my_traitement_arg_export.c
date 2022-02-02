/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_traitement_arg_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:49:52 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/31 10:19:50 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strmicrojoin(char **str, char c)
{
	char	*res;
	int		x;
	int		len;

	if ((*str))
		len = ft_strlen((*str));
	else
		len = 0;
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		return (NULL);
	x = 0;
	while (len > x)
	{
		res[x] = (*str)[x];
		x++;
	}
	res[x] = c;
	x += 1;
	res[x] = '\0';
	*str = my_free_tab((void **)str);
	return (res);
}

char	*my_recup_str_2(char *arg)
{
	char	*new;

	while (*arg && *arg != '=')
		arg++;
	if (!(*arg) || !(*(++arg)))
		return (NULL);
	new = ft_strdup(arg);
	if (!new)
		return (NULL);
	return (new);
}

char	*my_recup_str(char *arg, int tele)
{
	int		x;
	char	*new;

	x = 0;
	if (tele == 0)
	{
		while (arg[x] && arg[x] != '=')
			x++;
		if (arg[x] == '=')
			x++;
		new = malloc(sizeof(char) * (x + 1));
		if (!new)
			return (NULL);
		x = -1;
		while (arg[++x] && arg[x - 1] != '=')
			new[x] = arg[x];
		new[x] = '\0';
		return (new);
	}
	return (my_recup_str_2(arg));
}
