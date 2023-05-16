/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:53:15 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/15 15:22:02 by mschaub          ###   ########.fr       */
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
# include "../../libft/libft.h"

# define BUFFER_SIZE 4000

/* Structs */

enum e_token
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

/* Functions */

t_shell *fill_shell(t_shell *shell);
void	print_shell(t_shell *s);
int	main();
void    ft_free(char **str);

char *new_node_SPACE(char *str, t_shell **shell, int c);
char *new_node_DW(char *str, t_shell **shell, int c);
char *new_node_PIPE(char *str, t_shell **shell, int c);
char *new_node_RED(char *str, t_shell **shell, int c);
char *new_node_NL_ESC(char *str, t_shell **shell, int c);
char *new_node_DSQ(char *str, t_shell **shell, int c);

//int	ft_strlen(char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

int ft_isspace(char c);
int ft_issignal(char c);




#endif
