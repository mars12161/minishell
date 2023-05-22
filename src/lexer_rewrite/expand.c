#include "lexer.h"

static char    *ft_find_path(char *str, t_env **env)
{
    t_env *temp;
    char *path;

    temp = *env;
    while(temp)
    {
        if (!strncmp(temp->content, str, ft_strlen(str)))
        {
            path = ft_strtrim(temp->content, str);
            path = ft_strtrim(str, "=");
            return (path);
        }
        temp = temp->next;
    }
    return (NULL);
}

void    ft_expand(t_shell **shell, t_env **env)
{
    t_shell *temp;

    temp = *shell;
    while(temp)
    {
        if (temp->type == D_QUOTE)
        {
            temp->input = ft_find_path(temp->input, env);
            temp->type = WORD;
            temp->state = OTHER;
        }
        temp = temp->next;
    }
}