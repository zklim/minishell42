/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:36:22 by zhlim             #+#    #+#             */
/*   Updated: 2024/01/24 17:34:08 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "executions/execve.h"
# include "executions/builtins/echo.h"
# include "executions/builtins/pwd.h"
# include "executions/builtins/cd.h"

void	execute_cmd(t_cmd *cmd);

#endif