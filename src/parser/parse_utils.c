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
	return (c == ' ' || (c > 8 && c < 14));
}

t_token	get_token(char *token)
{
	t_token	op;

	if (!token)
		op = NONE;
	else if (streq(token, "|"))
		op = PIPE;
	else if (streq(token, ">>"))
		op = RDR_OUT_APPEND;
	else if (streq(token, ">"))
		op = RDR_OUT_REPLACE;
	else if (streq(token, "<<"))
		op = RDR_INPUT_UNTIL;
	else if (streq(token, "<"))
		op = RDR_INPUT;
	else
		op = NONE;
	free(token);
	return (op);
}

int	get_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	get_token_len(char *str)
{
	int		i;
	char	quotes;

	i = 0;
	if (is_onstr(OPERATOR, str[i]))
	{
		if (input_at_i[i] == input_at_i[i + 1])
			return (2);
		return (1);
	}
	while (str[i] && !is_whitespace(str[i]) && !is_onstr(OPERATOR, str[i]))
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quotes = str[i];
			while (str[i] && str[i] != quotes)
				i++;
			i++;
		}
		i++;
	}
	return (i);
}

int	get_num_statements(char *input)
{
	int		count;
	bool	quotes;
	bool	flag;

	count = 0;
	flag = false;
	quotes = false;
	while (*input)
	{
		if (is_onstr(OPERATOR, *input))
			count++;
		if (is_onstr(QUOTES, *input))
			quotes = !quotes;
		else if (is_onstr(QUOTES, *input) && *input == *(input + 1))
			input++;
		if (*input != ' ' && !is_onstr(OPERATOR, *input) && !flag && !quotes)
		{
			flag = true;
			count++;
		}
		else if (*input == ' ' || is_onstr(OPERATOR, *input))
			flag = false;
		input++;
	}
	return (count);
}
