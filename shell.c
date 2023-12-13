#include "shell.h"

/**
 * Entry - Enters interactive mode, allowing the user to input commands.
 */
void interactive_mode(void)
{
	char *input;
	size_t len = 0;

	while (1)
	{
		printf("($) ");
		if (getline(&input, &len, stdin) == -1)
			break;

		input[strlen(input) - 1] = '\0';

		process_command(input);

		free(input);
		input = NULL;
		len = 0;
	}
}

/**
 * Entry - Processes the given command by forking a child process
 *
 * @param command The command to be processed.
 */
void process_command(char *command)
{
	printf("Command: %s\n", command);
}
