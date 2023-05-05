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

# define BUFFER_SIZE 4000

/* Structs */

enum e_token
{
	WORD,
	ENV,
	PIPE,
	D_QUOTE,
	S_QUOTE,
	NEW_LINE,
	REDIRECT_IN,
	REDIRECT_OUT,
	ESCAPE,
};

enum e_state
{
	IN_DQUOTE,
	IN_SQUOTE,
	OTHER,
};

typedef struct s_shell
{
	char *input;
	int	len;
	enum e_token type;
	enum e_state state;
	struct s_shell *next;
}	t_shell;

/* Functions */

int	ft_strlen(char *str);
char *split_line(char *str);
t_shell *fill_shell(t_shell *shell);
void	print_stack(t_shell *s);
int	main();

#endif
