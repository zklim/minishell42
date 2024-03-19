/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:29:32 by cocheong          #+#    #+#             */
/*   Updated: 2024/03/10 21:29:32 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>

typedef struct	s_parser_token
{
    char	*command;
    char	**args;
}				t_parser_token;

char	**lexer(char *input);
int	parser(char **lexer_tokens);

int	main(void)
{
	char	*line;
	char	**lexer_tokens;
	int		parser_tokens;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		lexer_tokens = lexer(line);
		parser_tokens = parser(lexer_tokens);
		free(line);
	}
	return (0);
}