/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:08:05 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/22 12:08:05 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 50

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strstr(const char *s, const char *to_find);
int		ft_strcmp(const char *s1, const char *s2);
char	**lexer(char *input);
// int	executor(t_parser_token **parser_tokens);

typedef enum e_token_type
{
	TOKEN_COMMAND = 0,
	TOKEN_PIPE = 1,
	TOKEN_REDIRECT_APPEND = 2,
	TOKEN_REDIRECT_REPLACE = 3,
	TOKEN_REDIRECT_INPUT_UNTIL = 4,
	TOKEN_REDIRECT_INPUT = 5,
}	t_token_type;

typedef struct s_executor_token
{
	char	**cmd;
	int		in;
	int		out;
	bool	is_pipe;
}				t_executor_token;

typedef struct s_parser_token
{
	t_token_type		redirect;
	char				**args;
}				t_parser_token;

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	printf("%s\n", cwd);
	free(cwd);
}

char	*ft_strstr(const char *s, const char *to_find)
{
	int	i;

	if (ft_strlen(to_find) == 0)
		return ((char *)s);
	i = 0;
	while (s && *s)
	{
		if (*s == *to_find)
		{
			i = 0;
			while (s[i] == to_find[i] && s[i])
				i++;
			if (i == ft_strlen(to_find))
				return ((char *)s);
		}
		s++;
	}
	return (0);
}

int	get_token_type(char *token)
{
	if (token == NULL)
		return (0);
	if (ft_strlen(token) == 1)
	{
		if (ft_strchr(token, '|'))
			return (TOKEN_PIPE);
		else if (ft_strchr(token, '<'))
			return (TOKEN_REDIRECT_INPUT);
		else if (ft_strchr(token, '>'))
			return (TOKEN_REDIRECT_REPLACE);
	}
	if (ft_strlen(token) == 2 && ft_strstr(token, "<<"))
		return (TOKEN_REDIRECT_INPUT_UNTIL);
	if (ft_strlen(token) == 2 && ft_strstr(token, ">>"))
		return (TOKEN_REDIRECT_APPEND);
	return (0);
}

