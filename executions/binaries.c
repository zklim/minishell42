/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 02:53:28 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/17 02:53:28 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern long long	g_exit_status;

#define NOT_FOUND NULL
// Function to get the PATH environment variable and split it into an array of paths
static char	**get_paths(t_vlst *envp_lst)
{
	t_vlst	*temp;

	// Start with the first environment variable
	temp = envp_lst;
	// Loop through the environment variables until we find the PATH variable
	while (!streq("PATH", temp->var_name))
	{
		temp = temp->next;
		// If we've gone through all the environment variables and haven't found the PATH variable, return NULL
		if (temp == NULL)
			return (NULL);
	}
	// Split the PATH variable's value into an array of paths and return it
	return (ft_split(temp->var_value, ':'));
}

// Function to get the full path of the binary file for a command
static char	*get_bin_path(char *cmd, char **paths)
{
	size_t	i;
	char	*tmp;
	char	*bin_path;

	// If there are no paths, return NULL
	if (!paths)
		return (NULL);
	i = 0;
	// Loop through the paths
	while (paths[i])
	{
		// Join the current path with the command to get the full path of the binary file
		tmp = ft_strjoin(paths[i], "/");
		bin_path = join_free(tmp, cmd);
		// If the binary file exists and is executable, return its full path
		if (access(bin_path, F_OK | X_OK) == 0)
			return (bin_path);
		// If the binary file doesn't exist or isn't executable, free the memory allocated for its full path and continue with the next path
		free(bin_path);
		i += 1;
	}
	// If we've gone through all the paths and haven't found the binary file, return NULL
	return (NULL);
}

// Function to print an error message, free the memory allocated for the paths, set the global exit status, and exit the program
static void	exit_and_free_matrix(char **paths, char *cmd, int exit_status)
{
	// If a command is provided, print an error message for it
	if (cmd)
		perror(cmd);
	// Free the memory allocated for the paths
	free_matrix(paths);
	// If the global exit status isn't a signal, set it to the provided exit status
	if (!WIFSIGNALED(g_exit_status))
		g_exit_status = exit_status;
	// Exit the program with the global exit status
	exit(g_exit_status);
}

// Function to execute a binary command
void	cmd_binaries(t_statement *statement, t_data *data)
{
	char	*bin_path;
	char	**paths;

	// Start with the first argument of the statement as the binary path
	bin_path = statement->argv[0];
	// Get the paths from the PATH environment variable
	paths = get_paths(data->envp_lst);
	// If the statement is an absolute path
	if (is_absolute_path(statement))
	{
		// Try to execute the binary file
		if (execve(bin_path, statement->argv, data->envp) == -1)
			// If the execution fails, print an error message, free the memory allocated for the paths, set the global exit status to 127, and exit the program
			exit_and_free_matrix(paths, statement->argv[0], 127);
		// If the execution succeeds, free the memory allocated for the paths, set the global exit status to 0, and exit the program
		exit_and_free_matrix(paths, NULL, EXIT_SUCCESS);
		return ;
	}
	// If the statement isn't an absolute path, get the full path of the binary file for the command
	bin_path = get_bin_path(statement->argv[0], paths);
	// If the binary file isn't found
	if (bin_path == NOT_FOUND)
	{
		// Print a "command not found" message, free the memory allocated for the paths, set the global exit status to 127, and exit the program
		cmd_not_found(statement->argv[0]);
		exit_and_free_matrix(paths, NULL, 127);
	}
	// Try to execute the binary file
	if (execve(bin_path, statement->argv, data->envp) == -1)
	{
		// If the execution fails, free the memory allocated for the full path of the binary file, print an error message, free the memory allocated for the paths, set the global exit status to 127, and exit the program
		free(bin_path);
		exit_and_free_matrix(paths, statement->argv[0], 127);
	}
	// If the execution succeeds, free the memory allocated for the full path of the binary file, free the memory allocated for the paths, set the global exit status to 0, and exit the program
	free(bin_path);
	exit_and_free_matrix(paths, NULL, EXIT_SUCCESS);
}
