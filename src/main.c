/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:36:12 by zhlim             #+#    #+#             */
/*   Updated: 2024/03/25 17:49:15 by zhlim            ###   ########.fr       */
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

int	sig_int;

int	main(int argc, char **argv, char **env)
{
	t_shell		shell;
	char		*line;
	// int			save;
	// int			file;

	sig_int = 0;
	register_signals();
	line = NULL;
	while (1)
	{
		line = readline("input: ");
		if (line == NULL)
			exit(0);
		ft_echo(line, 0, env);
		// file = redirect_outputs(&save, "output.txt", 0);
		if (sig_int != 0)
			break;
	}
	// restore_outputs(&save, file);
	// close(file);
	(void)argc;
	(void)argv;
	shell.env = build_env(env);
}