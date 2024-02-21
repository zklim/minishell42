/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:33:36 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/21 03:21:26 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT2_H
# define EXPORT2_H

# include "../../minishell.h"

void	print_export(char **env);
void	add_to_env(t_data *shell, char *addition);
void	ft_export(t_data *shell, char *addition);

#endif