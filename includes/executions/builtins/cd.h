/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:30:35 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/19 02:44:51 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "../includes/executions/builtins/cd.h"
# include "../../minishell.h"


void	ft_cd(char *path);
void	ft_pwd(void);

#endif