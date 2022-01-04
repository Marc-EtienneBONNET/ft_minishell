/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 03:54:22 by mbonnet           #+#    #+#             */
/*   Updated: 2021/10/01 03:54:24 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <inttypes.h>

# define HEXA_LOWER "0123456789abcdef"
# define HEXA_UPPER "0123456789ABCDEF"
# define NOT_SET -1

typedef struct s_precision	t_prec;
struct	s_precision {
	int					sub;
	int					align_right;
	int					size;
	int					after_dot;
	char				type;
};

int		ft_printf(const char *str, ...);
int		ft_lst_new_prec(t_prec **lst);
char	*ft_convert_hex(long int var, char *base_to);
char	*convert_number(long long nbr, char *base);
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);
int		ft_process_args(const char *s, va_list arg, t_prec *lst);
void	ft_treat_prec(va_list arg, int *i, const char *str, t_prec **lst);
void	ft_arg_c(va_list arg, char c, t_prec **lst, int *size);
void	ft_arg_d(va_list arg, t_prec **lst, int *size, int is_signed);
void	ft_arg_s(va_list arg, t_prec **lst, int *size);
void	ft_arg_x(va_list arg, char base, t_prec **lst, int *size);
void	ft_arg_p(va_list arg, t_prec **lst, int *size);
void	ft_lst_prec_delone(t_prec **lst);
int		ft_part_putstr(const char *s, size_t i);
int		ft_print_char(char c, int nb);
char	*ft_utoa(unsigned int nb);

#endif
