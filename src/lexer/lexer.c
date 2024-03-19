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


char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		parser(char **lexer_tokens);



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

bool	is_onstr(char *str, char *set)
{
	int	i;

	while (str && *str)
	{
		i = 0;
		while (set && set[i])
		{
			if (*str == set[i])
				return (true);
			i++;
		}
		str++;
	}
	return (false);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*ptr != '\0')
		ptr++;
	while (*src != '\0')
		*ptr++ = *src++;
	*ptr = '\0';
	return (ptr);
}

// char	**adjust_tokens(char **lexer_tokens)
// {
// 	char	**adjusted;
// 	int		adjusted_size;
// 	int		i;

// 	adjusted_size = 50;
// 	adjusted = malloc(adjusted_size + 1, sizeof(*adjusted));
// 	if(adjusted == NULL)
// 		return (NULL);

// 	return (0);
// }

// int	token_join_quotes(char ***lexer_tokens, int i)
// {
// 	char	*joined;
// 	char	*tmp;
// 	int		j;

// 	joined = NULL;
// 	j = i;
// 	while ((*lexer_tokens)[j] && is_onstr(((*lexer_tokens)[j]), "\"\'"))
// 	{
// 		tmp = ft_strjoin(joined, (*lexer_tokens)[j]);
// 		if (tmp == NULL)
// 			return (0);
// 		free(joined);
// 		joined = tmp;
// 		j++;
// 	}
// 	if (joined == NULL)
// 		return (1);
// 	(*lexer_tokens)[i] = joined;
// 	while ((*lexer_tokens)[j])
// 	{
// 		(*lexer_tokens)[j] = (*lexer_tokens)[j + 1];
// 		j++;
// 	}
// 	return (1);
// }

// int	join_quotes(char ***lexer_tokens)
// {
// 	int	i;

// 	i = 0;
// 	if (*lexer_tokens == NULL)
// 		return (0);

// 	while ((*lexer_tokens)[i])
// 	{
// 		if ((*lexer_tokens[i] && is_onstr(*lexer_tokens[i], "\"\'")))
// 		{
// 			if (token_join_quotes(lexer_tokens, i) == 0)
// 				return (0);
// 			else
// 				if (is_onstr(*lexer_tokens[i], "\"\'") == false)
// 					i += 2;
// 		}
// 		else
// 			i++;
// 	}
// 	return (1);
// }

char	*join_tokens(char **tokens, int start, int end)
{
	char	*joined_token;
	int		i;

	joined_token = ft_strdup(tokens[start]);
	i = start + 1;
	while (i <= end)
	{
		joined_token = realloc(joined_token, ft_strlen(joined_token) + ft_strlen(tokens[i]) + 2);
		ft_strcat(joined_token, " ");
		ft_strcat(joined_token, tokens[i]);
		i++;
	}
	return (joined_token);
}

int	handle_quotes(char **lexer_tokens, char **joined_tokens, int i, int *j)
{
	int		start;
	char	quote_char;

	quote_char = lexer_tokens[i][0];
	start = i;
	while (lexer_tokens[i] != NULL && lexer_tokens[i][ft_strlen(lexer_tokens[i]) - 1] != quote_char)
		i++;
	if (lexer_tokens[i] != NULL)
	{
		joined_tokens[*j] = join_tokens(lexer_tokens, start, i);
		(*j)++;
	}
	return (i);
}

char	**join_quotes(char **lexer_tokens)
{
	char	**joined_tokens;
	int		i;
	int		j;

	joined_tokens = malloc(MAX_TOKENS * sizeof(char *));
	i = 0;
	j = 0;
	while (lexer_tokens[i] != NULL)
	{
		if (lexer_tokens[i][0] == '\'' || lexer_tokens[i][0] == '\"')
		{
			i = handle_quotes(lexer_tokens, joined_tokens, i, &j);
			i++;
		}
		else
		{
			joined_tokens[j] = strdup(lexer_tokens[i]);
			j++;
			i++;
		}
	}
	joined_tokens[j] = NULL;
	free(lexer_tokens);
	return (joined_tokens);
}

char	**get_tokens(char *input)
{
	char	**lexer_tokens;
	int		i;
	int		j;
	int		len;

	lexer_tokens = malloc(MAX_TOKENS * sizeof(char *));
	i = 0;
	j = 0;
	len = 0;
	while (input[i])
	{
		while (input[i] == ' ' && input[i] != '\0')
			i++;
		len = 0;
		while (input[i + len] != ' ' && input[i + len] != '\0')
			len++;
		lexer_tokens[j] = ft_substr(input, i, len);
		i += len;
		printf("lexer_tokens[%d] = %s\n", j, lexer_tokens[j]);
		j++;
	}
	lexer_tokens[j] = NULL;
	return (lexer_tokens);
}

char	**lexer(char *input)
{
	char	**lexer_tokens;
	int		exit_status;

	lexer_tokens = get_tokens(input);
	lexer_tokens = join_quotes(lexer_tokens);
	exit_status = parser(lexer_tokens);
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
