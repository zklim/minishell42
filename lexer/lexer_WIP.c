/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 22:34:01 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/22 22:34:01 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_lexer
{
	char    **lexer_tokens;
	int		lexer_tokens_count;
}   t_lexer;

#include <stdlib.h>
#include <string.h>

// Stubs for missing functions
char    get_next_special(char *tmp)
{
	// Implementation goes here
	return ('\0');
}

size_t  get_next_token_size(char *tmp, char next_special)
{
	// Implementation goes here
	return (0);
}

char    *ft_substr(char *s, unsigned int start, size_t len)
{
	// Implementation goes here
	return (NULL);
}

void    *ft_free(void **ptr)
{
	// Implementation goes here
	return (NULL);
}

int     get_subshell_count(char *tokens[], int i)
{
	// Implementation goes here
	return (0);
}

char    *get_end_of_subshell(char *tokens[], int *i, char *subshell_token)
{
	// Implementation goes here
	return (NULL);
}

char    *ft_append(char **dest, char *src)
{
	// Implementation goes here
	return (NULL);
}

int     token_is_unadjusted(char *token)
{
	// Implementation goes here
	return (0);
}

char    **ft_str_arr_realloc(char **arr, size_t new_size)
{
	// Implementation goes here
	return (NULL);
}

void    ft_free_str_array(char ***arr)
{
	// Implementation goes here
}

int     is_valid_line_syntax(char *line)
{
	// Implementation goes here
	return (0);
}

int     exit_on_syntax_error()
{
	// Implementation goes here
	return (0);
}

char    **ft_split_set(char *s, char *set)
{
	// Implementation goes here
	return (NULL);
}

int     join_quotes(char ***tokens)
{
	// Implementation goes here
	return (0);
}

void    set_lex_toks(char **tokens)
{
	// Implementation goes here
}

int     is_valid_syntax(char **tokens)
{
	// Implementation goes here
	return (0);
}

int     parser(char **tokens)
{
	// Implementation goes here
	return (0);
}

void    ft_free_split(char **tokens)
{
	// Implementation goes here
}

void    reset_lex_toks()
{
	// Implementation goes here
}

// Existing functions
static char	*fetch_next_token(char **input_token)
{
	char	*new_token;
	char	*temp;
	char	special_char;
	int		i;

	temp = *input_token;
	special_char = get_next_special(temp);
	new_token = ft_calloc(get_next_token_size(temp, special_char) + 1, \
			sizeof(*new_token));
	if (new_token == NULL)
		return (NULL);
	index = 0;
	if (*temp == special_char)
		while (*temp && *temp == special_char)
			new_token[index++] = *temp++;
	else
		while (*temp && *temp != special_char)
			new_token[index++] = *temp++;
	temp = ft_substr(*input_token, index, ft_strlen(*input_token));
	if (*input_token == NULL)
	{
		free(new_token);
		return (NULL);
	}
	free(*input_token);
	*input_token = temp;
	return (new_token);
}

static char *get_subshell_token(char *tokens[], int *i)
{
	// Simplified implementation
	return (NULL);
}

static char	**modify_tokens(char **original_tokens)
{
	char	**modified;
	size_t	modified_size;
	int		i[2];

	modified_size = 50;
	modified = ft_calloc(modified_size + 1, sizeof(*modified));
	if (modified == NULL)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (original_tokens[i[0]])
	{
		if (original_tokens[i[0]][0] == '(')
			modified[i[1]] = get_subshell_token(original_tokens, &i[0]);
		else if (!token_is_unadjusted(original_tokens[i[0]]))
			modified[i[1]] = ft_strdup(original_tokens[i[0]++]);
		else
			modified[i[1]] = fetch_next_token(&original_tokens[i[0]]);
		if (modified[i[1]++] == NULL)
			return (free_tokens(original_tokens, modified));
		if ((size_t)i[1] == modified_size - 1)
			modified = ft_str_arr_realloc(modified, modified_size += 10);
	}
	ft_free_str_array(&original_tokens);
	return (modified);
}

int	lexer(char *line)
{
	char	**tokens;
	int		exit_status;

	tokens = ft_split(line, " ");
	if (tokens == NULL)
		return (NULL);
	tokens = modify_tokens(tokens);
	return (0);
}

int main()
{
	char *input = NULL;
	size_t len = 0;

	printf("Enter a command: ");
	getline(&input, &len, stdin);
	lexer(&input);
	return 0;
}
