/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puissance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:24:34 by mbonnet           #+#    #+#             */
/*   Updated: 2021/11/24 15:24:43 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puissance(int nb, int puissance)
{
	int	res;

	res = nb;
	if (puissance == 0)
		return (1);
	while (puissance > 1)
	{
		res *= nb;
		puissance--;
	}
	return (res);
}
