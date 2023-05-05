/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:22:34 by mschaub           #+#    #+#             */
/*   Updated: 2023/05/02 13:59:59 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <readline/readline.h>

# define BUFFER_SIZE 4000

/* Structs */

enum e_token
{
	WORD,
	S_QUOTE,
	D_QUOTE,
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

/*
Struct to store all the commands
*/
typedef struct s_cmds
{
	char **cmd;

	struct s_cmds *next;
}	t_cmds;

typedef struct s_tools
{

}	t_parse;

/* Functions */

int	ft_strlen(char *str);
char *split_line(char *str);
t_shell *fill_shell(t_shell *shell);
void	print_shell(t_shell *s);
int	main();

#endif
