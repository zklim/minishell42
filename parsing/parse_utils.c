/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 01:18:47 by cocheong          #+#    #+#             */
/*   Updated: 2024/01/20 01:18:47 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	return (false);
}

int	get_argc(t_lexer *lexer_list)
{
	int	argc;

	argc = 0;
	while (lexer_list)
	{
		if (lexer_list->token == OPERATOR && lexer_list->token != PIPE)
			argc++;
		lexer_list = lexer_list->next;
	}
	return (argc);
}

int	get_token_len(t_lexer *str)
{
	int		i;
	char	quotes;

	i = 0;
	if (is_onstr(OPERATOR, str->token))
	{
		if (str->token == GREAT_GREAT || str->token == LESS_LESS)
			return (2);
		return (1);
	}
	else if (str->token && !is_whitespace(str->token)
		&& !is_onstr(OPERATOR, str->token))
	{
		while (str->str[i])
		{
			if (str->str[i] == 34 || str->str[i] == 39)
			{
				quotes = str->str[i];
				i++;
				while (str->str[i] && str->str[i] != quotes)
					i++;
				i++;
			}
			else if (is_onstr(OPERATOR, str->str[i]))
				break ;
			else
				i++;
		}
	}
}

int	get_num_statements(t_lexer *input)
{
	int		count;
	bool	quotes;
	bool	flag;

	count = 0;
	flag = false;
	quotes = false;
	while (input)
	{
		if (is_onstr(input->token, input))
			count++;
		if (is_onstr(QUOTES, input))
			quotes = !quotes;
		else if (is_onstr(QUOTES, input) && input == (input + 1))
			input++;
		if (input->str != ' ' && !is_onstr(input->token, input)
			&& !flag && !quotes)
		{
			flag = true;
			count++;
		}
		else if (input->str == ' ' || is_onstr(input->token, input))
			flag = false;
	}
	return (count);
}


