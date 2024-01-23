/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:36:12 by zhlim             #+#    #+#             */
/*   Updated: 2024/01/23 18:25:29 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	main(void)
// {	
// 	char	*path = "/bin/ls";
// 	char	*args[] = {path , "-la", NULL};
// 	char	*env[] = {NULL};
// 	t_cmd	cmd;
	
// 	cmd.path = path;
// 	cmd.args = args;
// 	cmd.env = env;
	
// 	execute_cmd(&cmd);

// 	return 0;
// }

int	main(int argc, char **argv, char **env) {
	(void)argc;
	(void)argv;
	ft_echo("$?", 0, env);
}