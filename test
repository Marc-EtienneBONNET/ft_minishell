# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 15:14:49 by mbonnet           #+#    #+#              #
#    Updated: 2022/02/02 12:08:52 by mbonnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell 

SRCS			=	main.c\
					hendler/hendler.c\
					building/my_unset.c\
					building/my_cd.c\
					building/my_exit.c\
					building/my_echo_pwd_env.c\
					building/export/my_export.c\
					building/export/my_traitement_arg_export.c\
					building/export/ajoue_env_export.c\
					building/export/my_print_export.c\
					building/my_check_building.c\
					free/my_free.c\
					tmp/tmp.c\
					my_init_struct_env.c\
					parsing/my_init_parsing.c\
					parsing/my_check_str_cmd.c\
					parsing/utile.c\
					parsing/my_init_tab_cmd/my_init_tab_cmd.c\
					parsing/my_init_struct/my_init_struct.c\
					parsing/my_init_struct/utile.c\
					parsing/my_init_struct/my_gestion_red.c\
					parsing/my_init_struct/my_gestion_cmd.c\
					parsing/my_init_struct/my_gestion_arg.c\
					ex_cmd/my_lancement_ex.c\
					ex_cmd/my_gestion_gu_and_var_env.c\
					ex_cmd/my_gestion_gu_and_var_env_utile.c\
					ex_cmd/my_gestion_tub.c\
					ex_cmd/my_gestion_red.c\
					ex_cmd/my_gestion_heredoc.c\
					ex_cmd/my_gestion_heredoc_2.c\
					ex_cmd/my_gestion_ex.c\

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}

HEAD			=	-I includes -I libft/includes

CC				=	clang

CFLAGS			=	-Wall -Werror -Wextra -g 

LIBFT_DIR		=	libft

LDFLAGS			=	-L ${LIBFT_DIR} -lft 

.c.o			:
					${CC} ${CFLAGS} ${HEAD}  -c $< -o ${<:.c=.o} 

$(NAME)			:	${OBJS} ${LIBFT_DIR}
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
