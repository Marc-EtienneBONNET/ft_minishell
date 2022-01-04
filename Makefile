# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 15:14:49 by mbonnet           #+#    #+#              #
#    Updated: 2022/01/04 17:52:59 by mbonnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell 

SRCS			=	main.c\
					hendler/hendler.c\

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}

HEAD			=	-I includes -I libft/includes

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra -g 

LIBFT_DIR		=	libft

LDFLAGS			=	-L ${LIBFT_DIR} -lft 

.c.o			:
					${CC} ${CFLAGS} ${HEAD}  -c $< -o ${<:.c=.o} 

$(NAME)			:	${OBJS}
					make -C ${LIBFT_DIR}
					${CC} ${CFLAGS} -lreadline ${OBJS} ${LDFLAGS} -o ${NAME} -lncurses


all				:	${NAME}

clean			:
					make clean -C ${LIBFT_DIR}
					rm -rf ${OBJS}

fclean			:	clean
					make fclean -C ${LIBFT_DIR}
					rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
