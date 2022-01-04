/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treat_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 22:04:34 by hsaadaou          #+#    #+#             */
/*   Updated: 2021/09/30 17:05:20 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_multiple_size(char *str, va_list arg, t_prec *t)
{
	int		temp;

	temp = 0;
	temp = ft_atoi(str);
	while (temp == 0 && ft_strchr("0-", *str))
		str++;
	if (*str == '*')
	{
		t->sub = -1;
		temp = (int)va_arg(arg, int);
	}
	return (temp);
}

static int	ft_get_star_arg(va_list arg, char *str, int is_size, t_prec *t)
{
	int		out;
	int		temp;

	out = -1;
	temp = 0;
	if (str[0] == '*')
		temp = (int)va_arg(arg, int);
	else
		temp = ft_get_multiple_size(str, arg, t);
	if (temp >= 0)
		out = temp;
	if (temp < 0 && is_size == 1)
	{
		t->sub = -1;
		t->align_right = 1;
		out = temp * -1;
	}
	return (out);
}

static t_prec	*ft_lst_init(va_list arg, char *str)
{
	t_prec			*tmp;
	int				i;

	i = 0;
	if (!(ft_lst_new_prec(&tmp)))
		return (NULL);
	if (str[i] == '-')
	{
		tmp->align_right = 1;
		i++;
	}
	if (str[i] == '0')
	{
		tmp->sub = 1;
		i++;
	}
	tmp->size = ft_get_star_arg(arg, str + i, 1, tmp);
	while (str[i] && ft_strchr("0123456789*-", str[i]))
		i++;
	if (str[i] && str[i] == '.')
		tmp->after_dot = ft_get_star_arg(arg, str + i + 1, 0, tmp);
	if (ft_strchr("csxXpuido%", str[ft_strlen(str) - 1]))
		tmp->type = str[ft_strlen(str) - 1];
	return (tmp);
}

void	ft_treat_prec(va_list a, int *i, const char *str, t_prec **lst)
{
	int		l;
	char	*tmp;

	l = *i + 1;
	if (!str[l])
		return ;
	while (str[l] && ft_strchr("0123456789*.-", str[l]))
		l++;
	tmp = ft_substr(str + *i, 0, ((l + 1) - *i));
	if (ft_strlen(tmp))
		*lst = ft_lst_init(a, tmp);
	free(tmp);
	*i = l;
}
