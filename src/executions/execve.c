/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:04:17 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/21 20:39:18 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executions/execve.h"

extern long long	g_exit_status;

// Function to execute a command
void	exec_cmd(t_statement *current_node, t_data *data)
{
	// Set the SIGINT signal handler to child_signals
	signal(SIGINT, child_signals);
	// If the current node is a pipe, execute the pipe
	if (current_node->token == PIPE)
		exec_pipe(current_node, data);
	// If the current node is not a pipe or a redirect, execute the executable
	else if (current_node->token == NONE)
		exec_executables(current_node, data);
	// If the current node is a redirect, execute the redirect
	else
		exec_redirects(current_node, data);
	// Exit with the global exit status
	exit(g_exit_status);
}

// Function to execute a type of statement
void	exec_type(t_statement *statement_list, t_data *data)
{
	int		temp_status;

	// If the statement list has only one statement
	if (p_lstsize(statement_list) == 1)
	{
		// If the statement is not a built-in command and we are in a child process
		if (!builtin(statement_list, data) && fork() == 0)
		{
			// Set the SIGINT signal handler to child_signals
			signal(SIGINT, child_signals);
			// Execute the executable
			exec_executables(statement_list, data);
		}
	}
	// If we are in a child process
	else if (fork() == 0)
		// Execute the command
		exec_cmd(statement_list, data);
	// Wait for the child process to terminate
	waitpid(-1, &temp_status, 0);
	// If the child process was not terminated by a signal
	if (!WTERMSIG(temp_status))
		// Set the global exit status to the exit status of the child process
		g_exit_status = temp_status >> 8;
}
