/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:07:28 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/19 02:28:43 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECVE_H
# define EXECVE_H

# include "../minishell.h"

typedef	struct	s_cmd
{
	char	*path;
	char	**args;
	char	**env;
}	t_cmd;

#endif