/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo_pwd_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:32:47 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/27 15:35:43 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	option(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) >= 2)
	{
		if (str[0] == '-' && str[1] == 'n')
		{
			while (str[++i])
			{
				if (str[i] != 'n')
					return (0);
				return (1);
			}
		}
	}
	return (0);
}

int	my_echo(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i] && option(argv[i]))
	{
		flag = 1;
		i++;
	}
	if (!(argv[i]) && flag == 0)
		printf("\n");
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		else if (!(argv[i + 1]) && flag == 0)
			printf("\n");
		i++;
	}
	if (g_term.cmd->pid == 0)
		exit (0);
	else
		return (0);
}

int	my_pwd(t_cmd *cmd)
{
	char	*pwd;

	if (!cmd->arg[1])
	{
		pwd = getcwd(NULL, 0);
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf(ROUGE"pwd: -a : option non valable\n"BLANC);
	if (g_term.cmd->pid == 0)
		exit (0);
	else
		return (0);
}

int	my_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->arg[1])
	{
		while (g_term.my_env[i].key)
		{
			if (g_term.my_env[i].key[ft_strlen(
						g_term.my_env[i].key) - 1] == '=')
			{
				printf("%s", g_term.my_env[i].key);
				if (g_term.my_env[i].var)
					printf("%s", g_term.my_env[i].var);
				printf("\n");
			}
			i++;
		}
	}
	else
		printf(ROUGE"env: option non valable\n"BLANC);
	if (g_term.cmd->pid == 0)
		exit (0);
	else
		return (0);
}
