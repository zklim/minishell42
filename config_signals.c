/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:41:04 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/16 16:41:04 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

extern long long	g_exit_status;
// Function to handle signals in a child process
void	child_signals(int signum)
{
	// If the signal is SIGINT (Ctrl+C)
	if (signum == SIGINT)
	{
		// Print a newline
		ft_putchar_fd('\n', STDOUT_FILENO);
		// Set the global exit status to 130
		g_exit_status = 130;
		// Exit with the global exit status
		exit(g_exit_status);
	}
}

// Function to dismiss a signal
void	dismiss_signal(int signum)
{
	// If the signal is SIGINT (Ctrl+C)
	if (signum == SIGINT)
	{
		// Print a newline
		ft_putchar_fd('\n', STDOUT_FILENO);
		// Move the cursor to a new line
		rl_on_new_line();
		// Replace the current line with an empty string
		rl_replace_line("", 0);
		// Redisplay the prompt
		rl_redisplay();
		// Set the global exit status to 130
		g_exit_status = 130;
	}
}

// Function to configure signals
void	config_signals(void)
{
	struct sigaction	sa;

	// Set the signal handler to dismiss_signal
	sa.sa_handler = &dismiss_signal;
	// Restart functions if interrupted by handler
	sa.sa_flags = SA_RESTART;
	// Initialize the signal set
	sigemptyset(&sa.sa_mask);
	// Add SIGINT to the signal set
	sigaddset(&sa.sa_mask, SIGINT);
	// Change the action taken by the process on receipt of a specific signal (SIGINT)
	sigaction(SIGINT, &sa, NULL);
	// Ignore SIGQUIT signal
	signal(SIGQUIT, SIG_IGN);
}
