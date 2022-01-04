/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_relloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:09:06 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/13 20:57:11 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_relloc(char **str, int len_more)
{
	int		len;
	char	*new_char;
	int		x;

	len = 0;
	if (str[0] != NULL)
		len = ft_strlen(str[0]);
	len += len_more;
	errno = 0;
	new_char = malloc(sizeof(char) * (len + 1));
	if (errno != 0)
		return (NULL);
	if (str[0] != NULL)
	{
		x = -1;
		while (str[0][++x] != '\0')
			new_char[x] = str[0][x];
		x--;
		while (++x < len)
			new_char[x] = ' ';
		new_char[x] = '\0';
		if (*str != NULL)
			free(*str);
	}
	return (new_char);
}
