# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 15:47:27 by mbonnet           #+#    #+#              #
#    Updated: 2021/11/12 16:52:09 by mbonnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  ft_convertisseur/ft_atoi.c\
		ft_convertisseur/ft_itoa.c\
		ft_convertisseur/ft_split.c\
		ft_convertisseur/ft_decimale_en_binaire.c\
		ft_convertisseur/ft_binaire_en_decimale.c\
		ft_fd/ft_putchar_fd.c\
		ft_fd/ft_putendl_fd.c\
		ft_fd/ft_putnbr_fd.c\
		ft_fd/ft_putstr_fd.c\
		ft_free_malloc/ft_relloc.c\
		ft_free_malloc/ft_calloc.c\
		ft_free_malloc/ft_free_double_tab_char.c\
		ft_get_next_line/get_next_line_2.c\
		ft_get_next_line/get_next_line.c\
		ft_get_next_line/get_next_line_utils.c\
		ft_liste_chene/ft_lstadd_back.c\
		ft_liste_chene/ft_lstadd_front.c\
		ft_liste_chene/ft_lstclear.c\
		ft_liste_chene/ft_lstdelone.c\
		ft_liste_chene/ft_lstiter.c\
		ft_liste_chene/ft_lstlast.c\
		ft_liste_chene/ft_lstmap.c\
		ft_liste_chene/ft_lstnew.c\
		ft_liste_chene/ft_lstsize.c\
		ft_str/ft_bzero.c\
		ft_str/ft_isalnum.c\
		ft_str/ft_isalpha.c\
		ft_str/ft_isascii.c\
		ft_str/ft_isdigit.c\
		ft_str/ft_isprint.c\
		ft_str/ft_memccpy.c\
		ft_str/ft_memchr.c\
		ft_str/ft_memcmp.c\
		ft_str/ft_memcpy.c\
		ft_str/ft_memmove.c\
		ft_str/ft_memset.c\
		ft_str/ft_putstr.c\
		ft_str/ft_strchr.c\
		ft_str/ft_strdup.c\
		ft_str/ft_strjoin.c\
		ft_str/ft_strlcat.c\
		ft_str/ft_strlcpy.c\
		ft_str/ft_strlen.c\
		ft_str/ft_strmapi.c\
		ft_str/ft_strncmp.c\
		ft_str/ft_strnstr.c\
		ft_str/ft_strrchr.c\
		ft_str/ft_strtrim.c\
		ft_str/ft_substr.c\
		ft_str/ft_tolower.c\
		ft_str/ft_toupper.c\
		ft_whitespace/ft_strlen_moin_whitespace.c\
		ft_whitespace/ft_whitespace.c\
		ft_printf/ft_printf.c ft_printf/srcs/parse_args.c \
		ft_printf/srcs/ft_lst_init.c ft_printf/srcs/converter/utils.c \
		ft_printf/srcs/converter/ft_convert_base.c \
		ft_printf/srcs/converter/ft_convert_base2.c \
		ft_printf/srcs/ft_treat_precision.c \
		ft_printf/srcs/converter/ft_utoa.c \
		ft_printf/srcs/ft_arg_c.c ft_printf/srcs/ft_arg_d.c \
		ft_printf/srcs/ft_arg_p.c \
		ft_printf/srcs/ft_arg_s.c ft_printf/srcs/ft_arg_x.c\
		ft_whitespace/ft_sans_whitespace.c\
		ft_matematique/ft_puissance.c\
		ft_affichage/ft_binaire.c\

OBJS			=	${SRCS:.c=.o}

HEAD			=	includes

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra -g

NAME			=	libft.a

.c.o			:
					${CC} ${CFLAGS} -I ${HEAD} -c $< -o ${<:.c=.o}

${NAME}			:	${OBJS}
					ar -rcs ${NAME} ${OBJS}

all				:	${NAME}

clean			:
					rm -rf ${OBJS}

fclean			:	clean
					rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
