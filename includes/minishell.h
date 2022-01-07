/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:44 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/07 15:16:30 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_info_cmd
{
	int		nb_maillons;
}	t_info_cmd;

typedef struct s_cmd
{
	char			*path;
	char			*cmd;
	char			**arg;
	char			*red;
	t_info_cmd		*info_cmd;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;

typedef struct str_env
{
	char	*key;
	char	*var;
}	t_env;

typedef struct s_term
{
	char	**envp;
	t_env	*my_env;
	char	*str_cmd;
	t_cmd	*cmd;
	pid_t	pid;
	int		dernier_ret;
}	t_term;

t_term *term;

//hendler
	//hendler.c
void	handler_ctr_c(int code);
void	handler_ctr_c_2(int code);
void	handler_ctr_backslash(int code);

//parsing
	//protocole parsing
t_cmd	*my_parsing(char *cmd_tmp);

	//gestion_var_env
char	*my_take_key_env(char *cmd_tmp, int x);
void	my_inclus_res_var_env_2(char **tmp, int x, char **res, char *str_env);
char	*my_inclus_res_var_env(char **tmp, char *key_env, int x);
char	*my_gestion_var_env(char *cmd_tmp);

	//tab_cmd
		//init_tab_cmd
char	**my_malloc_chaine(char *cmd_tmp);
int		my_strlen_space(char *str, int *index);
void	my_strlen_space_2(char *str, int *index, int *conteur);
int		my_compte_nb_chaine(char *cmd_tmp);
int		my_avance_chaine(char *cmd_tmp, int *i);
		//rempli tab cmd 
void	my_rempli_cmd(char **tab_cmd, char *cmd_tmp, int *i, int *y);
void	my_rempli_tab_cmd(char **tab_cmd, char *cmd_tmp);

	//4struct_chene_cmd
		//1chenage.c
t_cmd	*my_init_struct_cmd(char **tab_cmd);;
t_cmd	*my_ajoute_maillon(t_cmd *cmd, t_cmd *tmp);
t_cmd	*my_ajoute_maillon_2(t_cmd *cmd, t_cmd *tmp);
		//2create_new_maillon.c
t_cmd	*new_maillons(char **tab_cmd, int *x);
t_cmd	*bzero_tmp(void);
char	**init_cmd_arg(char **tab_cmd, int *x, int *y);

	//pars_env
		//my_pars_env
int		my_init_struct_env(void);
	//utile
		//gestion des free
void	*my_free_tab(void *a_free);
void	*my_free_double_tab(void **tab_str, int nb_str);
void	*my_free_liste_chene(t_cmd *cmd);
void	*my_free_maillon_2(t_cmd *tmp);
		//checker_et_ft_utile.c
int		my_check_redirection(char *str);
char	*my_little_printf_char(char *str);
		//fonction_tmp
int		my_print_list_chene(t_cmd *cmd);

//cmd_ex
	//lancement_ex_cmd.c
int		my_lancement_ex(void);
int		my_exe_cmd(t_term *term, t_cmd *cmd);

//building
	//cd
int		my_echo(char **argv);
int	my_pwd(t_cmd *cmd);
void	my_env(t_cmd *cmd);

#endif
