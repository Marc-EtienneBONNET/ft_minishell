/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_tab_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:38:55 by mbonnet           #+#    #+#             */
/*   Updated: 2021/09/30 16:56:24 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_tab_char(char **tab)
{
	int	x;

	x = -1;
	if (!tab)
		return ;
	while (tab[++x])
		free(tab[x]);
	free(tab[x]);
	free(tab);
}
