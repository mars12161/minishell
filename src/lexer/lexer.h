/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:53:15 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/08 16:53:15 by mschaub          ###   ########.fr       */
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

# define BUFFER_SIZE 4000

/* Structs */

enum e_token
{
	WORD,
	S_QUOTE,
	D_QUOTE,
	SPACE,
	ENV,
	PIPE,
	NEW_LINE,
	REDIRECT_IN,
	REDIRECT_OUT,
	ESCAPE,
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

char *split_line(char *str);
t_shell *fill_shell(t_shell *shell);
void	print_shell(t_shell *s);
int	main();
int ft_splittimes(char *str);
char **ft_split(char *str);
void    ft_free(char **str);

#endif
