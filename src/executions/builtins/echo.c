/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:51:18 by zhlim             #+#    #+#             */
/*   Updated: 2024/02/21 03:57:12 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// IMPORTANT: Print exit code yet to be implemented
static char	*get_env_key(char *env)
{
	char	*key;
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * i + 1);
	if (!key)
		return (NULL);
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

static void	ft_env_value(char *env)
{
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	ft_putstr_fd(env + i + 1, 1);
}

void	ft_echo(t_data *data, t_statement *stmt, int flag_n)
{
	char	*key;
	t_vlst	*env;

	if (!stmt || !stmt->argv || stmt->argc < 1)
		return ;

	if (stmt->argv[0][0] == '$')
	{
		if (stmt->argv[0][1] == '?')
			write(1, "PRINT_EXIT_CODE", 15);
		else
		{
			env = data->envp_vlst;
			while (env)
			{
				key = get_env_key(env->var_name);
				if (!ft_strncmp(key, stmt->argv[0] + 1, ft_strlen(key)))
				{
					ft_env_value(env->var_value);
					free(key);
					break ;
				}
				free(key);
				env = env->next;
			}
		}
	}
	else
		ft_putstr_fd(stmt->argv[0], 1);
	if (!flag_n)
		write(1, "\n", 1);

	return ;
}
