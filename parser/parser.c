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

#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 50

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strstr(const char *s, const char *to_find);



typedef enum e_token_type
{
	TOKEN_COMMAND = 0,
	TOKEN_PIPE = 1,
	TOKEN_REDIRECT_APPEND = 2,
	TOKEN_REDIRECT_REPLACE = 3,
	TOKEN_REDIRECT_INPUT_UNTIL = 4,
	TOKEN_REDIRECT_INPUT = 5,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef enum e_parser_token_type
{
	std = 0,
	subshell = 1
}	t_pars_tok_type;

char	**lexer(char *input);

typedef struct s_parser_token
{
	t_pars_tok_type		type;
	t_token_type		redirect[6];
	char				**command;
	char				**args;
}				t_parser_token;

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
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
	char	*commands[] = {"echo", "pwd", "unset", "cd", "env", "exit", "export", NULL};

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(arg, commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	parser(char **lexer_tokens)
{
	t_parser_token	**parser_tokens;
	int				i;

	parser_tokens = malloc(MAX_TOKENS * sizeof(t_parser_token *));
	i = 0;
	while (lexer_tokens[i] != NULL)
	{
		parser_tokens[i] = malloc(sizeof(t_parser_token));
		parser_tokens[i]->args = malloc(sizeof(char *));
		*parser_tokens[i]->args = ft_strdup(lexer_tokens[i]);
		if (is_command(lexer_tokens[i]) == 1)
			parser_tokens[i]->type = TOKEN_COMMAND;
		else if (get_token_type(lexer_tokens[i]) == TOKEN_PIPE)
			parser_tokens[i]->type = TOKEN_PIPE;
		else if (get_token_type(lexer_tokens[i]) == TOKEN_REDIRECT_APPEND)
			parser_tokens[i]->type = TOKEN_REDIRECT_APPEND;
		else if (get_token_type(lexer_tokens[i]) == TOKEN_REDIRECT_REPLACE)
			parser_tokens[i]->type = TOKEN_REDIRECT_REPLACE;
		else if (get_token_type(lexer_tokens[i]) == TOKEN_REDIRECT_INPUT_UNTIL)
			parser_tokens[i]->type = TOKEN_REDIRECT_INPUT_UNTIL;
		else if (get_token_type(lexer_tokens[i]) == TOKEN_REDIRECT_INPUT)
			parser_tokens[i]->type = TOKEN_REDIRECT_INPUT;
		printf("parser_tokens[%d] = %s\n", i, *parser_tokens[i]->args);
		printf("parser_tokens[%d] = %d\n", i, parser_tokens[i]->type);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char			input[256];
// 	char			**lexer_tokens;
// 	t_parser_token	*parser_tokens;

// 	printf("Enter a command: ");
// 	fgets(input, 256, stdin);
// 	input[strcspn(input, "\n")] = 0;
// 	lexer_tokens = lexer(input);
// 	parser_tokens = parser(lexer_tokens);
// 	for (int i = 0; parser_tokens[i].command != NULL; i++)
// 	{
// 		printf("Command: %s\n", parser_tokens[i].command);
// 		printf("Arguments: ");
// 		for (int j = 0; parser_tokens[i].args[j] != NULL; j++)
// 			printf("%s ", parser_tokens[i].args[j]);
// 		printf("\n");
// 	}
// 	// ... (free memory)
// 	return (0);
// }
