#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define MAX_INPUT 1024

/**
 * display_prompt - Display the shell prompt
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * execute_command - Execute a command using execve
 * @command: The command to be executed
 *
 * Return: 0 on success, -1 on failure
 */
void execute_command(char *command)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error forking");
	}
	else if (child_pid == 0)
	{
		char *args[2];

		args[0] = command;

		args[1] = NULL;

		if (execve(command, args, NULL) == -1)
		{
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}

/**
 * main - Entry point for the simple shell program
 *
 * Return: Always 0
 */
int main(void)
{
	char input[MAX_INPUT];

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		display_prompt();

		if (fgets(input, MAX_INPUT, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			break;
		}
		execute_command(input);
	}
	return (EXIT_SUCCESS);
}
