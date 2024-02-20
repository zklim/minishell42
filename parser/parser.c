/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 04:27:49 by cocheong          #+#    #+#             */
/*   Updated: 2024/01/17 04:27:49 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to parse the input into an array of strings
char	**parse_input(char *input)
{
	size_t		i;
	size_t		k;
	char		**parsed;
	size_t		len;
	size_t		j;

	i = 0;
	k = 0;
	// Allocate memory for the parsed input
	parsed = malloc((get_num_statements(input) + 1) * sizeof(char *));
	while (input[i])
	{
		// Get the length of the current token
		len = get_token_len(&input[i]);
		if (!len)
		{
			i += 1;
			continue ;
		}
		// Allocate memory for the current token
		parsed[k] = malloc((len + 1) * sizeof(char));
		j = 0;
		// Copy the current token to the parsed input
		while (input[i] && j < len)
			parsed[k][j++] = input[i++];
		parsed[k++][j] = '\0';
	}
	parsed[k] = NULL;
	return (parsed);
}

// Function to process a command and store it in a statement
t_statement	*process_command(char **parsed, size_t *command_index,
							t_statement *current)
{
	size_t	arg_index;

	arg_index = 0;
	// Loop through the parsed input until we find an operator
	while (parsed[*command_index]
		&& !is_onstr(OPERATOR, parsed[*command_index][0]))
	{
		// Remove quotes from the current argument and store it in the statement
		current->argv[arg_index] = remove_quotes(parsed[*command_index]);
		arg_index++;
		(*command_index)++;
	}
	current->argv[arg_index] = NULL;
	// If the current token is an operator, store it in the statement
	if (parsed[*command_index])
	{
		current->token = get_token(parsed[*command_index]);
		(*command_index)++;
	}
	return (current);
}

// Function to parse the input and process the commands
t_statement	*parser(char *input)
{
	t_statement	*current;
	t_statement	*head;
	char		**parsed;
	size_t		command_index;

	command_index = 0;
	// Parse the input
	parsed = parse_input(input);
	free(input);
	// Create a new statement for the first command
	current = p_new_node(get_argc(&parsed[0]));
	head = current;
	while (parsed[command_index])
	{
		// Process the current command and store it in the statement
		current = process_command(parsed, &command_index, current);
		if (!parsed[command_index])
			break ;
		// Create a new statement for the next command
		current->next = p_new_node(get_argc(&parsed[command_index]));
		current = current->next;
	}
	current->next = NULL;
	free(parsed);
	return (head);
}
