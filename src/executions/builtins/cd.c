/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhlim <zhlim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:30:20 by zhlim             #+#    #+#             */
/*   Updated: 2024/01/25 19:28:16 by zhlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executions/builtins/cd.h"

static char	*get_env_name(char *path)
{
	char	*env_name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (path[i + 1] != '\0' && path[i + 1] != '/')
		i++;
	env_name = malloc(sizeof(char) * (i + 1));
	if (!env_name)
		return (NULL);
	while (j < i)
	{
		env_name[j] = path[j + 1];
		j++;
	}
	env_name[j] = '\0';
	return (env_name);
}

static char	*new_path(char *path, char *env_value)
{
	char	*new_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (path[i] != '\0' && path[i] != '/')
		i++;
	new_path = malloc(sizeof(char) * (ft_strlen(&path[i]) + ft_strlen(env_value) + 1));
	if (!new_path)
		return (NULL);
	while (env_value[j] != '\0')
	{
		new_path[j] = env_value[j];
		j++;
	}
	while (path[i] != '\0')
	{
		new_path[j] = path[i];
		i++;
		j++;
	}
	return new_path;
}

void	ft_cd(char *path)
{
	static char	*prev_pwd;
	char		*current_pwd;
	char		*env_name;

	current_pwd = getcwd(NULL, 0);
	if (prev_pwd == NULL)
		prev_pwd = current_pwd;
	if (path == NULL)
		path = getenv("HOME");
	else if (*path == '$')
	{
		env_name = get_env_name(path);
		path = new_path(path, getenv(env_name));
		free(env_name);
	}
	else if (*path == '-')
			path = prev_pwd;
	if (chdir(path) == -1)
		printf("cd: no such file or directory: %s\n", path);
	else
	{
		free(prev_pwd);
		prev_pwd = current_pwd;
		printf("%s\n", getcwd(NULL, 0)); // for testing
	}
}