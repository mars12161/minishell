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
    struct s_parse *next;
}   t_parse;

void ft_excute(t_parse *parse, t_env **env)
{
    while (parse)
    {
        if (exec_builtin(parse, env) == 1)
            dosomething
        parse = parse->next;
    }
}
