#include "lexer.h"

static t_shell *get_shell_bottom(t_shell *shell)
{
    while(shell && shell->next != NULL)
        shell = shell->next;
    return (shell);
}

static void ft_add_tail(t_shell **shell, t_shell *new_node)
{
    t_shell *bottom;

    if (!new_node)
        return ;
    new_node->next = 0;
    if (!*shell)
    {
		*shell = new_node;
        return ;
    }
	bottom = get_shell_bottom(*shell);
    bottom->next = new_node;
    new_node->previous = bottom;
    new_node->previous->next = new_node;
}

char *new_node_D(char *str, t_shell **shell) // for $ and WORD
{
    t_shell *new_node;
    int i;
    int j;

    //printf("test in new_node_DW\n");
    //printf("in new_node: %s\n", str);

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] >= 33 && str[i] <= 126)
            j++;
        if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\t'))
            break ;
        i++;
    }
    new_node->input = ft_substr((char const *)str, 0, j);
    //printf("new_node->input: %s\n", new_node->input);
    str += j;
    //printf("str: %s\n", str);
    new_node->len = ft_strlen(new_node->input);
    if (c == 36)
        ft_add_tail(shell, new_node, ENV, OTHER);
    return (str);
}

char *new_node_W(char *str, t_shell **shell) // for $ and WORD
{
    t_shell *new_node;
    int i;
    int j;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
    if (!new_node)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] >= 33 && str[i] <= 126)
            j++;
        if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\t'))
            break ;
        i++;
    }
    new_node->input = ft_substr((char const *)str, 0, j);
    //printf("new_node->input: %s\n", new_node->input);
    str += j;
    //printf("str: %s\n", str);
    new_node->len = ft_strlen(new_node->input);
    if (c == 36)
        ft_add_tail(shell, new_node, ENV, OTHER);
    else if (c == 500)
        ft_add_tail(shell, new_node, WORD, OTHER);
    return (str);
}

char *new_node_PIPE(char *str, t_shell **shell, int c)
{
    t_shell *new_node;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    new_node->input = ft_substr((char const *)str, 0, 1);
    str += 1;
    new_node->len = ft_strlen(new_node->input);
    if (c == 124)
        ft_add_tail(shell, new_node, PIPE, OTHER);
    return (str);
}

char *new_node_RED_2(char *str, t_shell **shell, int c)
{
    t_shell *new_node;
    int i;
    int flag;

    new_node = NULL;
    i = 0;
    flag = 0;
    while(str[i])
    {
        if (str[i] == c)
            flag++;
        i++;
    }
    //printf ("c ======%d\n", c);
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    new_node->input = ft_substr((char const *)str, 0, flag);
    str += flag;
    new_node->len = ft_strlen(new_node->input);
    if (c == 60)
        ft_add_tail(shell, new_node, HEREDOC, OTHER);
    else if (c == 62)
        ft_add_tail(shell, new_node, APP_M, OTHER);
    return (str);
}

char *new_node_RED(char *str, t_shell **shell, int c)
{
    t_shell *new_node;
    int i;
    int flag;

    new_node = NULL;
    i = 0;
    flag = 0;
    while(str[i])
    {
        if (str[i] == c)
            flag++;
        if (str[i] != c)
            break ;
        i++;
    }
    if (flag == 2)
        return (new_node_RED_2(str, shell, c));
    else if (flag > 2)
        return ("error"); //todo later
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    new_node->input = ft_substr((char const *)str, 0, 1);
    str += 1;
    new_node->len = ft_strlen(new_node->input);
    if (c == 60)
        ft_add_tail(shell, new_node, REDIRECT_IN, OTHER);
    else if (c == 62)
        ft_add_tail(shell, new_node, REDIRECT_OUT, OTHER);
    return (str);
}

char *new_node_NL_ESC(char *str, t_shell **shell, int c)
{
    t_shell *new_node;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    new_node->input = ft_substr((char const *)str, 0, 1);
    str += 1;
    new_node->len = ft_strlen(new_node->input);
    if (c == 10)
        ft_add_tail(shell, new_node, NEW_LINE, OTHER);
    else if (c == 92)
        ft_add_tail(shell, new_node, ESCAPE, OTHER);
    return (str);
}

char *new_node_DSQ(char *str, t_shell **shell, int c)
{
    t_shell *new_node;
    int i;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
    i = 1;
    while (str[i])
    {
        if (str[i] == c)
            break ;
        i++;
    }
    if (str[i] == 0)
    {
        free(new_node); // add a free function later
        return (new_node_DW(str, shell, 500));
    }
    i += 1;
    new_node->input = ft_substr((char const *)str, 0, i);
    str += i;
    new_node->len = ft_strlen(new_node->input);
    if (c == 34)
        ft_add_tail(shell, new_node, D_QUOTE, IN_DQUOTE);
    else if (c == 39)
        ft_add_tail(shell, new_node, S_QUOTE, IN_SQUOTE);
    return (str);
}