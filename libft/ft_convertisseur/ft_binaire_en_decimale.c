/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binaire_en_decimale.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:15:35 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/24 15:25:07 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convertisseur_binaire_en_decimale(char *binaire)
{
	int	res;
	int	index;
	int	index_2;

	index = 0;
	res = 0;
	index_2 = ft_strlen(binaire);
	index_2--;
	if (binaire[0] == '-')
	{
		index_2--;
		index++;
	}
	while (binaire[index] != '\0')
	{
		res += ((binaire[index] - 48) * (ft_puissance(2, index_2)));
		index_2--;
		index++;
	}
	if (binaire[0] == '-')
		res *= -1;
	return (res);
}
