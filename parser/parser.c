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

typedef enum e_token_type
{
	NONE,
	TOKEN_COMMAND,
	TOKEN_PIPE,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_REPLACE,
	TOKEN_REDIRECT_INPUT_UNTIL,
	TOKEN_REDIRECT_INPUT,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

char	**lexer(char *input);

typedef struct s_parser_token
{
	char		*command;
	char		**args;
	t_token		*redirects;
}				t_parser_token;

void	redirect_token_types(t_token *tokens, int num_tokens)
{
	int	i;

	i = 0;
	while (i < num_tokens)
	{
		if (strcmp(tokens[i].value, "|") == 0)
			tokens[i].type = TOKEN_PIPE;
		else if (strcmp(tokens[i].value, "<") == 0)
		{
			if (strcmp(tokens[i + 1].value, "<") == 0)
			{
				tokens[i].type = TOKEN_REDIRECT_INPUT_UNTIL;
				i++;
			}
			else
				tokens[i].type = TOKEN_REDIRECT_INPUT;
		}
		else if (strcmp(tokens[i].value, ">") == 0)
		{
			if (strcmp(tokens[i + 1].value, ">") == 0)
			{
				tokens[i].type = TOKEN_REDIRECT_APPEND;
				i++;
			}
			else
				tokens[i].type = TOKEN_REDIRECT_REPLACE;
		}
		else
			tokens[i].type = TOKEN_COMMAND;
		i++;
	}
}

t_parser_token	*parser(char **lexer_tokens)
{
	t_parser_token	*parser_tokens;
	int				i;

	parser_tokens = malloc(MAX_TOKENS * sizeof(t_parser_token));
	i = 0;
	while (lexer_tokens[i] != NULL)
	{
		parser_tokens[i].command = lexer_tokens[i];
		parser_tokens[i].args = &lexer_tokens[i + 1];
		while (lexer_tokens[i] != NULL && strcmp(lexer_tokens[i], "|") != 0
			&& strcmp(lexer_tokens[i], ">") != 0
			&& strcmp(lexer_tokens[i], ">>") != 0
			&& strcmp(lexer_tokens[i], "<") != 0
			&& strcmp(lexer_tokens[i], "<<") != 0)
		{
			redirect_token_types(parser_tokens[i].redirects, MAX_TOKENS);
			i++;
		}
		if (lexer_tokens[i] != NULL)
			lexer_tokens[i] = NULL;
		i++;
	}
	return (parser_tokens);
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
