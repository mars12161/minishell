/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:22:06 by mschaub           #+#    #+#             */
/*   Updated: 2023/06/12 11:22:32 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

/*
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
}   t_parse;

no redirection  0
REDIRECT_IN,	1
HEREDOC,	2

no redirection  0
REDIRECT_OUT,	1
APP_M		2

no pipe 0;
pipe 1;
*/

void excute_interagration(t_parse *parse, t_env **env, int fd_in, int fd_out)
{
    while (parse)
    {
        if (exec_builtin(parse, env) == 1)
		{
			if (parse->redirection_in)
			{
				redirection_in(t_parse *parse, int fd_in);
				close(fd_in);
			}
			if (parse->redirection_out)
			{
				redirection_in(t_parse *parse, int fd_out);
				close(ft_out);
			}
			ft_execute(parse, env);
		}   
        else if (exec_builtin(parse, env) == -1)
            return (-1);
        parse = parse->next;
    }
}

int ft_pipe(t_parse *parse, t_env **env)
{
    int pid1;
    int pid2;
    int fd_in;
    int fd_out;

    fd_in = 0;
    fd_out = 1;
    if (pipe(parse->fd))
        ft_error("pipe created failed");
    pid1 = fork();
    if (pid1 == -1)
        ft_error("child process creat failed");
    else if (pid1 == 0)
    {
        if (!parse->previous->pipe)
            excute_interagration(parse, env, fd_in, parse->fd);
        else
            excute_interagration(parse, env, parse->previous->fd, parse->fd);
    }
    pid2 = fork();
    if (pid2 == -1)
        ft_error("pipe created failed");
    else if (pid1 == 0)
    {
        if (!parse->next->pipe)
            excute_interagration(parse, env, parse->fd, fd_out);
        else
            excute_interagration(parse, env, parse->fd, parse->next->fd);
    }
    close(parse->fd[0]);
    close(parse->fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}