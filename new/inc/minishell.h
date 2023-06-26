/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschaub <mschaub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:53:15 by mschaub           #+#    #+#             */
/*   Updated: 2023/06/26 12:48:23 by mschaub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "../libft/libft.h"

# define PATH_SIZE 4096

//# define BUFFER_SIZE 4000

/* Structs */

extern int g_exit;

enum e_token
{
	WORD,		//0
	S_QUOTE,	//1
	D_QUOTE,	//2
	SPA,		//3
	ENV,		//4
	PIPE,		//5
	REDIRECT_IN,//6
	REDIRECT_OUT,//7
	HEREDOC,	//8
	APP_M,		//9
	INFILEPATH,
	OUTFILEPATH,
};

// enum e_state
// {
// 	OTHER,
// 	IN_SQUOTE,
// 	IN_DQUOTE,
// };

typedef struct s_shell
{
	char *input;
	int	len;
	enum e_token type;
	struct s_shell *pre;
	struct s_shell *next;
}	t_shell;

typedef struct s_parse
{
    char 	*command;
	char	**whole_line;
	int		wline_count;
    int	redirection_in;
    int	redirection_out;
    char *infilepath;  //if redirection_in == 0, infilepath = NULL
    char *outfilepath; //if redirection_out == 0, outfilepath = NULL
    int pipe;
    //int	fd[2];   //if pipe == 0, fd = NULL
}   t_parse;

typedef struct s_parse_arr
{
	t_parse **cmm;
	int	check;
	int	size;
}	t_parse_arr;

typedef struct s_env
{
    char *content;
    struct s_env *next;
}   t_env;

//debug
void	print_parse(t_parse	*head);
void	print_shell(t_shell *s);
void	print_parse_arr(t_parse_arr	*head);

//lexer_1
char *new_node_WORD(char *str, t_shell **shell);
t_shell *fill_shell(char *str, t_shell *shell, t_env **env);

//lexer_2
char *new_node_ENV(char *str, t_shell **shell, t_env **env);
char *new_node_PIPE(char *str, t_shell **shell);
char *new_node_RED_2(char *str, t_shell **shell, int c);
char *new_node_RED(char *str, t_shell **shell, int c);

//lexer_3
char *new_node_DQ(char *str, t_shell **shell, t_env **env);
char *new_node_SQ(char *str, t_shell **shell);

//lexer_4
int check_word_or_path(t_shell *shell);
void ft_add_tail(t_shell **shell, t_shell *new_node, enum e_token type);

//libft
/*int	ft_strlen(char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_setcheck(char c, char const *set);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);*/

//parser_1
t_parse	*parse_shell(t_shell *head, t_env *env);
t_parse_arr *parse_array_create(t_shell *head,t_env *env);

//parser_2
void	parse_redir_out(t_parse *cmm, t_shell *temp);
void	parse_redir_out_app(t_parse *cmm, t_shell *temp);
void	parse_delim(t_parse *cmm, t_env *env, t_shell *temp);
void	parse_redir_in(t_parse *cmm, t_shell *temp);

//parser_3
void	check_infile(char *infilepath);
int	args_count(t_shell *head);
int	get_size_cmmarr(t_shell *head);

//expand
char    *ft_expand(char *str, t_env **env);

//env
t_env *new_node_env(char *str);
void ft_add_tail_env(t_env **env, t_env *new_node);
t_env *init_env(char **envp, t_env *env);

//free_1
void    free_all(t_shell **shell, t_parse *node, t_env **env);
void    free_shell(t_shell **shell);
void    ft_free_str(char **str);

//free_2
void ft_free_3str(char *str1, char *str2, char *str3);

//buildin_1
int check_buildin(char *str);
int   ft_redirection_out(t_parse *node);
int    buildin_easy_mode(t_shell **shell, t_parse_arr *cmmarr, t_env *env);

//buildin 2 3 4 5 6 7 8
int	ft_echo(t_parse *node);
int ft_export(t_parse *node, t_env **env);
int ft_cd(t_parse *node, t_env **env);
int ft_exit(void);
int ft_pwd(t_parse *node);
int ft_unset(t_parse *node, t_env **env);
int ft_env(t_parse *node, t_env **env);

//error
void    ft_error(char *str);

//parse_multi_env_1
char *ft_parse_dollar_frame(char *str, t_env *env);

//parse_multi_env_2
int check_dollar(char *str, int c);
int ft_count_size(char *str, int c);
char *ft_check_strjoin(char *s1, char *s2);
int  check_path_char(int c);

//signals
void	sigint_handler(int sig);
void	setting_signal(void);
int	change_attr(bool ctrl_chr);

#endif
