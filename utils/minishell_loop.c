/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:55:19 by cocheong          #+#    #+#             */
/*   Updated: 2024/01/17 14:55:19 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Create a loop that will run forever until the user exits the shell.
// The loop should display a prompt to the user, and then wait for a command.
// The prompt should be something like: minishell$.
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include <string.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

char	*minishell_read_line(void)
{
	char	*line;
	size_t	bufsize;


	bufsize = 0;
	if (getline(&line, &bufsize, stdin) == -1) 
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
			perror("minishell: getline\n");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

char	**minishell_split_line(char *line)
{
	int		bufsize;
	int		position;
	char	**tokens;
	char	*token;

	tokens = malloc(bufsize * sizeof(char *));
	bufsize = 64;
	position = 0;
	if (!tokens)
	{
		fprintf(stderr, "minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "minishell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}

int	minishell_execute(char **args)
{
	int	i;

	i = 0;
	if (args[0] == NULL)
		return (1);

	if (ft_strncmp(args[0], "exit", 4) == 0)
		return (0);

	while (args[i] != NULL)
	{
		printf("%s\n", args[i]);
		i++;
	}
	return (1);
}

int	minishell_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		ft_putstr_fd("minishell$ ", 1);
		line = minishell_read_line();
		if (!line)
		{
			printf("Error: Failed to read line\n");
			continue;
		}
		args = minishell_split_line(line);
		if (!args)
		{
			printf("Error: Failed to split line into arguments\n");
			free(line);
			continue;
		}
		status = minishell_execute(args);
		free(line);
		free(args);
	}
	return (status);
}
