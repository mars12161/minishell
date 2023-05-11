#include "../includes/minishell.h"

//if (!ft_strchr("GEP01S", game->map.full[y][x]))
//                ft_error("wrong parameter", game);

int   ft_builtin(t_lexer *lexer)
{
    if (ft_strchr("echo", lexer->cmd))
        return (//);
    else if (ft_strchr("cd", lexer->cmd))
        return (//);
    else if (ft_strchr("pwd", lexer->cmd))
        return (//);
    else if (ft_strchr("env", lexer->cmd))
        return (//);
    else if (ft_strchr("export", lexer->cmd))
        return (//);
    else if (ft_strchr("unset", lexer->cmd))
        return (//);
    else if (ft_strchr("exit", lexer->cmd))
        return (//);
    return (1);
    
}
