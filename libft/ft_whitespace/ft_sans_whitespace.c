/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sans_whitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:22:47 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/07 10:22:48 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sans_whitespace(char *str, char **res)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (str[++x])
	{
		if (ft_whitespace(str[x]) == 0)
			(*res)[++y] = str[x];
	}
	(*res)[++y] = '\0';
}
