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
#include <stdlib.h>
#include <stdbool.h>

#define OPERATORS "|><"

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

typedef struct s_lexer
{
	char			*lexer_tokens;
	int				lexer_tokens_count;
	t_token			token;
	struct s_lexer	*next;
}	t_lexer;

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

t_token	get_token(char *token)
{
	t_token	op;

	if (!token)
		op = NONE;
	else if (streq(token, "|"))
		op = PIPE;
	else if (streq(token, ">>"))
		op = RDR_OUT_APPEND;
	else if (streq(token, ">"))
		op = RDR_OUT_REPLACE;
	else if (streq(token, "<<"))
		op = RDR_INPUT_UNTIL;
	else if (streq(token, "<"))
		op = RDR_INPUT;
	else
		op = NONE;
	free(token);
	return (op);
}

t_lexer	*init_lexer(t_lexer *lexer)
{
	lexer = malloc(sizeof(t_lexer));
	lexer->lexer_tokens = NULL;
	lexer->lexer_tokens_count = 0;
	lexer->token = NONE;
}

void	process_token(t_lexer *line, t_lexer *tokens,
	int *i, int *j)
{
	int	old_i;

	old_i = *i;
	if (line->lexer_tokens[*j] == ' ')
		(*j)++;
	tokens->lexer_tokens = ft_substr(line->lexer_tokens, *j, *i - *j);
	tokens->lexer_tokens_count++;
	tokens->next = malloc(sizeof(t_lexer));
	tokens = tokens->next;
	*j = old_i;
}

int	handle_quotes(char *lexer_tokens, int i)
{
	i++;
	if (lexer_tokens[i - 1] == '\"')
	{
		while (lexer_tokens[i] != '\"' && lexer_tokens[i] != '\0')
			i++;
	}
	else if (lexer_tokens[i - 1] == '\'')
	{
		while (lexer_tokens[i] != '\'' && lexer_tokens[i] != '\0')
			i++;
	}
	return (i);
}

int lexer(t_lexer *line)
{
	int i, j, counter;
	t_lexer *tokens, *head;

	i = j = counter = 0;
	tokens = malloc(sizeof(t_lexer));
	tokens->lexer_tokens_count = 0;
	tokens->next = NULL;
	head = tokens;

	while (line->lexer_tokens[i])
	{
		if (line->lexer_tokens[i] == '\"' || line->lexer_tokens[i] == '\'')
			i = handle_quotes(line->lexer_tokens, i);
		else if (line->lexer_tokens[i] == ' ' || line->lexer_tokens[i + 1] == '\0')
		{
			process_token(line, tokens, &i, &j);
			counter++;
			printf("%s %d\n", tokens->lexer_tokens, counter);
		}
		if (line->lexer_tokens[i] != '\0')
			i++;
	}
	return (0);
}


int main()
{
	t_lexer *input;
	size_t len = 0;

	init_lexer(input);
	printf("Enter a command: ");
	getline(&input->lexer_tokens, &len, stdin);
	printf("%s\n", input->lexer_tokens);
	lexer(input);
	printf("%s\n", input->lexer_tokens);
	return 0;
}

// This is a "part of" me. 
// This
// is
// a
// "part of" 
// me.
