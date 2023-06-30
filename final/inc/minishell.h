/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:53:15 by mschaub           #+#    #+#             */
/*   Updated: 2023/06/30 16:02:45 by mschaub          ###   ########.fr       */
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

/* Structs */

extern int	g_exit;

typedef struct	s_global
{
	int	in_heredoc;
	int g_exit;
}	t_global;

extern t_global globe;


enum e_token
{
	WORD,
	S_QUOTE,
	D_QUOTE,
	SPA,
	ENV,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APP_M,
	INFILEPATH,
	OUTFILEPATH,
};

typedef struct s_shell
{
	char			*input;
	int				len;
	enum e_token	type;
	struct s_shell	*pre;
	struct s_shell	*next;
}	t_shell;

typedef struct s_parse
{
	int		wline_count;
	int		redirection_in;
	int		redirection_out;
	int		pipe;
	char	*command;
	char	**whole_line;
	char	*infilepath;
	char	*outfilepath;
}	t_parse;

typedef struct s_parse_arr
{
	t_parse	**cmm;
	int		check;
	int		size;
}	t_parse_arr;

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

/* Debug */
void		print_parse(t_parse	*head);
void		print_shell(t_shell *s);
void		print_parse_arr(t_parse_arr	*head);

/* Lexer 1 */
char		*new_node_word(char *str, t_shell **shell, t_env **env);
t_shell		*fill_shell(char *str, t_shell *shell, t_env **env);

/* Lexer 2 */
char		*new_node_env(char *str, t_shell **shell, t_env **env);
char		*new_node_pipe(char *str, t_shell **shell);
char		*new_node_red_2(char *str, t_shell **shell, int c);
char		*new_node_red(char *str, t_shell **shell, int c);

/* Lexer 3 */
char		*new_node_dq(char *str, t_shell **shell, t_env **env);
char		*new_node_sq(char *str, t_shell **shell, t_env **env);

/* Lexer 4 */
int			check_word_or_path(t_shell *shell);
void		ft_add_tail(t_shell **shell, t_shell *new_node, enum e_token type);

/* Parser 1 */
t_parse		*parse_shell(t_shell *head, t_env *env);
t_parse_arr	*parse_array_create(t_shell *head, t_env *env);

/* Parser 2 */
void		parse_redir_out(t_parse *cmm, t_shell *temp);
void		parse_redir_out_app(t_parse *cmm, t_shell *temp);
char		*read_heredoc(t_env *env, char *delimiter);
void		parse_delim(t_parse *cmm, t_env *env, t_shell *temp);
void		parse_redir_in(t_parse *cmm, t_shell *temp);

/* Parser 3 */
void		check_infile(char *infilepath);
int			args_count(t_shell *head);
int			get_size_cmmarr(t_shell *head);

/* Parse Multi Env 1 */
char		*ft_parse_dollar_frame(char *str, t_env *env);

/* Parse Multi Env 2 */
int			check_dollar(char *str, int c);
int			ft_count_size(char *str, int c);
char		*ft_check_strjoin(char *s1, char *s2);
int			check_path_char(int c);

/* Expand */
char		*ft_expand(char *str, t_env **env);

/* Env */
t_env		*new_node_ENV(char *str);
void		ft_add_tail_env(t_env **env, t_env *new_node);
t_env		*init_env(char **envp, t_env *env);
int			get_env_size(t_env **env);
char		**ft_env_str(t_env **env);

/* Free 1 */
void		free_all(t_shell **shell, t_parse_arr *node, t_env **env);
void		free_shell(t_shell **shell);
void		ft_free_str(char **str);

/* Free 2 */
void		ft_free_3str(char *str1, char *str2, char *str3);

/* Builtins */
int			check_buildin(char *str);
int			exec_builtin(t_parse *node, t_env **env);
int			ft_redirection_out(t_parse *node);
int			buildin_easy_mode(t_shell **shell, t_parse_arr *cmmarr, t_env *env);
int			ft_echo(t_parse *node);
int			ft_export(t_parse *node, t_env **env);
int			ft_cd(t_parse *node, t_env **env);
int			ft_exit(void);
int			ft_pwd(t_parse *node);
int			ft_unset(t_parse *node, t_env **env);
int			ft_env(t_parse *node, t_env **env);

/* Error */
void		ft_error(char *str);

/* Signals */
void		sigint_handler(int sig);
void		setting_signal(void);
int			change_attr(bool ctrl_chr);

/* Execute Pipe 1 */
int			init_pipex(t_parse_arr *cmmarr, t_env *env);

/* Execute Pipe 2 */
void		builtin_exit(t_parse *node, t_env *env);
void		ft_executer(char **whole_line, char **env);
char		*str_ncpy(char *str, int n);
char		*ft_strjoin_path_cmd(char const *s1, char c, char const *s2);

/* Execute Redir */
void		redir_child(t_parse *node);
void		redir_parent(t_parse_arr *cmmarr);

#endif