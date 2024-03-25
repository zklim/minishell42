/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:51:18 by zhlim             #+#    #+#             */
/*   Updated: 2024/03/25 18:07:37 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executions/builtins/echo.h"

static char	*get_env_key(char *env)
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
		while (env[i] != '=' && env[i])
		{
			key[i] = env[i];
			i++;
		}
		key[i] = '\0';
		return (key);
	}
}

static void	ft_env_value(char *env)
{
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	ft_putstr_fd(env + i + 1, 1);
}

static int	print_env(char *str, int i, char **env)
{
	char	*key;
	int		j;

	j = 0;
	if (str[i + 1] == '?')
		write(1, "PRINT_EXIT_CODE", 15);
	else
	{
		while (env[j])
		{
			key = get_env_key(env[j]);
			if (!ft_strncmp(key, &str[i + 1], ft_strlen(key)))
			{
				ft_env_value(env[j]);
				i = i + ft_strlen(key);
				free(key);
				break;
			}
			free(key);
			j++;
		}
	}
	return (i);
}

// IMPORTANT: Print exit code yet to be implemented
void	ft_echo(char *str, int flag_n, char **env)
{
	int		i;

	i = 0;
	if (!str || !*str)
		return;
	while (str[i])
	{
		if (str[i] == '$')
			i = print_env(str, i, env);
		else
			write(1, &str[i], 1);
		i++;
	}
	if (!flag_n)
		write(1, "\n", 1);
	return;
}