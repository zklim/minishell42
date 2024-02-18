/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:04:17 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/19 02:08:26 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executions/execve.h"

extern long long	g_exit_status;

void	exec_cmd(t_statement *current_node, t_data *data)
{
	signal(SIGINT, child_signals);
	if (current_node->token == PIPE)
		exec_pipe(current_node, data);
	else if (current_node->token == NONE)
		exec_executables(current_node, data);
	else
		exec_redirects(current_node, data);
	exit(g_exit_status);
}

void	exec_type(t_statement *statement_list, t_data *data)
{
	int		temp_status;

	if (p_lstsize(statement_list) == 1)
	{
		if (!builtin(statement_list, data) && fork() == 0)
		{
			signal(SIGINT, child_signals);
			exec_executables(statement_list, data);
		}
	}
	else if (fork() == 0)
		exec_cmd(statement_list, data);
	waitpid(-1, &temp_status, 0);
	if (!WTERMSIG(temp_status))
		g_exit_status = temp_status >> 8;
}
