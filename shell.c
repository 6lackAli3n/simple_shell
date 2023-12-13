#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief - Enters interactive mode, allowing the user to input commands.
 *
 * This function starts an interactive shell session
 * where the user can input commands.
 * It reads the commands, processes them, and
 * displays the result until the user decides to exit.
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
 * @brief - Processes the given command by forking a child process and
 * executing the command.
 *
 * This function takes a command as input, forks a child process,
 * and executes the command
 * using execvp in the child process.
 * It waits for the child process to finish in the parent process.
 *
 * @param command The command to be processed.
 */
void process_command(char *command)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		if (execlp(command, command, (char *)NULL) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}
