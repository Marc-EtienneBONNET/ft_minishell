/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdoublejoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:04:02 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/14 09:26:06 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdoublejoin(char **tab, char *str)
{
	char	**res;
	int		len;

	len = 0;
	res = NULL;
	if (!str)
		return (NULL);
	while (tab && tab[len])
		len++;
	res = malloc(sizeof(char *) * (len + 2));
	if (!res)
		return (NULL);
	len = 0;
	while (tab[len])
	{
		res[len] = ft_strdup(tab[len]);
		len++;
	}
	res[len++] = ft_strdup(str);
	res[len] = NULL;
	return (res);
}

char	**ft_strdoubledup(char **tab)
{
	char	**res;
	int		len;

	len = 0;
	res = NULL;
	while (tab && tab[len])
		len++;
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	len = 0;
	while (tab[len])
	{
		res[len] = ft_strdup(tab[len]);
		len++;
	}
	res[len] = NULL;
	return (res);
}