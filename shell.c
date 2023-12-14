#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


#define BUFFER_SIZE 1024
/**
 * display_prompt - Display the shell prompt
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}

/**
 * execute_command - Execute a command in a child process
 * @buffer: The command to be executed
 *
 * This function forks a child process and executes the given command.
 *
 * Return: Always 0 on success
 */
int execute_command(char *buffer, char **environ)
{
	char *cmd_args[2];
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		cmd_args[0] = buffer;
		cmd_args[1] = NULL;

		if (execve(buffer, cmd_args, environ) == -1)
		{
			perror(buffer);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			fprintf(stderr, "%s: not found\n", buffer);
		}
	}
	return (0);
}
/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 on success
 */
int main(void)
{
	char buffer[BUFFER_SIZE];

	extern char **environ;

	while (1)
	{
		display_prompt();
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		buffer[strcspn(buffer, "\n")] = '\0';

		execute_command(buffer, environ);
	}
	return (EXIT_SUCCESS);
}
