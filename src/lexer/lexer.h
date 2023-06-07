/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:53:15 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/22 13:33:29 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
//# include "../../libft/libft.h"

//# define BUFFER_SIZE 4000

/* Structs */

int	g_exit;

enum e_token
{
	WORD,		//0
	S_QUOTE,	//1
	D_QUOTE,	//2
	SPA,		//3
	ENV,		//4
	PIPE,		//5
	NEW_LINE,	//6
	REDIRECT_IN,//7
	REDIRECT_OUT,//8
	ESCAPE,		//9
	HEREDOC,	//10
	APP_M,		//11
};

enum e_state
{
	OTHER,
	IN_SQUOTE,
	IN_DQUOTE,
};

typedef struct s_shell
{
	char *input;
	int	len;
	enum e_token type;
	enum e_state state;
	struct s_shell *next;
}	t_shell;

typedef struct s_parse
{
    char 	*command;
    int 	size;
    int	redirection_in;
    int	redirection_out;
    char *infilepath;  //if redirection_in == 0, infilepath = NULL
    char *outfilepath; //if redirection_out == 0, outfilepath = NULL
    int pipe;
    int	fd[2];   //if pipe == 0, fd = NULL
}   t_parse;

typedef struct s_parse_arr
{
	t_parse **cmm;
	int	check;
	int	size;
}	t_parse_arr;
/*
no redirection  0
REDIRECT_IN,	1
HEREDOC,	2

no redirection  0
REDIRECT_OUT,	1
APP_M		2

no pipe 0;
pipe 1;
*/

/* Functions */

t_shell *fill_shell(t_shell *shell);
void	print_shell(t_shell *s);
void    ft_free(char **str);

char *new_node_SPACE(char *str, t_shell **shell, int c);
char *new_node_DW(char *str, t_shell **shell, int c);
char *new_node_PIPE(char *str, t_shell **shell, int c);
char *new_node_RED(char *str, t_shell **shell, int c);
char *new_node_NL_ESC(char *str, t_shell **shell, int c);
char *new_node_DSQ(char *str, t_shell **shell, int c);

// already in libft
/*int	ft_strlen(char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);*/

int ft_isspace(char c);
int ft_issignal(char c);

void	print_parse(t_parse *s);
void parse_integration(t_shell **shell, t_parse **parse);

void    ft_expand(t_shell **shell, t_env **env);

#endif
