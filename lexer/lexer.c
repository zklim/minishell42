/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:30:06 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/24 13:30:06 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define OPERATORS "|><"
#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 50

char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//Handle_quotes should go through the string and handle quotes
// 1. If it finds a quote, it should go through the string and find the next quote
// 2. It should then return the string between the quotes


typedef enum s_token
{
	NONE,
	PIPE,
	RDR_OUT_APPEND,
	RDR_OUT_REPLACE,
	RDR_INPUT_UNTIL,
	RDR_INPUT
}	t_token;

char	**ft_split(char const *s, char c);

bool	streq(char *str1, char *str2)
{
	size_t	i;

	if ((str1 && !str2) || (!str1 && str2))
		return (false);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (false);
		i += 1;
	}
	return (true);
}

bool	is_onstr(const char *str, int ch)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return (true);
		i += 1;
	}
	return (false);
}

int skip_blankspace(char *lexer_tokens, int i)
{
	int	*j;
	while (lexer_tokens[i] == ' ')
	{
		i++;
		(*j)++;
	}
	return (*j);
}

char	**lexer(char *input)
{
	char	**lexer_tokens;
	int		i;
	int		j;
	int		k;

	lexer_tokens = malloc(MAX_TOKENS * sizeof(char *));
	i = 0;
	j = 0;
	k = 0;
	lexer_tokens[i] = malloc(MAX_TOKEN_LEN * sizeof(char));
	while (1)
	{
		if (input[j] == ' ' || input[j] == '\0')
		{
			lexer_tokens[i][k] = '\0';
			i++;
			lexer_tokens[i] = malloc(MAX_TOKEN_LEN * sizeof(char));
			k = 0;
		}
		else
		{
			lexer_tokens[i][k] = input[j];
			k++;
		}
		if (input[j] == '\0')
			break ;
		j++;
	}
	lexer_tokens[i] = NULL;
	return (lexer_tokens);
}

// int main() {
// 	char input[256];
// 	printf("Enter a command: ");
// 	fgets(input, 256, stdin);
// 	input[strcspn(input, "\n")] = 0;  // Remove trailing newline

// 	char **lexer_tokens = lexer(input);

// 	for (int i = 0; lexer_tokens[i] != NULL; i++) {
// 		printf("lex_token[%d] = %s\n", i, lexer_tokens[i]);
// 	}

// 	// Free the allocated memory
// 	for (int i = 0; lexer_tokens[i] != NULL; i++) {
// 		free(lexer_tokens[i]);
// 	}
// 	free(lexer_tokens);

// 	return 0;
// }

// This is a "part of" me. 
// This
// is
// a
// "part of" 
// me.
