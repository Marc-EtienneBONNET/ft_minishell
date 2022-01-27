/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:44 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 17:22:32 by mbonnet          ###   ########.fr       */
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
	char			*cmd;
	char			*path;
	char			*fichier_1;
	char			*fichier_2;
	char			*intra_red;
	char			**arg;
	char			*red;
	pid_t			pid;
	int				tub[2];
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
char		**my_recup_arg_2(char **str, int *y, char **res);
char		**my_recup_arg(char *str);
int	my_gestion_env_heredoc(char **tmp);

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

//cmd_ex
	//element_d_ex
int			creat_pipe(void);
int			creat_fork(void);
int			boucle_close_tub(void);
int			boucle_ex_fork(pid_t pid);
int			boucle_ex(void);
	//ex_cmd
int			my_ex_building(t_cmd *cmd);
int			my_exe_cmd(t_term g_term, t_cmd *cmd);
	//gestion_pip
void		my_tub_entre_sorti_enfant(t_cmd *cmd);
void		my_close_pip(t_cmd *cmd);
	//gestion_red
int			my_check_type_red(char *str);
int			my_ecrase_fichier(t_cmd *cmd);
int			my_recup_fd_fichier(t_cmd *cmd);
pid_t		my_gestion_red(t_cmd *cmd);
	//my_heredoc
int			my_concatonne_2(char **tmp, char **str, char **tmp_2);
int			my_concatonne(char **tmp, char **str, char **fd_ouv);
void		my_sorti(char **str, char **tmp, int *tub);
void		my_tub(int tele, int *tub);
void		my_heredoc(pid_t pid, int *tub, char *fd_ouv, char	*fd_ferm);
	//my_heredoc_2
int			my_check_var_env_heredoc(char **tmp);
	//protocole_ex
int			message_error(void);
int			boucle_waitpid(void);
int			my_lancement_ex(void);

//free
	//my_free
void		*my_free_tab(void *a_free);
void		*my_free_double_tab(void **tab_str, int nb_str);
void		*my_free_liste_chene(t_cmd *cmd);
void		*my_free_maillon(t_cmd *tmp);
int			my_free_all(int ret);

//hendler
	//hendler
void		handler_ctr_c(int code);
void		handler_ctr_c_2(int code);
void		handler_ctr_backslash(int code);

//parsing
	//init_tab_cmd
		//my_init_tab
char		**my_creat_tab_cmd(void);
		//my_rempli_tab
int			my_check_guil(int	*gu, char c);
int			my_take_nb_tab(void);
int			my_strlen_cmd(char *str);
int			my_copie(char **tab_cmd, int y, int i, char *str);
int			my_rempli_tab_cmd(char **tab_cmd, char *str);
		//my_sup_tab_cmd_vide
int			ft_compte(char **tab_cmd);
char		*my_copi_tab_cmd(char *str);
char		**my_sup_str_vide(char **tab_cmd);
	//my_init_struct
		//my_choose_index_2
char		*recup_red(char *red);
int			my_ajoute_arg(char *str, int *x, char ***arg);
void		my_gomme_path(t_cmd *tmp);
void		my_take_arg(char *str, t_cmd *tmp);
int			my_take_red(char *str, t_cmd *tmp);
		//my_choose_index_3
int			my_recup_path(t_cmd *tmp);
int			my_take_cmd_and_path(char *str, t_cmd *tmp);
		//my_choose_index
void		my_take_fichier_and_intra_red(char *str, t_cmd *tmp);
int			my_passe_fichier(int x, int red, char *str, int *gu);
char		**my_choose_var_env_path(void);
char		*my_choose_path(t_cmd *tmp);
		//my_init_struct
char		*recup_element(char *str, int *x);
t_cmd		*my_creat_tmp(char *str);
int			my_add_liste_chene(t_cmd *tmp);
int			my_init_struct(char **tab_cmd);
	//my_init_struct_env
char		*my_env_key(char *env);
char		*my_env_var(char *env);
int			my_init_struct_env(void);
	//my_preparatif_str_cmd
int			my_check_guillemet(void);
char		*my_recup_key(char *cmd);
int			my_transforme_str_cmd_pour_var_env_2(int *x, char **new_cmd,
				char *var_env, char *key);
int			my_transforme_str_cmd_pour_var_env(int *x, char *key);
int			my_check_var_env(void);
	//my_protocole_de_parsing
int			my_parsing(void);
	//utile
int			my_check_redirection(char *str);
int			my_check_cara_legale(char c);

//tmp
	//tmp.c
int			my_print_list_chene(t_cmd *cmd);
int			my_print_maillon(t_cmd *cmd, int i);

//main
int			mise_en_place_de_lancement(int ac, char **envp);
int			my_check_space(char *str);
//int			my_check_guillemet(char *str);
int			main(int ac, char **av, char **envp);

//tmp
	//tmp.c
int			my_print_list_chene(t_cmd *cmd);

#endif
