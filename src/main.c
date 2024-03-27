/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:36:12 by zhlim             #+#    #+#             */
/*   Updated: 2024/03/27 17:50:43 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>

int	sig_int;

int	main(int argc, char **argv, char **env)
{
	t_shell		shell;
	// char		*line;
	int			save;
	int			file;
	t_cmd		cmd;

	sig_int = 0;
	register_signals();
	// line = NULL;
	cmd.path = "/bin/cat";
	cmd.args = argv;
	cmd.env = env;
	while (1)
	{
		// line = readline("input: ");
		// if (line == NULL)
		// 	exit(0);
		file = redirect_inputs(&save, "input.txt");
		execute_cmd(&cmd);
		restore_inputs(&save, file);
		execute_cmd(&cmd);
	}
	(void)argc;
	(void)argv;
	shell.env = build_env(env);
}