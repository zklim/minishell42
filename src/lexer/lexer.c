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

// #include "../../includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LEN 50

char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		parser(char **lexer_tokens);
void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
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

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

char	*join_tokens(char **tokens, int start, int end)
{
	char	*joined_token;
	int		i;

	joined_token = ft_strdup(tokens[start]);
	i = start + 1;
	while (i <= end)
	{
		joined_token = ft_realloc(joined_token, \
			ft_strlen(joined_token) + ft_strlen(tokens[i]) + 2);
		ft_strcat(joined_token, " ");
		ft_strcat(joined_token, tokens[i]);
		i++;
	}
	return (joined_token);
}

int	ft_str_ends_with(char *str, char *end)
{
	int	str_len;
	int	end_len;

	if (!str || !end)
		return (0);
	str_len = ft_strlen(str);
	end_len = ft_strlen(end);
	if (end_len > str_len)
		return (0);
	return (ft_strcmp(&str[str_len - end_len], end) == 0);
}

void	remove_last_char(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0)
		str[len - 1] = '\0';
}

int	handle_quotes(char **lexer_tokens, char **joined_tokens, int i, int *j)
{
	char	*temp;
	char	*quote_type;

	if (lexer_tokens[i][0] == '\'')
		quote_type = "'";
	else
		quote_type = "\"";
	joined_tokens[*j] = ft_strdup(lexer_tokens[i] + 1);
	while (lexer_tokens[++i] && !ft_str_ends_with(lexer_tokens[i], quote_type))
	{
		temp = ft_strjoin(joined_tokens[*j], " ");
		free(joined_tokens[*j]);
		joined_tokens[*j] = ft_strjoin(temp, lexer_tokens[i]);
		free(temp);
	}
	if (lexer_tokens[i])
	{
		temp = ft_strjoin(joined_tokens[*j], " ");
		free(joined_tokens[*j]);
		joined_tokens[*j] = ft_strjoin(temp, lexer_tokens[i]);
		free(temp);
		remove_last_char(joined_tokens[*j]);
	}
	(*j)++;
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
			joined_tokens[j] = ft_strdup(lexer_tokens[i]);
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
