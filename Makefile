# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 15:14:49 by mbonnet           #+#    #+#              #
#    Updated: 2022/01/21 09:00:22 by mbonnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell 

SRCS			=	main.c\
					tmp.c\
					hendler/hendler.c\
					parsing/1protocole_de_parsing.c\
					parsing/2gestion_var_env.c\
					parsing/3tab_cmd/modifi_cmd_tmp_for_export.c\
					parsing/3tab_cmd/1init_tab_cmd.c\
					parsing/3tab_cmd/2rempli_tab_cmd.c\
					parsing/utile/checker_et_ft_utile.c\
					parsing/4struct_chene_cmd/1chenage.c\
					parsing/4struct_chene_cmd/2create_new_maillon.c\
					parsing/4struct_chene_cmd/3mouv_struct_for_red.c\
					parsing/pars_env/my_pars_env.c\
					cmd_ex/protocole_ex.c\
					cmd_ex/element_d_ex.c\
					cmd_ex/gestion_pip.c\
					cmd_ex/gestion_red.c\
					cmd_ex/ex_cmd.c\
					cmd_ex/my_heredoc.c\
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
