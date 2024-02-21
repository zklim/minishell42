/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 21:38:13 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/16 21:38:13 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern long long	g_exit_status;
// Function to execute a command
void	exec_executables(t_statement *node, t_data *data)
{
	// If the command is a built-in command, execute it and return
	if (builtin(node, data))
		return ;
	// If the command is not a built-in command, try to execute it as a binary command
	// cmd_binaries(node, data);
}
