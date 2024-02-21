/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:16:31 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/16 15:16:31 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	panic(t_data *data, char *error_msg, int exit_status)
{
	if (data)
		destroy(data);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	exit(exit_status);
}
