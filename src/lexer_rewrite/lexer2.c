/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:00:23 by yli               #+#    #+#             */
/*   Updated: 2023/05/22 19:00:25 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_shell	*init_lexer_node()
{
	t_shell *new_node;

    new_node = NULL;
    new_node = (t_shell *)malloc(sizeof(t_shell));
	if (!new_node)
		return (NULL);
	new_node->command = (char **)malloc(sizeof(char *) * 50;
	if (!new_node->command)
        return 0;
    new_node->command[50] = 0;
    new_node->redirection_in = 0;
    new_node->infilepath = NULL;
    new_node->outfilepath = NULL;
    new_node->pipe = 0;
    new_node->previous = 0;
    new_node->next = 0;
}

t_shell *fill_shell(t_shell *shell, t_env **env)
{
	char *str;
	int	i = 0;
	t_shell *node;

	str = readline("[minishell:]");
	node = init_lexer_node();
	while (*str == ' ')
		str++;
	while (*str)
	{

		if (*str == '$')
		{
			str = new_node_WORD_ENV(char *str, t_shell **shell, t_shell *new_node, t_env **env);
			printf("DOLLAR\n");
		}
		else if (*str == '|')
		{
			str = new_node_PIPE(str, &shell, 124);
			printf("PIPE\n");
		}
		else if (*str == '\"')
		{
			printf("DQ\n");
			str = new_node_DSQ(str, &shell, 34);
		}
		else if (*str == '\'')
		{
			printf("SQ\n");
			str = new_node_DSQ(str, &shell, 39);
		}
		else if (*str == '<')
		{
			printf("REDI OR HEREDOC\n");
			str = new_node_RED(str, &shell, 60);
		}
		else if (*str == '>')
		{
			printf("REDO OR APP_M\n");
			str = new_node_RED(str, &shell, 62);
		}
		else if (*str == '\\')
		{
			printf("ESC\n");
			str = new_node_NL_ESC(str, &shell, 92);
		}
		else
		{
			printf("WORD\n");
			str = new_node_W(str, &shell, node, 0);
		}
		//printf("helloend\n");
	}
	//ft_free(result);
	return (shell);
}

static t_shell *ft_check_add_tail(char *str, t_shell **shell, t_shell *new_node)
{
    t_shell *bottom;
    t_shell *new_node2;

    if (str + 1 == 0 || new_node->pipe == 1)
    {
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
    	new_node2 = init_lexer_node();
		return (new_node2);
	}
	else
		return (NULL);
}

static int new_node_word_len(char *str)
{
	int i;
    int j;
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
    return (j);
}

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

static int new_node_quote_len(char *str, int c)
{
	int i;

    i = 0;

    while (str[i])
    {
        if (str[i] == c)
            break ;
        i++;
    }
    i += 1;
    return (i);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

statoc char 

static char *ft_dquote_env_check(char *str, char quote)
{
	int i;
	char *result;

	result = ft_strtrim(str, quote);
	ft_free_str(&str);
	i = ft_strchr(result, '$');
	if (i > -1)

}
char *new_node_WORD(char *str, t_shell **shell, t_shell *new_node, t_env **env) // for $ and WORD
{
    static int n;
    char *envstr;
    int j;

    
    if (*str == '$')
    {
    	envstr = ft_substr((char const *)str, 0, j);
    	new_node->command[n] = ft_expand(envstr, env);
    }
    else if (*str == "\'")
    {
    	j = new_node_quote_len(char *str, "\'")
    	new_node->command[n] = ft_substr((char const *)str, 0, j);
    }
    else if (*str == "\"")
    {
    	j = new_node_quote_len(char *str, "\"")

    }
    else
    {	j = new_node_WORD_len(str);
    	new_node->command[n] = ft_substr((char const *)str, 0, j);
    }
    str += j;
    ft_check_add_tail(str, shell, new_node);
    return (str);
}

static int ft_check_red_mode(char *str)
{
	if (*str == '<' && str + 1 != '<')
		return (1);
	else
		return (2);
	if (*str == '>' && str + 1 != '>')
		return (3);
	else
		return (4);
}

static void new_node_red_input(char *str, t_shell *new_node)
{
	int a;

	a = ft_check_red_mode(str);
	if (a == 1)
	{
		new_node->redirection_in = 1;
		new_node->infilepath = str;
	}
	else if (a == 2)
	{
		new_node->redirection_in = 2;
		new_node->infilepath = str;
	}
	else if (a == 3)
	{
		new_node->redirection_out = 1;
		new_node->outfilepath = str;
	}
	else if (a == 4)
	{
		new_node->redirection_out = 2;
		new_node->outfilepath = str;
	}

}

char *new_node_red(char *str, t_shell **shell, t_shell *new_node)
{
    int i;
    int j;
    char *path;

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
    if (j <= 2)
    {
    	while(str[i] == ' ')
    	{
    		i++;
    		j++;
    	}
    	while (str[i])
    	{
        	if (str[i] >= 33 && str[i] <= 126)
            	j++;
        	if (str[i] >= 33 && str[i] <= 126 && (str[i + 1] == ' ' || str[i + 1] == '\t'))
            	break ;
        	i++;
    	}
    }
    path = ft_substr((char const *)str, 0, j);
    str += j;
    new_node_red_input(path, new_node);
    ft_check_add_tail(str, shell, new_node);
    return (str);
}

char *new_node_PIPE(char *str, t_shell **shell, t_shell *new_node)
{
   	new_node->pipe = 1;
    str += 1;
    
    return (str);//not finish
}

char *new_node_DSQ(char *str, t_shell **shell, int c)
{
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

char *new_node_quote(char *str, t_shell **shell, t_shell *new_node, t_env **env)
{
	int i;


	i = 1;
	while (str[i])
    {
        if (str[i] == c)
            break ;
        i++;
    }
    if (str[i] == 0)
        return (new_node_WORD(str, shell, new_node, env));
    i += 1;


}
