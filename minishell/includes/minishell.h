/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:30:59 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/19 19:36:30 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "minishell$ "

extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_BACKGROUND,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF
}								t_token_type;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	struct s_token				*next;
}								t_token;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}								t_redir_type;

typedef struct s_redir
{
	t_redir_type				type;
	char						*file;
	int							heredoc_fd;
	struct s_redir				*next;
}								t_redir;

typedef struct s_arg
{
	char						*val;
	struct s_arg				*next;
}								t_arg;

typedef struct s_cmd
{
	char						**av;
	t_redir						*redirs;
	struct s_cmd				*next;
}								t_cmd;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_BACKGROUND,
	NODE_SUBSHELL
}								t_node_type;

typedef struct s_ast
{
	t_node_type					type;
	t_cmd						*cmd;
	struct s_ast				*left;
	struct s_ast				*right;
}								t_ast;

typedef struct s_env
{
	char						*key;
	char						*value;
	int							is_set;
	struct s_env				*next;
}								t_env;

typedef struct s_shell
{
	t_env						*env;
	int							last_exit_status;
	int							stdin_backup;
	int							stdout_backup;
	int							syntax_error;
}								t_shell;

typedef struct s_heredoc_ctx
{
	char						*delimiter;
	int							fd;
	int							expand;
	int							eof_reached;
	t_shell						*shell;
}								t_heredoc_ctx;

/* Lexer functions */
t_token							*tokenize(char *input);
void							free_token(t_token *token);
void							free_tokens(t_token *tokens);
t_token							*new_token(t_token_type type, char *value);
void							add_token(t_token **tokens, t_token *new);
int								is_meta(char c);
char							*handle_quoted(char *input, int *i, char quote);
t_token							*handle_operator(char *input, int *i);
char							*join_markers(char *ret, char *part,
									char m_start, char m_end);

/* Parser functions */
t_cmd							*parse(t_token *tokens, t_shell *shell);
t_cmd							*parse_single_cmd(t_token **tokens,
									t_shell *shell);
void							free_cmds(t_cmd *cmds);
t_cmd							*new_cmd(void);
t_redir							*new_redir(t_redir_type type, char *file);
void							add_redir(t_cmd *cmd, t_redir *redir);
t_redir_type					token_to_redir_type(t_token_type type);
int								is_redir_token(t_token_type type);
int								is_ambiguous_redirect(char *filename);
int								parse_redir_token(t_token **tok, t_cmd *cmd,
									char **av, t_shell *sh);
int								count_args(t_token *tokens, t_shell *shell);
int								is_token_quoted(char *value);
char							*expand_tilde_token(char *value,
									t_shell *shell);
void							process_input(char *input, t_shell *shell);
int								handle_word_token(t_token **tokens, char **av,
									int *idx, t_shell *shell);

/* Arg Utils (New) */
t_arg							*new_arg(char *val);
void							add_arg(t_arg **head, t_arg *new);
void							free_arg_list(t_arg *head);
char							**arg_list_to_array(t_arg *head);
int								get_expanded_word_len(char *s);
int								add_split_args(t_arg **args, char *expanded);

/* AST functions */
t_ast							*parse_ast(t_token *tokens, t_shell *shell);
t_ast							*parse_ast_ptr(t_token **tokens,
									t_shell *shell);
t_ast							*new_ast_node(t_node_type type);
void							free_ast(t_ast *ast);
int								execute_ast(t_ast *ast, t_shell *shell);

/* Executor functions */
int								execute(t_cmd *cmds, t_shell *shell);
int								execute_subshell(t_ast *ast, t_shell *shell);
int								execute_cmd(t_cmd *cmd, t_shell *shell);
int								execute_pipeline(t_cmd *cmds, t_shell *shell);
char							*find_command_path(char *cmd, t_env *env);
void							setup_pipe_fds(int in_fd, int out_fd);
void							exec_in_child(t_cmd *cmd, t_shell *shell);
void							child_process(t_cmd *cmd, t_shell *shell,
									int in_fd, int out_fd);
