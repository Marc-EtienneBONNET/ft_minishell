/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_building.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:32:47 by mbonnet           #+#    #+#             */
/*   Updated: 2022/01/06 16:32:57 by mbonnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		option(char *str)
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

int		ft_echo(char **argv)
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
	return (0);
}

int		pwd(void)
{
	char *pwd;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	return (0);
}