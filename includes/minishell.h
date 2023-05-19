/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:22:34 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/19 13:29:15 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
# include <readline/history.h>
# include "../src/signals/signals.h"
# include "../src/parser/parser.h"
# include "../src/lexer/lexer.h"
# include "../src/builtin/builtin.h"

# define BUFFER_SIZE 4000

/* Structs */

/*enum e_token
{
	WORD,
	S_QUOTE,
	D_QUOTE,
	SPA,
	ENV,
	PIPE,
	NEW_LINE,
	REDIRECT_IN,
	REDIRECT_OUT,
	ESCAPE,
	HEREDOC,
	APP_M,
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

typedef struct s_env
{
    char *content;
    struct s_env *next;
}   t_env;

typedef struct s_heredoc
{
    char *line;
    struct s_env *next;
}   t_heredoc;


typedef struct s_parse
{
    char 	**command;
    int 	size;
    int	redirection_in;
    int	redirection_out;
    char *infilepath;  //if redirection_in == 0, infilepath = NULL
    char *outfilepath; //if redirection_out == 0, outfilepath = NULL
    int pipe;
    int	fd[2];   //if pipe == 0, fd = NULL
	struct s_parse *previous;
    struct s_parse *next;
}   t_parse;*/
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

/*int	ft_strlen(char *str);
char *split_line(char *str);
t_shell *fill_shell(t_shell *shell);
void	print_shell(t_shell *s);*/

#endif
