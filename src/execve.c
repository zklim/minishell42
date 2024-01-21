/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:04:17 by zhlim             #+#    #+#             */
/*   Updated: 2024/01/12 21:31:01 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve.h"

void	execute_cmd(t_cmd *cmd) {
	if (execve(cmd->path, cmd->args, cmd->env) == -1)
	{
		perror(strerror(errno));
		exit(errno);
	}
}

int	main(void)
{	
	char	*path = "/bin/ls";
	char	*args[] = {path ,"-l", NULL};
	char	*env[] = {NULL};
	t_cmd	cmd;
	
	cmd.path = path;
	cmd.args = args;
	cmd.env = env;
	
	execute_cmd(&cmd);

	return 0;
}
