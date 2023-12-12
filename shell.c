#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/**
 * display_prompt - A command line alawys ends with anew line
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * read_command - Read a command from the user
 *
 * Return: The entered command or NULL on end-of-file
 */
char *read_command(void)
{
	char *command = NULL;
	size_t bufsize = 0;

	if (getline(&command, &bufsize, stdin) == -1)
	{
		free(command);
		return (NULL);
	}
	command[strcspn(command, "\n")] = '\0';
	return (command);
}

/**
 * execute_command - Execute a command using execve
 * @command: The command to be executed
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *command)
{
	pid_t pid;
	char *args[2];
	
	args[0] = command;
	args[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		extern char **environ;
		if (execve(command, args, environ) == -1)
		{
			fprintf(stderr, "%s: No such file or directory\n", command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
	return (0);
}

/**
 * main - Entry point for the simple shell program
 *
 * Return: Always 0
 */
int main(void)
{
	char *command;

	while (1)
	{
		display_prompt();

		command = read_command();

		if (command == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		execute_command(command);
		free(command);
	}
	return (0);
}