static int	is_command(char *arg)
{
	int		i;
	char	*commands[8];

	commands[0] = "echo";
	commands[1] = "pwd";
	commands[2] = "unset";
	commands[3] = "cd";
	commands[4] = "env";
	commands[5] = "exit";
	commands[6] = "export";
	commands[7] = NULL;
	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(arg, commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	set_token_type(t_parser_token *parser_token, char *lexer_token)
{
	if (is_command(lexer_token) == 1)
		parser_token->redirect = TOKEN_COMMAND;
	else if (get_token_type(lexer_token) == TOKEN_PIPE)
		parser_token->redirect = TOKEN_PIPE;
	else if (get_token_type(lexer_token) == TOKEN_REDIRECT_APPEND)
		parser_token->redirect = TOKEN_REDIRECT_APPEND;
	else if (get_token_type(lexer_token) == TOKEN_REDIRECT_REPLACE)
		parser_token->redirect = TOKEN_REDIRECT_REPLACE;
	else if (get_token_type(lexer_token) == TOKEN_REDIRECT_INPUT_UNTIL)
		parser_token->redirect = TOKEN_REDIRECT_INPUT_UNTIL;
	else if (get_token_type(lexer_token) == TOKEN_REDIRECT_INPUT)
		parser_token->redirect = TOKEN_REDIRECT_INPUT;
}

int	is_redir_token(t_token_type token)
{
	if (token == TOKEN_REDIRECT_APPEND || token == TOKEN_REDIRECT_REPLACE
		|| token == TOKEN_REDIRECT_INPUT_UNTIL || token == TOKEN_REDIRECT_INPUT)
		return (1);
	return (0);
}

void	free_executor_tokens(t_executor_token **executor_tokens)
{
	int	i;

	i = 0;
	while (executor_tokens[i])
	{
		free(executor_tokens[i]);
		i++;
	}
	free(executor_tokens);
}

void get_executor_tokens(t_parser_token **parser_tokens, t_executor_token **executor_token)
{
	int	i[2];
	int	c_i;

	i[0] = 0;
	i[1] = 0;
	c_i = 0;
	while (parser_tokens[i[0]] != NULL)
	{
		if (parser_tokens[i[0]]->redirect == TOKEN_COMMAND)
		{
			executor_token[i[1]]->cmd[c_i] = ft_strdup(*parser_tokens[i[0]]->args);
			if (!executor_token[i[1]]->cmd[c_i])
			{
				free_executor_tokens(executor_token);
				return ;
			}
			c_i++;
		}
		else if (is_redir_token(parser_tokens[i[0]]->redirect))
		{
			//do redirect command
		}
		else if (parser_tokens[i[0]]->redirect == TOKEN_PIPE)
		{
			//do pipe command
			executor_token[i[1]]->cmd[c_i] = NULL;
			i[1]++;
			c_i = 0;
		}
		i[0]++;
	}
	executor_token[i[1]]->cmd[c_i] = NULL;
}

void execute_tokens(t_executor_token **executor_token)
{
	int		i;

	i = 0;
	while (*executor_token[i]->cmd != NULL)
	{
		if (ft_strcmp(executor_token[i]->cmd[0]++, "cd") == 0)
			ft_cd(executor_token[i]->cmd);
		if (ft_strcmp(*executor_token[i]->cmd[0], "echo") == 0)
			ft_echo(executor_token[i]->cmd);
		if (ft_strcmp(*executor_token[i]->cmd[0], "env") == 0)
			ft_env();
		if (ft_strcmp(*executor_token[i]->cmd[0], "export") == 0)
			ft_export(executor_token[i]->cmd);
		if (ft_strcmp(executor_token[i]->cmd[0], "pwd") == 0)
			ft_pwd();
		if (ft_strcmp(*executor_token[i]->cmd[0], "unset") == 0)
			ft_unset(executor_token[i]->cmd);
		if (ft_strcmp(*executor_token[i]->cmd[0], "exit") == 0)
			ft_exit(executor_token[i]->cmd);
		i++;
	}
}

t_executor_token	**allocate_executor_tokens(t_parser_token **parser_tokens)
{
	t_executor_token	**executor_tokens;
	int					i;

	executor_tokens = malloc(MAX_TOKENS * sizeof(t_executor_token *));
	i = 0;
	while (parser_tokens[i] != NULL)
	{
		executor_tokens[i] = malloc(sizeof(t_executor_token));
		executor_tokens[i]->cmd = malloc(MAX_TOKENS * sizeof(char *));
		if (!executor_tokens[i] || !executor_tokens[i]->cmd)
		{
			free_executor_tokens(executor_tokens);
			return (NULL);
		}
		i++;
	}
	return (executor_tokens);
}

int	executor(t_parser_token **parser_tokens)
{
	t_executor_token	**executor_tokens;
	int					i;
	int					exit_status;

	executor_tokens = allocate_executor_tokens(parser_tokens);
	if (!executor_tokens)
		return (-1);
	get_executor_tokens(parser_tokens, executor_tokens);
	execute_tokens(executor_tokens);
	free_executor_tokens(executor_tokens);
	free(parser_tokens);
	return (0);
}

int	parser(char **lexer_tokens)
{
	t_parser_token	**parser_tokens;
	int				i;
	int				exit_status;

	parser_tokens = malloc(MAX_TOKENS * sizeof(t_parser_token *));
	i = 0;
	while (lexer_tokens[i] != NULL)
	{
		parser_tokens[i] = malloc(sizeof(t_parser_token));
		parser_tokens[i]->args = malloc(sizeof(char *));
		*parser_tokens[i]->args = ft_strdup(lexer_tokens[i]);
		set_token_type(parser_tokens[i], lexer_tokens[i]);
		printf("parser_tokens[%d] = %s\n", i, *parser_tokens[i]->args);
		printf("parser_tokens[%d] = %d\n", i, parser_tokens[i]->redirect);
		i++;
	}
	exit_status = executor(parser_tokens);
	free(lexer_tokens);
	return (0);
}
