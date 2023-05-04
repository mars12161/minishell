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

typedef struct s_shell
{
	char *input;
	int	len;
	enum e_token type;
	enum e_state state;
	s_shell *next;
}	t_shell;

typedef enum e_token
{
	WORD = -1,
	ENV = '$',
	//SPACE = ' ',
	PIPE = '|',
	D_QUOTE = '\"',
	S_QUOTE = '\'',
	NEW_LINE = '\n',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	ESC = '\\',
}

typedef enum e_state
{
	D_QUOTE,
	S_QUOTE,
	OTHER,
}

/* Functions */

int	ft_strcmp(char *s1, char *s2);
int	minishell_loop(void);

#endif
