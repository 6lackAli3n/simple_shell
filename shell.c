#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * interactive_mode - Enters interactive mode,
 * allowing the user to input commands.
 */
void interactive_mode(void)
{
	char *input;
	size_t len = 0;

	while (1)
	{
		printf("($) ");
		if (getline(&input, &len, stdin) == -1)
		{
			 printf("\n");
			 free(input);
			 exit(EXIT_SUCCESS);
		}
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}

		process_command(input);
	}
}
/**
 * Processe_command - processes the given command by forking a
 * child process and executing the command.
 *
 * This function takes a command as input, forks a child process,
 * and executes the command
 * using execvp in the child process.
 * @param command: The command to be processed.
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
		char *args[100];
		int arg_count = 0;

		char *token = strtok(command, " ");
		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;
		
		execvp(args[0], args);
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}
