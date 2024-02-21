/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocheong <cocheong@student.42kl.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:57:14 by cocheong          #+#    #+#             */
/*   Updated: 2024/01/17 14:57:14 by cocheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

long long	g_exit_status = 0;

// Function to get input from the user
static char	*get_input(void)
{
	// Read a line from the user
	char	*raw_input = readline("minishell$ ");
	// Trim leading and trailing spaces and tabs from the input
	char	*input = trim_free(raw_input, " \t");
	// Return the trimmed input
	return (input);
}

// Function to clean up the parsed statement list
static void	clean_parsed(t_statement **statement_list, t_data *data)
{
	// Clear the statement list
	p_lstclear(statement_list);
	// Set the statement list to NULL
	*statement_list = NULL;
	// Set the head of the list to NULL
	data->head = NULL;
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i += 1;
	}
	if (src[i] && i < n)
	{
		while (i < n)
			dest[i++] = '\0';
	}
	dest[i] = '\0';
	return (dest);
}

// Function to trim leading and trailing characters from a string and free the original string
char	*trim_free(char *s1, char const *set)
{
	// Initialize the beginning and end indices and the trimmed string
	size_t	beg;
	size_t	end;
	char	*trimmed_str;

	// If the string or the set is NULL, return NULL
	if (!s1 || !set)
		return (NULL);
	// Find the first character in the string that is not in the set
	beg = 0;
	while (s1[beg] != '\0' && ft_strchr(set, s1[beg]) != NULL)
		beg += 1;
	// Find the last character in the string that is not in the set
	end = ft_strlen(s1 + beg);
	while (end > beg && ft_strchr(set, s1[(beg + end) - 1]) != NULL)
		end -= 1;
	// Allocate memory for the trimmed string
	trimmed_str = malloc((end + 1) * sizeof(char));
	if (!trimmed_str)
		return (NULL);
	// Copy the characters from the beginning to the end into the trimmed string
	ft_strncpy(trimmed_str, (s1 + beg), end);
	// Free the original string
	free(s1);
	// Return the trimmed string
	return (trimmed_str);
}

// // Main function
// int	main(int ac, char **av, char **envp)
// {
// 	// Initialize the data structure, the statement list, and the input string
// 	t_data		data;
// 	t_statement	*statement_list;
// 	char		*input;

// 	// If there are more than one arguments, exit with an error
// 	if (av && ac > 1)
// 		panic(NULL, CL_ARGUMENTS_ERR, EXIT_FAILURE);
// 	// Set up the shell
// 	setup_shell(envp, &data, &statement_list);
// 	// Main loop
// 	while (1)
// 	{
// 		// Get input from the user
// 		input = get_input();
// 		// If the input is not valid, continue to the next iteration
// 		if (!valid_input(input, &data))
// 			continue ;
// 		// Add the input to the history
// 		add_history(input);
// 		// Expand the input
// 		input = expander(input, &data);
// 		// If the input is empty, free it and continue to the next iteration
// 		if (!input[0])
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		// Parse the input into a statement list
// 		statement_list = parser(input);
// 		// Set the head of the list to the statement list
// 		data.head = statement_list;
// 		// Execute the type of statement
		// exec_type(statement_list, &data);
// 		// Clean up the parsed statement list
// 		clean_parsed(&statement_list, &data);
// 	}
// 	// Return success
// 	return (EXIT_SUCCESS);
// }

void print_statements(t_statement *head) 
{
	t_statement *current = head;

	while (current != NULL) {
		// Assuming that your t_statement structure has a member named 'command'
		// that is a null-terminated array of strings.
		char **args = current->argv;
		while (*args != NULL) {
			printf("%s ", *args);
			args++;
		}
		printf("\n");
		current = current->next;
	}
}

int main(int ac, char **av, char **envp) {
	t_data		data;
	t_statement	*statement_list;
	char		*input;

	setup_shell(envp, &data, &statement_list);

	while (1) {
		char *input = get_input();
		add_history(input);
		if (input == NULL) {
			fprintf(stderr, "Failed to get input\n");
			return 1;
		}

		// If the user entered 'exit', break the loop
		if (strcmp(input, "exit") == 0) {
			free(input);
			break;
		}

		t_statement *statements = parser(input);
		print_statements(statements);

		// Don't forget to free the memory allocated by parser
		// You might need to write a function to do this, depending on how your
		// t_statement structure is defined.

		free(input); // Assuming get_input allocates memory for the input
	}

	return 0;
}

