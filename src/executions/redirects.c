/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:39:18 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/16 21:39:18 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern long long	g_exit_status;

// Function to redirect input until a certain condition is met
static void	redirect_input_until(t_statement *node)
{
	char	*buff;
	int		fd[2];

	// Create a pipe
	pipe(fd);
	while (1)
	{
		// Read a line from the user
		buff = readline("> ");
		// If the line is equal to the next argument, break the loop
		if (streq(buff, node->next->argv[0]))
			break ;
		// Write the line to the write end of the pipe
		ft_putendl_fd(buff, fd[1]);
	}
	// Close the write end of the pipe
	close(fd[1]);
	// Redirect the standard input to the read end of the pipe
	dup2(fd[0], STDIN_FILENO);
	// Close the read end of the pipe
	close(fd[0]);
	// Free the buffer
	free(buff);
}

// Function to redirect input from a file
static void	redirect_input(t_statement *node)
{
	int		in_file;
	char	*error_msg_prefix;

	// If the next argument exists
	if (node->next->argv[0])
	{
		// Skip all input redirects
		while (node->next->token == RDR_INPUT)
			node = node->next;
		// If the file exists
		if (access(node->next->argv[0], F_OK) == 0)
		{
			// Open the file for reading
			in_file = open(node->next->argv[0], O_RDONLY, 0666);
			// Redirect the standard input to the file
			dup2(in_file, STDIN_FILENO);
		}
		else
		{
			// Print an error message
			error_msg_prefix = ft_strjoin("minishell: ", node->next->argv[0]);
			perror(error_msg_prefix);
			free(error_msg_prefix);
			// Set the global exit status to 2
			g_exit_status = 2;
			// Exit with failure
			exit(EXIT_FAILURE);
		}
	}
}

// Function to redirect output to a file
static void	redirect_output(t_statement *node)
{
	// Close the standard output
	close(STDOUT_FILENO);
	// While the next operator is an output redirect
	while (node->next->token == RDR_OUT_REPLACE
		|| node->next->token == RDR_OUT_APPEND)
	{
		// If the operator is an output replace, open the file for writing and truncate it
		if (node->token == RDR_OUT_REPLACE)
			open(node->next->argv[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		// If the operator is an output append, open the file for writing and append to it
		else if (node->token == RDR_OUT_APPEND)
			open(node->next->argv[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
		// Move to the next node
		node = node->next;
		// Close the standard output
		close(1);
	}
	// If the operator is an output replace, open the file for writing and truncate it
	if (node->token == RDR_OUT_REPLACE)
		open(node->next->argv[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	// If the operator is an output append, open the file for writing and append to it
	else if (node->token == RDR_OUT_APPEND)
		open(node->next->argv[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
}

// Function to execute redirects
void	exec_redirects(t_statement *node, t_data *data)
{
	t_statement	*temp;

	// Save the current node
	temp = node;
	// If the operator is an input redirect, redirect the input
	if (node->token == RDR_INPUT)
		redirect_input(node);
	// If the operator is an input redirect until, redirect the input until a certain condition is met
	else if (node->token == RDR_INPUT_UNTIL)
		redirect_input_until(node);
	// Otherwise, redirect the output
	else
		redirect_output(node);
	// Set the operator of the temp node to none
	temp->token = NONE;
	// While the operator is not none or a pipe, move to the next node
	while (node->token != NONE && node->token != PIPE)
		node = node->next;
	// If the operator is none, execute the command
	if (node->token == NONE)
		exec_cmd(temp, data);
	// Otherwise, execute the pipe
	else
		exec_pipe(node, data);
}
