#include "minishell.h"

int    aj_env_to_exp(char *key, char *var)
{
    int     i;
    char    **tmp;

    i = 0;
    while (term->exp[i])
        i++;
    tmp = malloc(sizeof(char *) * (i + 2));
    if (!tmp)
        return (1);
    i = -1;

    while (term->exp[++i])
        tmp[i] = ft_strdup(term->exp[i]);
    tmp[i] = ft_strjoin(key, "=\"");
    tmp[i] = ft_strjoin(tmp[i], var);
    tmp[i] = ft_strjoin(tmp[i], "\"");
    i++;
    tmp[i] = NULL;
    i = -1;
    while (term->exp[++i])
        free(term->exp[i]);
    free(term->exp);
    term->exp = tmp;
    return (0);
}