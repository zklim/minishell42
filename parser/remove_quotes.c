/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:59:09 by cocheong          #+#    #+#             */
/*   Updated: 2024/01/22 15:59:09 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to check if there are any unclosed quotes in a string
int	unclosed_quotes(char *str)
{
	char	last_opened;

	last_opened = 0;
	// Loop through the string until we find an open quote
	while (*str && !last_opened)
	{
		if (*str == '\'' || *str == '"')
			last_opened = *str;
		str++;
	}
	// Loop through the string until we find the closing quote
	while (*str && last_opened)
	{
		if (*str && *str == last_opened)
			last_opened = 0;
		str++;
	}
	// If there are more characters in the string, check them for unclosed quotes
	if (*str)
		return (unclosed_quotes(str));
	// If there are no more characters and no unclosed quotes, return 0
	else if (!last_opened)
		return (0);
	// If there is an unclosed quote, return 1
	else
		return (1);
}

// Function to calculate the size of a string after removing quotes
static size_t	remove_quotes_size(char	*parsed)
{
	size_t	i;
	size_t	size;
	char	quotes;

	i = 0;
	size = 0;
	// Loop through the string
	while (parsed[i])
	{
		// If the current character is not a quote, increment the size
		while (parsed[i] && !is_onstr(QUOTES, parsed[i]))
		{
			i += 1;
			size += 1;
		}
		if (!parsed[i])
			break ;
		quotes = parsed[i++];
		// If the current character is a quote, skip it and the matching closing quote
		while (parsed[i] && parsed[i] != quotes)
		{
			i += 1;
			size += 1;
		}
		quotes = 0;
	}
	return (size);
}

// Function to remove quotes from a string
char	*remove_quotes(char	*parsed)
{
	size_t	i;
	size_t	j;
	char	quotes;
	char	*unquoted_parsed;

	i = 0;
	j = 0;
	quotes = '\0';
	// Allocate memory for the unquoted string
	unquoted_parsed = malloc((remove_quotes_size(parsed) + 1) * sizeof(char));
	// Loop through the string
	while (parsed[i])
	{
		// If the current character is not a quote, copy it to the unquoted string
		while (parsed[i] && !is_onstr(QUOTES, parsed[i]))
			unquoted_parsed[j++] = parsed[i++];
		if (!parsed[i])
			break ;
		quotes = parsed[i];
		i += 1;
		// If the current character is a quote, skip it and the matching closing quote
		while (parsed[i] && parsed[i] != quotes)
			unquoted_parsed[j++] = parsed[i++];
		quotes = '\0';
	}
	unquoted_parsed[j] = '\0';
	free(parsed);
	return (unquoted_parsed);
}
