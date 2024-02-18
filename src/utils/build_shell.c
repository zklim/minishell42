/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:24:23 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/16 16:45:15 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils/build_shell.h"

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char		**build_env(char **env)
{
	char	**shell_env;
	int		i;

	i = 0;
	shell_env = (char **)malloc(sizeof(char *) * (ft_arrlen(env) + 1));
	if (!shell_env)
		return NULL;
	while (env[i])
	{
		shell_env[i] = ft_strdup(env[i]);
		i++;
	}
	shell_env[i] = NULL;
	return (shell_env);
}
