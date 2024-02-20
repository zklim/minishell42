/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_shell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:24:53 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/19 02:16:36 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_SHELL_H
# define BUILD_SHELL_H

# include "../libft/libft.h"
# include "../minishell.h"

int		ft_arrlen(char **arr);
char	**build_env(char **env);

#endif