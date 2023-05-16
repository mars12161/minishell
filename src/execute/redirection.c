#include "builtin.h"
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


int redirection_out(t_parse *parse,int fd)
{
    if (access(outfilepath, F_OK) == 0 && access(outfilepath, W_OK))
    {
        ft_error("wrong outfile right");
        return (-1);
    }
    if (parse->redirection_out == 1)
        fd = open(outfilepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (parse->redirection_out == 2)
        fd = open(outfilepath, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd < 0)
    {
        ft_error("open outfile failed");
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
		ft_error("redirection_out failed");
    return (0);
}

int redirection_in(t_parse *parse, int fd)
{
    if (parse->redirection_in == 1)
    {
        if (access(infilepath, R_OK))
        {
            ft_error("wrong infilepath");
            return (-1);
        }
        fd = open(infilepath, O_RDONLY);
        if (dup2(fd, STDIN_FILENO) == -1)
        {
		    ft_error("dup2 failed");
            return (-1);
        }
        return (0);
    }
    else if (parse->redirection_in == 2)
        return (redirection_in_heredoc(parse));
    //else
    //    return (0);
}

redirection_in_heredoc(t_parse *parse)
{
    char *heredoc;

    heredoc = malloc(4048);
    if (!heredoc)
        return (NULL);
    while(1)
    {
        write(1, ">", 1);
    	while (bytes_read > 0)
	    {
		    bytes_read = read(fd, buffer, BUFFER_SIZE);
		    if (bytes_read == -1)
		    {
			    free(buffer);
			    free(wstr);
			    return (NULL);
		    }
		    buffer[bytes_read] = '\0';
		    wstr = ft_strjoin(wstr, buffer);
	    }
    }



}




t_redir_list	*parse_here_doc(t_redir_list *redir, char *arg, char **env)
{	
	char	*line;
	int		fd;

	fd = open("/tmp/.minishell_tmp",
			O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0666);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, arg, ft_strlen(arg)) == 0)
			break ;
		else
		{
			if (ft_strchr(line, '$') != -1)
				line = expand_env(line, env);
			write(fd, line, ft_strlen(line));
		}
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(arg);
	add_redir_tail(redir,
		new_redir_elem(ft_strdup("/tmp/.minishell_tmp"), HERE_DOC));
	close(fd);
	return (redir);
}

char	*expand_env(char *line, char **env)
{
	int		i;
	int		j;
	char	*value;
	char	res[1024];

	i = -1;
	value = NULL;
	while (line[++i] && line[i] != '$')
		res[i] = line[i];
	if (line[i] == '$')
	{
		line = line + i;
		value = get_expanded_value(&line, env);
		if (value)
		{
			j = 0;
			while (value[j])
				res[i++] = value[j++];
		}
	}
	while (*line)
		res[i++] = *(line++);
	res[i] = '\0';
	return (ft_strdup(res));
}
