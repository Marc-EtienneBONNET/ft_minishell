#include "minishell.h"

int		change_pwd(char *pwd, char *oldpwd)
{
	int	i;

	i = -1;
	while (term->my_env[++i].key)
	{
		if (ft_strncmp(term->my_env[i].key, "PWD", 3) == 0)
		{
			free(term->my_env[i].var);
			term->my_env[i].var = ft_strdup(pwd);
			if (!term->my_env[i].var)
				return (-1);
			free(pwd);
		}
	}
	i = -1;
	while (term->my_env[++i].key)
	{
		if (ft_strncmp(term->my_env[i].key, "OLDPWD", 6) == 0)
		{
			free(term->my_env[i].var);
			term->my_env[i].var = ft_strdup(oldpwd);
			if (!term->my_env[i].var)
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
		while (term->my_env[++i].key)
		{
			if (ft_strncmp(term->my_env[i].key, "OLDPWD", 6) == 0 && term->my_env[i].var)
			{
				chdir(term->my_env[i].var);
				printf("%s\n", term->my_env[i].var);
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
		while (term->my_env[++i].key)
		{
			if (ft_strncmp(term->my_env[i].key, "HOME", 4) == 0)
			{
				pwd = getcwd(NULL, 0);
				chdir(term->my_env[i].var);
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