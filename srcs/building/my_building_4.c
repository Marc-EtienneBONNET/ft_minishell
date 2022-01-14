#include "minishell.h"

int verif(char *str)
{
    int i;
    i = 0;
    while (term->exp[i])
    {
        if (ft_strncmp(term->exp[i], str, ft_strlen(term->exp[i])) == 0)
            return (1);
        i++;
    }
    return (0);
}

int	ft_strcmp(char *str1, char *str2)
{
	unsigned int	x;

	x = 0;
	while ((str1[x]) || (str2[x]))
	{
		if ((unsigned char)str1[x] < (unsigned char)str2[x])
			return (-1);
		else if ((unsigned char)str1[x] > (unsigned char)str2[x])
			return (1);
		x++;
	}
	return (0);
}

void    creat_export(void)
{
    int i;

    i = 0;
    while (term->my_env[i].key)
        i++;
    term->exp = malloc(sizeof(char *) * (i + 1));
    if (!term->exp)
        return ;
    i = -1;
    while (term->my_env[++i].key)
    {
        term->exp[i] = ft_strjoin(term->my_env[i].key, "=");
        term->exp[i] = ft_strjoin(term->exp[i], term->my_env[i].var);
    }
    term->exp[i] = NULL;
}

int    aj_export(char *str)
{
    char    **tmp;
    int     i;
    int     k;

    k = 0;
    while (term->exp[k])
        k++;
    tmp = malloc(sizeof(char *) * (k + 2));
    if (!tmp)
        return (1);
    i = -1;
    while (term->exp[++i])
        tmp[i] = ft_strdup(term->exp[i]);
    tmp[i++] = ft_strdup(str);
    tmp[i] = NULL;
    i = -1;
    while (++i < k)
        free(term->exp[i]);
    free(term->exp);
    term->exp = tmp;
    return (0);
}

int sort_exp(void)
{
    int i;
    int j;
    char    *tmp;

    i = -1;
    while(term->exp[++i])
    {
        j = i;
        while (term->exp[++j])
        {
            if (ft_strcmp(term->exp[i], term->exp[j]) > 0)
            {
                tmp = term->exp[i];
                term->exp[i] = term->exp[j];
                term->exp[j] = tmp;
            }
        }
    }
    i = -1;
    while (term->exp[++i])
        printf("declare -x %s\n", term->exp[i]);
    return (0);
}