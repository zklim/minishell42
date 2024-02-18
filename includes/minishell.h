/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:36:22 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/19 02:27:12 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "executions/execve.h"
# include "executions/builtins/echo.h"
# include "executions/builtins/pwd.h"
# include "executions/builtins/cd.h"
# include "executions/builtins/export.h"
# include "executions/builtins/env.h"
# include "executions/builtins/unset.h"
# include "utils/build_shell.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include "utils/build_shell.h"
# include "executions/execve.h"
# include "executions/builtins/cd.h"
# include "executions/builtins/echo.h"
# include "executions/builtins/env.h"
# include "executions/builtins/export.h"
# include "executions/builtins/export2.h"
# include "executions/builtins/pwd.h"
# include "executions/builtins/unset.h"

# define SUCCESS 0
# define FAILURE -1
# define OPERATORS "|<>"
# define QUOTES "\"\'"
# define DELIMS "\"\' "
# define REDIRECTS "><"

# define CL_ARGUMENTS_ERR "minishell: no support for command-line arguments"
# define NO_PIPE_PROMPT "minishell: no support for pipe prompt"
# define NO_SYTX_PROMPT "minishell: no support for syntax prompt"
# define PIPE_ERR "minishell: pipe() failed"
# define FORK_ERR "minishell: fork() failed"

# define UNCLOSED_QUOTES "minishell: unclosed quotes"
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `"
# define SYTX_ERR_RDR "minishell: syntax error near unexpected token `newline'"

typedef enum s_token
{
	NONE,
	RDR_OUT_REPLACE,
	RDR_OUT_APPEND,
	RDR_INPUT,
	RDR_INPUT_UNTIL,
	PIPE,
}	t_token;

typedef struct s_statement
{
	int					argc;
	char				**argv;
	t_token				token;
	struct s_statement	*next;
}				t_statement;

typedef struct s_vlst
{
	char			*var_name;
	char			*var_value;
	bool			is_exported;
	struct s_vlst	*next;
}				t_vlst;

typedef struct s_data
{
	char		**envp;
	t_vlst		*envp_vlst;
	t_statement	**head;
}				t_data;

void		cmd_binaries(t_statement *statement, t_data *data);
void		exec_executables(t_statement *node, t_data *data);
void		exec_pipe(t_statement *node, t_data *data);
void		exec_redirects(t_statement *node, t_data *data);
bool		is_valid_id(char *str);
bool		builtin(t_statement *s, t_data *data);
// Expander Utils
void		init_vars(size_t *i, size_t *size, bool *in_quotes,
				bool *in_dquotes);
size_t		exit_status_size(void);
size_t		expand_size(char *input_at_i, size_t *i, t_data *data);
int			expanded_size(char *input, t_data *data);
// Expander
size_t		expand_exit_status(char *expanded_input_at_i, size_t *i);
size_t		expand_variable(char *expanded_input_at_i, char *input,
				size_t *i, t_data *data);
char		*expander(char *input, t_data *data);
// Invalid_syntax
bool		has_operator(char *input);
bool		check_operator(char *input, size_t *i, bool in_quotes);
bool		invalid_syntax_on_operator(char *input);
bool		invalid_syntax2(char *input);
bool		invalid_syntax(char *input);
// Parser Utils
int			is_whitespace(char c);
t_token		get_token(char *token);
int			get_argc(char **argv);
int			get_token_len(char *str);
int			get_num_statements(char *input);
// Parser
char		**parse_input(char *input);
t_statement	*process_command(char **parsed, size_t *command_index,
				t_statement *current);
t_statement	*parser(char *input);
// Remove_quotes
int			unclosed_quotes(char *str);
char		*remove_quotes(char	*parsed);
// Utils
// Linked List
// P_list_utils
void		p_lstclear(t_statement **head);
size_t		p_lstsize(t_statement *head);
t_statement	*p_new_node(int argc);
// V_list_utils
size_t		v_lstsize_exported(t_vlst **head);
bool		get_exported_state(char *var_name, t_vlst **head);
char		**split_envp(char *env);
int			save_user_vars(char *statement, t_vlst **head, bool to_export);
// V_list_utils2
char		*get_varvalue_fromvlst(char *var_name, t_data *data);
char		*get_fromvlst(char *var_name, t_vlst **head);
t_vlst		*v_new_node(char *var_name, char *var_value, bool is_exported);
t_vlst		*v_lstlast(t_vlst *node);
void		v_lstadd_back(t_vlst **head, t_vlst *new);
// Destroy
void		v_lstclear(t_vlst **head);
void		destroy(t_data *data);
// init_envp_lst
t_vlst		*init_envp_lst(char **envp);
// is_all_digits_or_signal
bool		is_all_digits_or_signals(char *str);
// other_tools
bool		is_onstr(const char *str, int ch);
bool		streq(char *str1, char *str2);
bool		unexpected_token(char token);
// Panic
void		panic(t_data *data, char *error_msg, int exit_status);
// Valid_input
bool		valid_input(char *input, t_data *data);
// Main
void		child_signals(int signum);
void		dismiss_signal(int signum);
void		config_signals(void);
void		setup_shell(char **envp, t_data *data,
				t_statement **statement_list);



#endif