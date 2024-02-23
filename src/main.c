/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:36:12 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/24 00:05:11 by zhlim            ###   ########.fr       */
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

// int	sig_int;

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell				shell;

// 	register_signals();
// 	while (1)
// 	{
// 		if (readline("input: ") == NULL)
// 			exit(0);
// 	}
// 	(void)argc;
// 	(void)argv;
// 	shell.env = build_env(env);
// }

int	main(int argc, char **argv, char **env)
{
	t_shell				shell;
	int					save;
	int					file;

	register_signals();
	save = 0;
	while (1)
	{
		if (readline("input: ") == NULL)
			exit(0);
		file = redirect_outputs(&save, "output.txt", 0);
		restore_outputs(&save, file);
	}
	(void)argc;
	(void)argv;
	shell.env = build_env(env);
}