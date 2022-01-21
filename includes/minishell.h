/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:44 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/21 16:39:45 by mbonnet          ###   ########.fr       */
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
	t_info_cmd		*info_cmd;
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
	int		save_stdin;
	int		save_stdout;
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
int			my_concatonne(char **tmp, char **str);
void		my_sorti(char **str, char **tmp, int *tub);
void		my_tub(int tele, int *tub);
void		my_heredoc(pid_t pid, int *tub);
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
	//3tab_cmd
		//1init_tab_cmd
int			my_avance_chaine(char *cmd_tmp, int *i);
int			my_compte_nb_chaine(char *cmd_tmp);
void		my_strlen_space_2(char *str, int *index, int *conteur);
int			my_strlen_space(char *str, int *index);
char		**my_malloc_chaine(char *cmd_tmp);
		//2rempli_tab_cmd
void		my_rempli_cmd(char **tab_cmd, char *cmd_tmp, int *i, int *y);
void		my_rempli_tab_cmd(char **tab_cmd, char *cmd_tmp);
		//modifi_cmd_tmp_for_ex
int			my_install_guillemet(char **res, int *x);
void		my_passe_guillemet(char *res, int *x);
char		*my_modif_for_export(char *cmd_tmp);
void		my_avance_whitespace(char *str, int *i);
	//4struct_chene_cmd
		//1chenage
t_cmd		*my_ajoute_maillon_2(t_cmd *cmd, t_cmd *tmp);
t_cmd		*my_ajoute_maillon(t_cmd *cmd, t_cmd *tmp);
void		new_maillons_3(char **cmd, char *path);
t_cmd		*new_maillons(char **tab_cmd, int *x);
t_cmd		*my_init_struct_cmd(char **tab_cmd);
		//2create_new_maillon
char		**init_cmd_arg(char **tab_cmd, int *x);
t_cmd		*bzero_tmp(void);
char		*my_modifie_cmd(t_cmd *tmp);
t_cmd		*new_maillons_2(char **tab_cmd, int *x, t_cmd *tmp);
		//3mouv_struct_for_red_2
t_cmd		*my_mouv_struct_for_red(t_cmd **cmd);
		//3mouv_struct_for_red
int			my_ajoute_arg(t_cmd **cmd, t_cmd **cmd_new_arg);
void		my_ajuste_pointeur(t_cmd **cmd);
char		*my_choose_fichier(t_cmd *cmd);
int			my_mouv_struct_for_red_droite(t_cmd **cmd);
int			my_mouv_struct_for_red_gauche(t_cmd **cmd);
		//my_gestion_path
char		**my_recup_path_2(void);
char		*my_recup_path(t_cmd *cmd);
char		*my_gestion_path(t_cmd *tmp);
	//pars_env
		//my_pars_env
char		*my_env_key(char *env);
char		*my_env_var(char *env);
int			my_init_struct_env(void);
	//utile
		//checker_et_ft_utile
int			my_check_redirection(char *str);
char		*my_little_printf_char(char *str);
	//protocole parsing
char		*my_gestion_var_env_2(char **res, int *x);
int			my_gestion_for_export(void);
int			my_lancement_struct(char **cmd_tmp_env);
char		*my_gestion_var_env(char *cmd_tmp);
int			my_parsing(void);
	//2gestion_var_env
char		*my_take_key_env(char *cmd_tmp, int x);
void		my_inclus_res_var_env_2(char **tmp, int x,
				char **res, char *str_env);
char		*my_give_str_env(char *key);
char		*my_recup_str_env(char **tmp, char *key_env);
char		*my_inclus_res_var_env(char **tmp, char *key_env, int x);

//main
int			mise_en_place_de_lancement(int ac, char **envp);
int			my_check_space(char *str);
int			my_check_guillemet(char *str);
int			main(int ac, char **av, char **envp);

#endif
