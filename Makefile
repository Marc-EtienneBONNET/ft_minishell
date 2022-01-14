# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 15:14:49 by mbonnet           #+#    #+#              #
#    Updated: 2022/01/14 08:48:18 by mbonnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell 

SRCS			=	main.c\
					hendler/hendler.c\
					parsing/1protocole_de_parsing.c\
					parsing/2gestion_var_env.c\
					parsing/3tab_cmd/1init_tab_cmd.c\
					parsing/3tab_cmd/2rempli_tab_cmd.c\
					parsing/utile/gestion_des_free.c\
					parsing/utile/checker_et_ft_utile.c\
					parsing/utile/fonction_tmp.c\
					parsing/4struct_chene_cmd/1chenage.c\
					parsing/4struct_chene_cmd/2create_new_maillon.c\
					parsing/4struct_chene_cmd/3mouv_struct_for_red.c\
					parsing/pars_env/my_pars_env.c\
					cmd_ex/lancement_ex_cmd.c\
					cmd_ex/gestion_pip.c\
					cmd_ex/ex_cmd.c\
					cmd_ex/gestion_red.c\
					building/my_building.c\
					building/my_building_2.c\
					building/my_building_3.c\

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
