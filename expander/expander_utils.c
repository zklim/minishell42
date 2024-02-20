/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 23:48:32 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/13 23:48:32 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to initialize variables
void	init_vars(size_t *i, size_t *size, bool *in_quotes, bool *in_dquotes)
{
	*i = 0;
	*size = 0;
	*in_quotes = false;
	*in_dquotes = false;
}

// Function to get the size of the exit status
size_t	exit_status_size(void)
{
	char	*exit_status;
	size_t	size;

	// Convert the exit status to a string
	exit_status = ft_lltoa(g_exit_status);
	// Get the length of the string
	size = ft_strlen(exit_status);
	// Free the string
	free(exit_status);
	// Return the length
	return (size);
}

// Function to get the size of the expanded variable
size_t	expand_size(char *input_at_i, size_t *i, t_data *data)
{
	size_t	var_size;
	char	*var_name;
	char	*var_value;

	// Skip the dollar sign
	*i += 1;
	// If it's a single dollar sign, return 1
	if (single_dollar(input_at_i))
		return (1);
	var_size = 0;
	// Get the length of the variable name
	while (input_at_i[var_size + 1]
		&& input_at_i[var_size + 1] != ' '
		&& !is_onstr(QUOTES, input_at_i[var_size + 1])
		&& input_at_i[var_size + 1] != '$')
				var_size += 1;
	// If there's no variable name, return 0
	if (var_size == 0)
		return (0);
	// Get the variable name
	var_name = ft_substr(input_at_i, 1, var_size);
	// Get the variable value
	var_value = get_fromvlst(var_name, &data->envp_vlst);
	// Free the variable name
	free(var_name);
	// Skip the variable name
	*i += var_size;
	// If there's no variable value, return 0
	if (!var_value)
		return (0);
	// Return the length of the variable value
	return (ft_strlen(var_value));
}

// Function to get the size of the expanded input
int	expanded_size(char *input, t_data *data)
{
	size_t	i;
	size_t	size;
	bool	in_quotes;
	bool	in_dquotes;

	// Initialize variables
	init_vars(&i, &size, &in_quotes, &in_dquotes);
	// Loop through the input
	while (input[i])
	{
		// If the current character is a double quote and we are not inside single quotes, toggle the in_dquotes flag
		if (input[i] == '\"' && !in_quotes)
			in_dquotes = !in_dquotes;
		// If the current character is a single quote and we are not inside double quotes, toggle the in_quotes flag
		if (input[i] == '\'' && !in_dquotes)
			in_quotes = !in_quotes;
		// If the current character is a dollar sign followed by a question mark and we are not inside quotes, add the size of the exit status
		if ((input[i] == '$' && input[i + 1] == '?') && !in_quotes)
		{
			size += exit_status_size() - 1;
			i += 1;
		}
		// If the current character is a dollar sign and we are not inside quotes, add the size of the expanded variable
		else if (input[i] == '$' && !in_quotes)
			size += expand_size(&(input[i]), &i, data) - 1;
		else
			i += 1;
		// Increment the size
		size += 1;
	}
	// Return the size
	return (size);
}
