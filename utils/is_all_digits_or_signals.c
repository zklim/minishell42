/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all_digits_or_signals.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:56:07 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/16 16:56:07 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_all_digits_or_signals(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]) && str[i] != '-' && str[i] != '+')
			return (false);
		i += 1;
	}
	return (true);
}