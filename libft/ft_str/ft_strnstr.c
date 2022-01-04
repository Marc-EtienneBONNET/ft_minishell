/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:46:15 by mbonnet           #+#    #+#             */
/*   Updated: 2021/09/30 17:07:50 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, char *sous_str, unsigned int size)
{
	unsigned int	x;
	unsigned int	i;

	i = 0;
	x = 0;
	if (sous_str[0] == '\0')
		return (str);
	else if (str[0] == '\0')
		return (NULL);
	while (str[x] && x < size)
	{
		while (str[x + i] == sous_str[i] && i + x < size && str[x + i])
		{
			i++;
			if (sous_str[i] == '\0')
				return (&(str[x]));
		}
		i = 0;
		x++;
	}
	return (NULL);
}
