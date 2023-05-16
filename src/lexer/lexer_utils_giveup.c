#include "lexer.h"

int ft_isspace(char c)
{
    if (c == ' ' || (c <= 13 && c >= 9))
        return (1);
    return (0);
}

int ft_issignal(char c)
{
    return (c == '\'' || c == '\"' || c == '<' || c == '>'
        || c == '|' || c == '$' || ft_isspace(c) || c == '\n' || c == '\0');
}
