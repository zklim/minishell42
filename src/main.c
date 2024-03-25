/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:36:12 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/23 21:01:17 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>

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

int	sig_int;

int	main(int argc, char **argv, char **env)
{
	t_shell				shell;

	register_signals();
	while (1)
	{
		if (readline("input: ") == NULL)
			exit(0);
		else if (sig_int == 1)
			printf("SIGINT received\n");
	}
	(void)argc;
	(void)argv;
	shell.env = build_env(env);
}