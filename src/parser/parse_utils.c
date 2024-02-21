/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 01:18:47 by cocheong          #+#    #+#             */
/*   Updated: 2024/01/20 01:18:47 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

t_token	get_token(char *token)
{
	t_token	op;

	if (!token)
		op = NONE;
	else if (streq(token, "|"))
		printf("PIPE\n");
		// op = PIPE;
	else if (streq(token, ">>"))
		// op = RDR_OUT_APPEND;
		printf("RDR_OUT_APPEND\n");
	else if (streq(token, ">"))
		printf("RDR_OUT_REPLACE\n");
		// op = RDR_OUT_REPLACE;
	else if (streq(token, "<<"))
		printf("RDR_INPUT_UNTIL\n");
		// op = RDR_INPUT_UNTIL;
	else if (streq(token, "<"))
		printf("RDR_INPUT\n");
		// op = RDR_INPUT;
	else
		op = NONE;
	free(token);
	return (op);
}

int	get_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

// Function to get the length of a token in a string
int	get_token_len(char *str)
{
	int		i;
	char	quotes;

	i = 0;
	// If the first character is an operator, return the length of the operator
	if (is_onstr(OPERATORS, str[i]))
	{
		if (str[i] == str[i + 1])
			return (2);
		return (1);
	}
	// Loop through the string until we find a whitespace or an operator
	while (str[i] && !is_whitespace(str[i]) && !is_onstr(OPERATORS, str[i]))
	{
		// If the current character is a quote, skip to the matching closing quote
		if (str[i] == 34 || str[i] == 39)
		{
			quotes = str[i];
			while (str[i] && str[i] != quotes)
				i++;
			i++;
		}
		i++;
	}
	return (i);
}

// Function to get the number of statements in an input string
int	get_num_statements(char *input)
{
	int		count;
	bool	quotes;
	bool	flag;

	count = 0;
	flag = false;
	quotes = false;
	// Loop through the input string
	while (*input)
	{
		// If the current character is an operator, increment the count
		if (is_onstr(OPERATORS, *input))
			count++;
		// If the current character is a quote, toggle the quotes flag
		if (is_onstr(QUOTES, *input))
			quotes = !quotes;
		else if (is_onstr(QUOTES, *input) && *input == *(input + 1))
			input++;
		// If the current character is not a whitespace or an operator and we are not inside quotes, increment the count
		if (*input != ' ' && !is_onstr(OPERATORS, *input) && !flag && !quotes)
		{
			flag = true;
			count++;
		}
		// If the current character is a whitespace or an operator, reset the flag
		else if (*input == ' ' || is_onstr(OPERATORS, *input))
			flag = false;
		input++;
	}
	return (count);
}