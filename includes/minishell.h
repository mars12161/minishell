#ifndef MINISHELL
# define MINISHELL

# include "libft.h"
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

# define BUFFER_SIZE 4000

typedef struct s_shell
{
	t_token	*start;
	t_envp	*envp;
	t_envp	*secret_envp;
	int	in;
	int	out;
	int	fdin;
	int	fdout;
	int	pipein;
	int	pipeout;
	int	pid;
	//int	charge;
	int	parent;
	//int	last;
	int	result;
	bool	exit;
	int	not_execute;
}	t_shell

typedef struct	s_lexer
{
	char *cmd;
	t_input	token;
	struct s_lexer *next;
}	t_lexer;

typedef enum e_input
{
	CMD,
	NOMAL_VAR,
	//SPACE,
	PIPE,
	D_QUOTE,
	S_QUOTE,
	REDIRECT_IN,
	REDIRECT_OUT
}	t_input;

/* Functions */

int	ft_strcmp(char *s1, char *s2);

#endif


