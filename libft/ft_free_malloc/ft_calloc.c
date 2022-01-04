/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:38:55 by mbonnet           #+#    #+#             */
/*   Updated: 2021/09/30 16:55:48 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nb, size_t len_nb)
{
	void	*res;

	res = (void *)malloc(len_nb * nb);
	if (!(res))
		return (NULL);
	ft_bzero(res, nb * len_nb);
	return (res);
}
