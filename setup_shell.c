/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:39:56 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/16 16:39:56 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// Function to set up the shell
void	setup_shell(char **envp, t_data *data, t_statement **statement_list)
{
	// Assign the environment variables to the data structure
	data->envp = envp;
	// Initialize the list of environment variables
	data->envp_lst = init_envp_lst(envp);
	// Initialize the head of the list to NULL
	data->head = NULL;
	// Initialize the statement list to NULL
	*statement_list = NULL;
	// Configure the signals for the shell
	config_signals();
}