/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:04:17 by zhlim             #+#    #+#             */
/*   Updated: 2024/01/13 23:06:10 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execve.h"

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
	char	*args[] = {path , "-la", NULL};
	char	*env[] = {NULL};
	t_cmd	cmd;
	
	cmd.path = path;
	cmd.args = args;
	cmd.env = env;
	
	execute_cmd(&cmd);

	return 0;
}
