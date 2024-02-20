/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 02:09:34 by cocheong          #+#    #+#             */
/*   Updated: 2024/02/19 02:09:34 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern long long	g_exit_status;

// Function to check if the given string is a valid identifier
bool	is_valid_id(char *str)
{
	size_t	i;

	i = 0;
	// If the string is "=", it's not a valid identifier
	if (streq(str, "="))
		return (false);
	// Loop through the string until we find "=" or the end of the string
	while (str[i] && str[i] != '=')
	{
		// If the current character is a digit, "!", "@", "{", "}", or "-", the string is not a valid identifier
		if (is_digit(str[i]) || str[i] == '!' || str[i] == '@'
			|| str[i] == '{' || str[i] == '}' || str[i] == '-')
			return (false);
		i += 1;
	}
	// If we've gone through the whole string without finding an invalid character, the string is a valid identifier
	return (true);
}

// Function to call the unset command
static int	call_cmd_unset(t_statement *s, t_data *data)
{
	// If there's only one argument, return success
	if (s->argc == 1)
		return (EXIT_SUCCESS);
	// Otherwise, call the unset function with the given arguments
	return (ft_unset(s, &data->envp_lst));
}

// Function to call the cd command
static int	call_cmd_cd(t_statement *s, t_data *data)
{
	// If there are more than two arguments, return an error
	if (s->argc > 2)
		return (cd_too_many_args());
	// Otherwise, call the cd function with the given arguments
	else
		return (ft_cd(s->argv[1], data));
}

// Function to call the echo command
static int	call_cmd_echo(t_statement *s)
{
	t_statement	*temp;
	bool		has_n;

	temp = s;
	has_n = false;
	// If there are at least two arguments and the second one is "-n", set has_n to true
	if (s->argc >= 2)
		has_n = streq(s->argv[1], "-n");
	// Call the echo function with the current statement and the value of has_n
	ft_echo(temp, has_n);
	temp = temp->next;
	// Loop through the rest of the statements while there are more than two arguments
	while (temp != NULL && temp->argc > 2)
	{
		// Call the echo function with the current statement and false for has_n
		ft_echo(temp, false);
		// If the operator is a pipe, break the loop
		if (temp->operator == PIPE)
			break ;
		temp = temp->next;
	}
	// If has_n is false, print a newline
	if (!has_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	// Return success
	return (EXIT_SUCCESS);
}

// Function to check if the command is a built-in command and execute it
bool	builtin(t_statement *s, t_data *data)
{
	// If the command is "exit", execute the exit command
	if (streq(s->argv[0], "exit"))
		cmd_exit(s, data);
	// If the command is "unset", execute the unset command and update the global exit status
	else if (streq(s->argv[0], "unset"))
		g_exit_status = call_cmd_unset(s, data);
	// If the command is "export", execute the export command and update the global exit status
	else if (streq(s->argv[0], "export"))
		g_exit_status = ft_export(s, data);
	// If the command is "cd", execute the cd command and update the global exit status
	else if (streq(s->argv[0], "cd"))
		g_exit_status = call_cmd_cd(s, data);
	// If the command contains '=' and is a valid identifier, save it as a user variable and update the global exit status
	else if (ft_strchr(s->argv[0], '=') && is_valid_id(s->argv[0]))
		g_exit_status = save_user_vars(s->argv[0],
				&data->envp_lst, false);
	// If the command is "echo", execute the echo command and update the global exit status
	else if (streq(s->argv[0], "echo"))
		g_exit_status = call_cmd_echo(s);
	// If the command is "pwd", execute the pwd command and update the global exit status
	else if (streq(s->argv[0], "pwd"))
		g_exit_status = ft_pwd();
	// If the command is "env", execute the env command and update the global exit status
	else if (streq(s->argv[0], "env"))
		g_exit_status = ft_env(data);
	// If the command is not a built-in command, return false
	else
		return (false);
	// If the command is a built-in command, return true
	return (true);
}
