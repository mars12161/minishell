/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:39:25 by mschaub           #+#    #+#             */
/*   Updated: 2023/07/24 10:10:19 by mschaub          ###   ########.fr       */
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
	EMPTY,
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
	int		size;
}	t_parse_arr;

typedef struct s_env
{
	char			*content;
	int				size;
	struct s_env	*next;
}	t_env;

/* Debug */
void		print_parse(t_parse	*head);
void		print_shell(t_shell *s);
void		print_parse_arr(t_parse_arr	*head);
void		print_env(t_env **env);

/* Lexer 1 */
char		*new_node_word(char *str, t_shell **shell, t_env **env);
t_shell		*fill_shell(char *str, t_shell *shell, t_env **env);
t_shell		*init_shell_node(void);

/* Lexer 2 */
char		*new_node_env(char *str, t_shell **shell, t_env **env);
char		*new_node_pipe(char *str, t_shell **shell);
char		*new_node_red_2(char *str, t_shell **shell, int c);
char		*new_node_red(char *str, t_shell **shell, int c);

/* Lexer 3 */
char		*new_node_dq(char *str, t_shell **shell, t_env **env);
char		*new_node_sq(char *str, t_shell **shell, t_env **env);
int			new_node_red_utils(char *str, int c);

/* Lexer 4 */
int			check_word_or_path(t_shell *shell);
void		ft_add_tail(t_shell **shell, t_shell *new_node, enum e_token type);

/* Lexer 5 */
int			ft_check_quote_in_word(char *str);
int			ft_i_start_from_sq(char *str, int pre);
int			ft_i_start_from_word(char *str, int pre);
int			ft_i_start_from_dq(char *str, int pre);

/* Lexer 6 */
char		*ft_parse_original_from_word(char *str, t_env **env);
char		*ft_parse_original_from_word_core(char *str, t_env **env,
				int signal, int size);

/* Lexer 7 */
int			ft_count_size_lexer(char *str, int c, int start);
char		*ft_parse_original_from_dq(char *str, t_env **env);
char		*ft_parse_original_from_sq(char *str, t_env **env);
int			ft_character_after_dollar(char *str);

/* Lexer 8 */
t_shell		*get_shell_bottom(t_shell *shell);
int			get_shell_size(t_shell *shell);
t_shell		*get_parse_bottom(t_shell *node);
int			ft_i_start_from_word_2(char *str, int pre);
char		*ft_parse_original_from_word_2(char *str, t_env **env,
				int c, int j);

/* Parser 1 */
t_parse_arr	*parse_array_create(t_shell *head, t_env *env);
t_parse		*parse_shell(t_shell *head, t_env *env);

/* Parser 2 */
char		*check_input(t_shell *temp);
void		parse_redir_out(t_parse *cmm, t_shell *temp);
void		parse_redir_out_app(t_parse *cmm, t_shell *temp);
char		*read_heredoc(t_env *env, char *delimiter);
void		parse_delim(t_parse *cmm, t_env *env, t_shell *temp);
char		*return_here(char *str);
void		check_delim(t_parse *cmm, t_env *env,
				char *delimiter, char *heredoc);

/* Parser 3 */
void		check_infile(char *infilepath);
int			args_count(t_shell *head);
int			get_size_cmmarr(t_shell *head);
void		parse_redir_in(t_parse *cmm, t_shell *temp);

/* Parser 4 */
t_parse		*parse_init(void);
char		**ft_shell_whole_line(t_shell *head);
int			ft_count_args(char **str);

/* Parse Multi Env 1 */
char		*ft_parse_dollar_frame(char *str, t_env *env, int signal);
char		*ft_parse_dollar_core(char *str, t_env *env, int signal);

/* Parse Multi Env 2 */
int			check_dollar(char *str, int c);
int			ft_count_size(char *str, int c);
char		*ft_check_strjoin(char *s1, char *s2);
int			check_path_char(int c);

/* Parse Multi Env 3 */
char		*check_path_valid_utils(char *str, t_env *env, int signal);
char		*ft_str_check_quote(char *path, t_env *env, int signal);
int			check_path_str(char *str);
char		*ft_parse_dollar_core_utils2(char *str2, char *str3,
				t_env *env, int signal);

/* Parse Multi Env 4 */
char		*ft_parse_dollar_frame_2(char *str);

/* Expand */
char		*ft_expand(char *str, t_env **env);
//char *ft_expand_valid_check(char *str, t_env **env);

/* Env */
t_env		*new_node_environ(char *str);
void		ft_add_tail_env(t_env **env, t_env *new_node);
t_env		*init_env(char **envp, t_env *env);
char		**ft_env_str(t_env *env);

/* Free 1 */
void		free_shell(t_shell **shell);
void		free_env(t_env **env);
void		free_all_in_loop(t_shell **shell, t_parse_arr *cmmarr, char *str);

/* Free 2 */
void		ft_free_3str(char *str1, char *str2, char *str3);
void		ft_free_str(char **str);

/* Builtins */
int			check_buildin(char *str);
int			exec_builtin(t_parse *node, t_env **env);
int			ft_redirection_out(t_parse *node);
int			buildin_easy_mode(t_shell **shell, t_parse_arr *cmmarr,
				t_env *env, char *str);
int			ft_strcmpn(char *str1, char *str2, int size);
int			ft_echo(t_parse *node, t_env **env);
int			ft_echo_help(t_parse *node, int fd);
int			ft_export(t_parse *node, t_env **env);
void		ft_export_name_check(char *str, t_env *env);
int			ft_check_signal_export(char *str);
void		export_loop(int i, t_parse *node, t_env **env, t_env *export);
int			ft_cd(t_parse *node, t_env **env);
int			ft_replace_oldpwd(char *str, t_env *env);
int			cd_env_loop(t_env **env, t_env *temp,
				char pwd[PATH_SIZE], char *str);
int			ft_exit(t_parse *node);
int			ft_pwd(t_parse *node);
void		ft_unset_core(char *str, t_env **env);
int			ft_unset(t_parse *node, t_env **env);
int			ft_env(t_parse *node, t_env **env);

/* Error */
void		ft_error(char *str);
void		ft_error_optimal(char *str, int exit);

/* Signals */
void		sigint_handler(int sig);
void		sigquit_handler(int sig);
void		sigint_heredoc(int sig);
void		sigint_process(int sig);
void		init_signals(void);

/*	Execute Easy Mode*/
int			execute_easy_mode(t_parse_arr *cmmarr, t_env *env);
void		builtin_exit(t_parse *node, t_env *env);
int			execute_exit(t_shell *shell, t_parse_arr *cmmarr,
				t_env *env, char *str);

/* Execute Pipe 1 */
void		init_pipex(t_parse_arr *cmmarr, t_env *env);

/* Execute Pipe 2 */
char		*ft_strjoin_path_cmd(char const *s1, char c, char const *s2);
void		ft_executer(char **whole_line, char **env);

/* Execute Redir */
void		redir_child(t_parse *node);
void		redir_parent(t_parse_arr *cmmarr);

/* Main Utils */
int			ft_check_readline_in_loop(void);
int			ft_empty_cmmarr(char *str, t_shell *shell);
int			err_heredoc(void);
#endif
