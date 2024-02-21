/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 23:47:50 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/13 23:47:50 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern long long	g_exit_status;

// Function to expand the exit status
size_t	expand_exit_status(char *expanded_input_at_i, size_t *i)
{
	char	*exit_status;
	size_t	j;

	// Skip the dollar sign and the question mark
	*i += 2;
	// Convert the exit status to a string
	exit_status = ft_lltoa(g_exit_status);
	j = 0;
	// Copy the exit status to the expanded input
	while (exit_status[j])
	{
		expanded_input_at_i[j] = exit_status[j];
		j += 1;
	}
	// Free the exit status string
	free(exit_status);
	// Return the length of the exit status
	return (j);
}

// Function to expand a variable
size_t	expand_variable(char *expanded_input_at_i, char *input,
	size_t *i, t_data *data)
{
	char	*var_value;
	size_t	size;
	size_t	j;
	size_t	k;

	size = 0;
	j = 0;
	k = 0;
	// Skip the dollar sign
	*i += 1;
	// If the next character is a whitespace or a quote, return 1
	if (!input[*i] || input[*i] == ' ' || input[*i] == '\"')
	{
		expanded_input_at_i[0] = '$';
		return (1);
	}
	// Get the length of the variable name
	while (input[*i + size] && input[*i + size] != ' '
		&& input[*i + size] != '\"' && !is_onstr(QUOTES, input[*i + size])
		&& input[*i + size] != '$')
		size += 1;
	// Get the variable value
	var_value = get_varvalue_fromvlst(ft_substr(input, *i, size), data);
	// Skip the variable name
	*i += size;
	// If there's no variable value, return 0
	if (!var_value)
		return (0);
	// Copy the variable value to the expanded input
	while (var_value[k])
		expanded_input_at_i[j++] = var_value[k++];
	// Return the length of the variable value
	return (j);
}

// Function to expand the input
char	*expander(char *input, t_data *data)
{
	size_t	i;
	size_t	j;
	bool	in_quotes;
	bool	in_dquotes;
	char	*expanded_input;

	// Initialize variables
	init_vars(&i, &j, &in_quotes, &in_dquotes);
	// Allocate memory for the expanded input
	expanded_input = malloc((expanded_size(input, data) + 1) * sizeof(char));
	// Loop through the input
	while (input[i])
	{
		// If the current character is a double quote and we are not inside single quotes, toggle the in_dquotes flag
		if (input[i] == '\"' && !in_quotes)
			in_dquotes = !in_dquotes;
		// If the current character is a single quote and we are not inside double quotes, toggle the in_quotes flag
		if (input[i] == '\'' && !in_dquotes)
			in_quotes = !in_quotes;
		// If the current character is a dollar sign followed by a question mark and we are not inside quotes, expand the exit status
		if (input[i] == '$' && input[i + 1] == '?' && !in_quotes)
			j += expand_exit_status(&(expanded_input[j]), &i);
		// If the current character is a dollar sign and we are not inside quotes, expand the variable
		else if (input[i] && input[i] == '$' && !in_quotes)
			j += expand_variable(&(expanded_input[j]), input, &i, data);
		// Otherwise, copy the current character to the expanded input
		else
			expanded_input[j++] = input[i++];
	}
	// Null-terminate the expanded input
	expanded_input[j] = '\0';
	// Free the input
	free(input);
	// Return the expanded input
	return (expanded_input);
}
