/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:55:40 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/16 17:55:40 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	has_operator(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (is_onstr(OPERATORS, input[i]))
			return (true);
		i += 1;
	}
	return (false);
}

bool	check_operator(char *input, size_t *i, bool in_quotes)
{
	if (input[*i] == input[*i + 1])
		(*i) += 2;
	else
		(*i) += 1;
	if (input[*i] == ' ')
	{
		while (input[*i] && input[*i] == ' ')
			(*i) += 1;
		if (is_onstr(OPERATORS, input[*i]))
			return (unexpected_token(input[*i]));
	}
	if (is_onstr(OPERATORS, input[*i]))
		return (unexpected_token(input[*i]));
	return (false);
}

bool	invalid_syntax_on_operator(char *input)
{
	size_t	i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (has_operator(&input[i]))
	{
		if (is_onstr(QUOTES, input[i]))
			in_quotes = !in_quotes;
		if (is_onstr(OPERATORS, input[i]) && !in_quotes)
		{
			if (check_operator(input, &i, in_quotes))
				return (true);
		}
		i += 1;
	}
	return (false);
}

// Function to check for invalid syntax in a string
bool	invalid_syntax2(char *input)
{
	size_t	i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	// Loop through the input string
	while (input[i])
	{
		// If the current character is a quote, toggle the in_quotes flag
		if (is_onstr(QUOTES, input[i]))
			in_quotes = !in_quotes;
		// If the current character and the next one form an invalid operator and we are not inside quotes, return an error
		if (((input[i] == '>' && input[i + 1] == '<')
				|| (input[i] == '<' && input[i + 1] == '>')
				|| (input[i] == '|' && input[i + 1] == '|')) && !in_quotes)
			return (unexpected_token(input[i + 1]));
		// If the current character is an invalid character and we are not inside quotes, return an error
		else if ((input[i] == '{' || input[i] == '}'
				|| input[i] == '(' || input[i] == ')'
				|| input[i] == '[' || input[i] == ']'
				|| input[i] == ';' || input[i] == '&' || input[i] == '*')
			&& !in_quotes)
			return (unexpected_token(input[i]));
		i += 1;
	}
	// If there are no errors, return false
	return (false);
}

// Function to check for invalid syntax at the start and end of a string
bool	invalid_syntax(char *input)
{
	// If the first character is a pipe, return an error
	if (input[0] == '|')
		return (unexpected_token('|'));
	// If the last character is a pipe, print an error message and return true
	if (input[ft_strlen(input) - 1] == '|')
	{
		ft_putendl_fd(NO_PIPE_PROMPT, STDERR_FILENO);
		return (true);
	}
	// If the last character is a redirect operator, print an error message and return true
	if (is_onstr(REDIRECTS, input[ft_strlen(input) - 1]))
	{
		ft_putendl_fd(SYTX_ERR_RDR, STDERR_FILENO);
		return (true);
	}
	// If there are no errors, return false
	return (false);
}
