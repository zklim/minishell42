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

// Parse the input into an array of strings @parsed = parse_input(input);
// Create a new node for the first command @current = p_new_node(get_argc(&parsed[0]));
// Process each command in the parsed input @while (parsed[command_index])
// Process each argument of the current command @while (parsed[command_index] && !is_onstr(OPERATOR, parsed[command_index][0]))
// Mark the end of the argv array @current->argv[arg_index] = NULL;
// If we've reached the end of the parsed input, break the loop @if (!parsed[command_index])
// Get the operator that follows the current command @current->operator = get_token(parsed[command_index]);
// Create a new node for the next command @current->next = p_new_node(get_argc(&parsed[command_index]));
// Move to the next node @current = current->next;
// Mark the end of the linked list @current->next = NULL;

char	**parse_input(char *input)
{
	size_t		i;
	size_t		k;
	char		**parsed;
	size_t		len;
	size_t		j;

	i = 0;
	k = 0;
	parsed = malloc((get_num_statements(input) + 1) * sizeof(char *));
	while (input[i])
	{
		len = get_token_len(&input[i]);
		if (!len)
		{
			i += 1;
			continue ;
		}
		parsed[k] = malloc((len + 1) * sizeof(char));
		j = 0;
		while (input[i] && j < len)
			parsed[k][j++] = input[i++];
		parsed[k++][j] = '\0';
	}
	parsed[k] = NULL;
	return (parsed);
}

t_statement	*process_command(char **parsed, size_t *command_index,
							t_statement *current)
{
	size_t	arg_index;

	arg_index = 0;
	while (parsed[*command_index]
		&& !is_onstr(OPERATOR, parsed[*command_index][0]))
	{
		current->argv[arg_index] = remove_quotes(parsed[*command_index]);
		arg_index++;
		(*command_index)++;
	}
	current->argv[arg_index] = NULL;
	if (parsed[*command_index])
	{
		current->token = get_token(parsed[*command_index]);
		(*command_index)++;
	}
	return (current);
}

t_statement	*parser(char *input)
{
	char		**parsed;
	t_statement	*current;
	t_statement	*head;
	size_t		command_index;

	command_index = 0;
	parsed = parse_input(input);
	free(input);
	current = p_new_node(get_argc(&parsed[0]));
	head = current;
	while (parsed[command_index])
	{
		current = process_command(parsed, &command_index, current);
		if (!parsed[command_index])
			break ;
		current->next = p_new_node(get_argc(&parsed[command_index]));
		current = current->next;
	}
	current->next = NULL;
	free(parsed);
	return (head);
}
