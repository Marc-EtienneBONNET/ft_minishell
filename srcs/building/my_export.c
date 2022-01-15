/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:29:06 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/15 16:49:53 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//export haha bonjour=salut bonjour= b="salut sa vas" "b=salut sa vas" b='salut sa vas' 'b=salut sa vas' salut="bonjour "toi

void	ft_parcours(int *para, char *str, int *y)
{
	if (((*para) == 1 && (*str) == -122)
		|| ((*para) == 2 && (*str) == '\''))
		(*para) = 0;
	else if ((*para) == 0 && (*str) == -122 && (*(str - 1)) == '=')
		(*para) = 1;
	else if ((*para) == 0 && (*str) == '\'' && (*(str - 1)) == '=')
		(*para) = 2;
	else if (((*para) == 0 && (*str) == -122 && (*(str - 1)) != '=')
		|| ((*para) == 0 && (*str) == '\'' && (*(str - 1)) != '=')
		|| (ft_whitespace((*str)) == 1 && (*para) == 0))
	{
		(*y)++;
		if ((*para) == 0 && (*str) == -122 && (*(str - 1)) != '=')
			(*para) = 1;
		else if (((*para) == 0 && (*str) == '\'' && (*(str - 1)) != '='))
			(*para) = 2;
	}
}

int	ft_len(char *str)
{
	int	para;
	int	y;

	para = 0;
	y = 0;
	while ((*str))
	{
		ft_parcours(&para, *str, *(str - 1), &y);
		str++;
	}
	return (y);
}

char	*ft_strmicrojoin(char **str, char c)
{
	char	*res;
	int		x;
	int		len;

	x = 0;
	if ((*str))
		len = ft_strlen((*str));
	else
		len = 0;
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		return (NULL);
	while ((*str) && (*str)[x])
	{
		res[x] = (*str)[x];
		x++;
	}
	res[x++] = c;
	res[x] = '\0';
	free((*str));
	return (res);
}

int	ft_compte_cara_sep(char *str)
{
	int	x;
	int	conteur;

	x = 0;
	conteur = 0;
	while (str[x])
	{
		if (x == 0)
			while (ft_whitespace(str[x++]) == 1)
				conteur++;
		if (str[x] == -122 || str[x] == '\'')
			conteur++;
		x++;
	}
	while (ft_whitespace(str[--x]) == 1)
		conteur++;
	return (conteur);
}

char	**my_clean_arg(char **tabe)
{
	char	**res;
	int		y;
	int		len;
	int		x;
	int		j;

	x = 0;
	y = 0;
	while (tabe[y])
		y++;
	res = malloc(sizeof(char *) * (y + 1));
	if (!res)
		return (NULL);
	y = 0;
	while (tabe[y])
	{
		len = ft_strlen(tabe[y]) - ft_compte_cara_sep(tabe[y]);
		res[y] = malloc(sizeof(char) * (len + 1));
		if (!res[y])
			return (NULL);
		j = 0;
		x = 0;
		while (tabe[y][x] && j < len)
		{
			if (x == 0)
			{
				while (ft_whitespace(tabe[y][x]) == 1)
					x++;
			}
			if (tabe[y][x] == -122 || tabe[y][x] == '\'')
				x++;
			res[y][j++] = tabe[y][x++];
		}
		printf("res : (%s), y : %d\n", res[y], y);
		y++;
	}
	return (res);
}

char	**my_recup_arg(char *str)
{
	int		para;
	int		y;
	char	**res;

	para = 0;
	y = 0;
	res = malloc(sizeof(char *) * (ft_len(str) + 1));
	if (!res)
		return (NULL);
	while ((*str))
	{
		ft_parcours(&para, *str, *(str - 1), &y);
		res[y] = ft_strmicrojoin(&(res[y]), *str);
		str++;
	}
	res[++y] = NULL;
	y = 0;
	while (res[y])
	{
		printf("res : (%s), y : %d\n", res[y], y);
		y++;
	}
	printf("\n");
	res = my_clean_arg(res);
	return (res);
}

int	my_export(char **argv)
{
	char	**arg;

	if (!argv[1])
		printf("impretion de export\n");
	else
	{
		arg = my_recup_arg(argv[1]);
	}
	return (1);
}