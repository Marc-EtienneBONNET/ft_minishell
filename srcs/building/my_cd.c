#include "minishell.h"

int		change_pwd(char *pwd, char *oldpwd)
{
	int	i;

	i = -1;
	while (g_term->my_env[++i].key)
	{
		if (ft_strncmp(g_term->my_env[i].key, "PWD", 3) == 0)
		{
			free(g_term->my_env[i].var);
			g_term->my_env[i].var = ft_strdup(pwd);
			if (!g_term->my_env[i].var)
				return (-1);
			free(pwd);
		}
	}
	i = -1;
	while (g_term->my_env[++i].key)
	{
		if (ft_strncmp(g_term->my_env[i].key, "OLDPWD", 6) == 0)
		{
			free(g_term->my_env[i].var);
			g_term->my_env[i].var = ft_strdup(oldpwd);
			if (!g_term->my_env[i].var)
				return (-1);
			free(oldpwd);
		}
	}
	return (0);
}

int		op(char **argv)
{
	int i;

	i = -1;
	if (ft_strncmp(argv[1], "-", 1) == 0)
	{
		while (g_term->my_env[++i].key)
		{
			if (ft_strncmp(g_term->my_env[i].key, "OLDPWD", 6) == 0 && g_term->my_env[i].var)
			{
				chdir(g_term->my_env[i].var);
				printf("%s\n", g_term->my_env[i].var);
				return (0);
			}
		}
	}
	if (chdir(argv[1]) == -1)
	{
		write(2, "minishell: cd: ", ft_strlen("minishell: cd: "));
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": ", 2);
		perror("");
	}
	return (0);
}

int my_cd(char **argv)
{
	char	*pwd;
	char	*oldpwd;
	int		i;

	i = -1;
	oldpwd = getcwd(NULL, 0);
	if (!argv[1] || (ft_strncmp(argv[1], "--", 2) == 0) || (ft_strncmp(argv[1], "~", 1) == 0))
	{
		while (g_term->my_env[++i].key)
		{
			if (ft_strncmp(g_term->my_env[i].key, "HOME", 4) == 0)
			{
				pwd = getcwd(NULL, 0);
				chdir(g_term->my_env[i].var);
				return (change_pwd(pwd, oldpwd));
			}
		}
	}
	op(argv);
	pwd = getcwd(NULL, 0);
	if (change_pwd(pwd, oldpwd) == -1)
		return (-1);
	return (0);
}