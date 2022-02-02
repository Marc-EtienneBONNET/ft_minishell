/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:44 by mbonnet           #+#    #+#             */
/*   Updated: 2022/02/02 16:39:30 by mbonnet          ###   ########.fr       */
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

typedef struct s_intra_red
{
	char				*fichier;
	char				*red;
}	t_intra_red;

typedef struct s_cmd
{
	char			*cmd;
	char			*path;
	t_intra_red		*red;
	char			**arg;
	char			*pip;
	pid_t			pid;
	int				tub[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;

}	t_cmd;

typedef struct str_env
{
	char	*key;
	char	*var;
}	t_env;

typedef struct s_term
{
	int		nb_maillon;
	char	**envp;
	char	*str_cmd;
	t_cmd	*cmd;
	t_env	*my_env;
	int		dernier_ret;
}	t_term;

extern t_term	g_term;

# define ENTRE 1
# define SORTI 0

//building
	//export
		//ajoue_env_export
char		*my_recup_str(char *arg, int tele);
int			my_check_doublon_and_cara_key(char *key, int tele);
int			my_ajoue_new_env(char **key, char **var);
int			my_ajoue_arg_ex(char **key, char **var);
int			my_ajoue_arg(char **arg);
		//my_export
int			mess_err2(char *str);
int			my_export(char **argv);
		//my_print_export
t_env		*my_copy_t_env(void);
int			my_sort(t_env **tmp);
int			my_print_export(void);
		//my_traitement_arg_export;
void		my_para(int *para, char *str);
int			ft_len_2(char *str);
char		*ft_strmicrojoin(char **str, char c);
int			nmy_gestion_env_heredoc(char **tmp);

	//my_cd
int			change_pwd(char *pwd, char *oldpwd);
int			op(char **argv);
int			my_cd(char **argv);
	//my_check_building
int			my_check_building(t_cmd *cmd);
	//my_echo_pwd_env
int			option(char *str);
int			my_echo(char **argv);
int			my_pwd(t_cmd *cmd);
int			my_env(t_cmd *cmd);
	//my_exit
int			ex_exit(int nbr, int err, char *str);
int			verif_arg(char *str);
long long	ft_atoll(char *str);
void		my_exit(char **argv);
	//my_unset
void		supp_var(char *argv);
int			mess_err(char *str);
int			check(char *str);
int			my_unset(char **argv);

//free
	//my_free
void		*my_free_tab(void **a_free);
void		*my_free_double_tab(void **tab_str, int nb_str);
void		*my_free_liste_chene(t_cmd *cmd);
void		*my_free_maillon(t_cmd *tmp);
int			my_free_all(int ret);

int			my_sup_maillon(void);
int			my_lancement_ex_2(void);
int			my_print_maillon_2(t_cmd *cmd, int i);

//hendler
	//hendler
void		handler_ctr_c(int code);
void		handler_ctr_c_2(int code);
void		handler_ctr_backslash(int code);

//tmp
	//tmp.c
int			my_print_list_chene(t_cmd *cmd);
int			my_print_maillon(t_cmd *cmd, int i);

//main
int			mise_en_place_de_lancement(int ac, char **envp);
int			my_check_space(char *str);
//int			my_check_guillemet(char *str);
int			main(int ac, char **av, char **envp);
int			message_error(void);
//parsing
	//my_init_parsing
int			my_init_parsing(void);
	//my_check_str_cmd
int			my_check_nb_guillemet(char *str);
int			my_check_bad_red(char *str);
	//utile.c
int			my_check_gu(int *gu, char c);
int			my_check_red(int gu, char c);
int			my_sup_char(char **str, int x);
	//my_init_tab_cmd
		//my_init_tab_cmd
char		**my_init_tab_cmd(char *str);
	//my_init_struct
		//my_init_struct
int			my_create_cmd(char **tab_cmd);
		//my_utile
int			my_check_red_pip(char *str);
char		*my_recup_ellement(char **str, int *x);
char		*my_take_red(int choose, int *x, char **str);
		//my_gestion_red
t_intra_red	*my_recup_red(char **str);
		//my_gestion_cmd
char		*my_recup_cmd(char **str);
char		*my_recup_path(char **str);
char		*my_recup_path_env(char *cmd);
char		*my_recup_pip(char **cmd);
		//my_recup_arg
char		**my_recup_arg(char **tab_cmd, t_cmd *cmd);
void		my_close_pip(t_cmd *cmd);

//ex_cmd
	//my_lancement_ex.c
int			my_lancement_ex(void);
	//my_gestion_gu_and_var_env
int			my_gestion_var_env_and_gui(t_cmd *cmd);
	//my_gestion_gu_and_var_env_utile
int			netoyage_guillemet(char **str);
int			my_check_var_env(char **str);
	//my_gestion_tub
void		my_connect_tub(void);
void		my_close_tub_parent(void);
void		my_creat_tub(void);
	//my_gestion_red
int			my_connect_red(void);
	//my_gestion_heredoc
int			my_connect_heredoc(void);
	//my_gestion_heredoc_2
int			ft_strcmp(char *str1, char *str2);
int			my_sorti(char **str, char **res, int option, int *tub);
int			my_concate(char **res, char *str);
int			netoyage_guillemet_2(char **str);
int			my_heredoc(char *deb, char *fin, int option, int *tub);
	//my_gestion_ex
int			my_exe_cmd(void);
#endif
