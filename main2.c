#include <stdio.h>
#include <stdlib.h>
#include "includes/minishell.h"

long long	g_exit_status = 0;

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

int main() {
	char *input = NULL;
	size_t len = 0;
	printf("Enter a command: ");
	getline(&input, &len, stdin);

	t_statement *statements = parser(input);
	print_statements(statements);

	// Don't forget to free the memory allocated by parser
	// You might need to write a function to do this, depending on how your
	// t_statement structure is defined.

	return 0;
}