/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_traitement_arg_export.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:49:52 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/18 16:14:22 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_para(int *para, char *str)
{
	if ((*para == 1 && *str == -122)
		|| (*para == 2 && *str == '\''))
		*para = 0;
	else if (*para == 0 && *str == -122)
		*para = 1;
	else if ((*para == 0 && *str == '\''))
		*para = 2;
}

int	ft_len_2(char *str)
{
	int	para;
	int	y;

	para = 0;
	y = 1;
	while (*str)
	{
		if ((ft_whitespace(*str) == 1 && para == 0))
		{
			while (ft_whitespace(*str) == 1)
				str++;
			y++;
			continue ;
		}
		else
			my_para(&para, str);
		str++;
	}
	return (y);
}

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
	free((*str));
	return (res);
}

char	**my_recup_arg_2(char **str, int *y, char **res)
{
	if (**str != -122 && (**str) != '\'')
	{
		res[*y] = ft_strmicrojoin(&(res[*y]), (**str));
		if (res[*y] == NULL)
			return (my_free_double_tab((void **)res, *y));
	}
	(*str)++;
	return (res);
}

char	**my_recup_arg(char *str)
{
	int		para;
	int		y;
	char	**res;

	para = 0;
	y = 0;
	res = malloc(sizeof(char *) * (ft_len_2(str) + 1));
	if (!res)
		return (NULL);
	res[y] = NULL;
	while ((*str))
	{
		if ((ft_whitespace(*str) == 1 && para == 0))
		{
			while (ft_whitespace(*str) == 1)
				str++;
			res[++y] = NULL;
			continue ;
		}
		my_para(&para, str);
		my_recup_arg_2(&str, &y, res);
	}
	res[++y] = NULL;
	return (res);
}
