/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gestion_red.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:47:37 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/02 12:00:30 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_len_double_tab(t_intra_red *red)
{
	int	res;

	res = 0;
	if (!red)
		res = 0;
	else
		while (red[res].red != NULL)
			res++;
	return (res);
}

t_intra_red	*my_realoc_red(t_intra_red **red, char *fichier, char *redi)
{
	int			len;
	t_intra_red	*new;

	len = my_len_double_tab(*red);
	new = malloc(sizeof(t_intra_red) * (len + 2));
	if (!new)
		return (NULL);
	len = 0;
	while ((*red) && (*red)[len].red)
	{
		new[len].fichier = (*red)[len].fichier;
		new[len].red = (*red)[len].red;
		len++;
	}
	new[len].fichier = ft_strdup(fichier);
	new[len].red = ft_strdup(redi);
	len++;
	new[len].fichier = NULL;
	new[len].red = NULL;
	my_free_tab((void **)red);
	return (new);
}

int	my_recup_red_2(char **str, int *x, t_intra_red **red)
{
	char		*tmp;
	char		*tmp_2;
	int			type_red;

	type_red = 0;
	type_red = my_check_red_pip(&(*str)[*x]);
	if (type_red < 5)
		return (-1);
	tmp = my_take_red(type_red, x, str);
	tmp_2 = my_recup_ellement(str, x);
	*red = my_realoc_red(red, tmp_2, tmp);
	tmp = my_free_tab((void **) &tmp);
	tmp_2 = my_free_tab((void **) &tmp_2);
	return (1);
}

t_intra_red	*my_recup_red(char **str)
{
	int			x;
	t_intra_red	*red;
	int			gu;

	x = -1;
	gu = 0;
	red = NULL;
	while ((*str)[++x])
	{
		my_check_gu(&gu, (*str)[x]);
		if (gu == 0)
		{
			if (my_recup_red_2(str, &x, &red) == -1)
				continue ;
			if (!(*str)[x])
				break ;
		}
	}
	return (red);
}
