/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:51:18 by zhlim             #+#    #+#             */
/*   Updated: 2024/01/23 18:31:37 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executions/builtins/echo.h"

char	*get_env_key(char *env)
{
	char	*key;
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * i + 1);
	if (!key)
		return NULL;
	else
	{
		i = 0;
		while (env[i] != '=')
		{
			key[i] = env[i];
			i++;
		}
		key[i] = '\0';
		return (key);
	}
}

void	print_env_value(char *env)
{
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	ft_putstr_fd(env + i + 1, 1);
}


// IMPORTANT: Print exit code yet to be implemented
void	ft_echo(char *str, int flag_n, char **env)
{
	char	*key;

	if (!str || !*str)
		return;
	if (*str == '$')
	{
		if (*(str + 1) == '?')
			write(1, "PRINT_EXIT_CODE", 15);
		else
		{
			key = get_env_key(*env);
			while (*env)
			{
				if (!ft_strncmp(get_env_key(*env), str + 1, ft_strlen(key)))
				{
					print_env_value(*env);
					break;
				}
				env = env + 1;
			}
		}
	}
	else
		ft_putstr_fd(str, 1);
	if (!flag_n)
		write(1, "\n", 1);
	return;
}