int								get_out_fd(t_cmd *cur, int *pipe_fd);
void							close_pipe_fds(int *pipe_fd);
void							handle_command_not_found(char *cmd_name);
void							execute_external(t_cmd *cmd, t_shell *shell);
void							restore_std_fds(t_shell *shell);
int								handle_empty_cmd(t_cmd *cmd, t_shell *shell);
int								print_brace_error(int open);

/* Redirection functions */
int								setup_redirections(t_redir *redirs,
									t_shell *shell);
int								handle_heredoc(t_redir *redir, int quoted,
									t_shell *shell);
void							print_heredoc_warning(char *delimiter);

/* Builtin functions */
int								is_builtin(char *cmd);
int								execute_builtin(char **av, t_shell *shell);
int								builtin_echo(char **av);
int								builtin_cd(char **av, t_shell *shell);
int								builtin_pwd(void);
int								builtin_export(char **av, t_shell *shell);
int								builtin_unset(char **av, t_shell *shell);
int								builtin_env(char **av, t_shell *shell);
int								builtin_exit(char **av, t_shell *shell);

/* cd utils functions */
char							*get_home_path(t_shell *shell);
char							*get_oldpwd_path(t_shell *shell);
char							*resolve_parent_path(t_shell *shell);

/* Environment functions */
t_env							*init_env(char **envp);
void							free_env(t_env *env);
char							*get_env_value(t_env *env, char *key);
int								set_env_value(t_env **env, char *key,
									char *value);
int								declare_env(t_env **env, char *key);
int								unset_env_value(t_env **env, char *key);
char							**env_to_array(t_env *env);
t_env							*new_env_node(char *key, char *value);
void							add_env_to_list(t_env **env, t_env *new);
t_env							*process_env_line(char *line, t_env *env);

/* Expansion functions */
char							*expand_variables(char *str, t_shell *shell);
char							*remove_markers(char *str);
char							*get_var_name(char *str, int *len);
char							*expand_var(char *str, int *i, t_shell *shell);
char							*join_parts(char *s1, char *s2);

/* Signal functions */
void							setup_signals(void);
void							setup_heredoc_signals(void);
void							setup_child_signals(void);
void							setup_parent_wait_signals(void);
void							restore_parent_signals(void);

/* Utility functions */
char							*ft_strdup(const char *s);
char							*ft_strjoin(char const *s1, char const *s2);
char							**ft_split(char const *s, char c);
int								ft_strcmp(const char *s1, const char *s2);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
size_t							ft_strlen(const char *s);
char							*ft_strchr(const char *s, int c);
char							*ft_strrchr(const char *s, int c);
char							*ft_substr(char const *s, unsigned int start,
									size_t len);
int								ft_isspace(int c);
int								ft_atoi(const char *str);
int								ft_atoll(const char *s, long long *out);
void							*ft_calloc(size_t count, size_t size);

/* Error functions */
void							print_error(char *cmd, char *arg, char *msg);
void							exit_error(char *msg, int status);
void							print_heredoc_eof_error(char *delimiter);
void							print_syntax_error(char *token, t_shell *shell);
void							reset_syntax_error_flag(t_shell *shell);
int								has_syntax_error(t_shell *shell);

/* Free functions */
void							free_array(char **array);
void							free_cmd(t_cmd *cmd);

/* Parse redir utils functions */
char							*get_redir_str(t_token_type type);
char							*get_token_str(t_token_type type);

/* Parse AST utils functions */
int								is_operator_token(t_token_type type);
char							*get_op_token_str(t_token **tok);
t_ast							*parse_primary(t_token **tokens,
									t_shell *shell);
t_ast							*parse_binary_op(t_token **tok, t_shell *sh,
									t_token_type op);
int								check_initial_operator(t_token *tokens);

/* Export utils functions */
void							print_export_line(char *key, char *value);
int								is_valid_identifier(char *s);
void							print_export_error(char *arg);
int								count_env(t_env *env);
void							sort_env_array(t_env **arr, int count);

#endif
