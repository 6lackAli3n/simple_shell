#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


void execute_command(char *buffer);

/**
 * handle_user_input - Handle user input,
 * prompt for commands, and execute them
 *
 */
void handle_user_input(void)
{
	char *buffer;
	size_t bufsize = 32;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	while (1)
	{
		printf("$ ");
		getline(&buffer, &bufsize, stdin);

		if (buffer[0] == '\n')
		{
			continue;
		}
		if (fork() == 0)
		{
			execute_command(buffer);
		}
		else
		{
			wait(NULL);
		}
	}
	free(buffer);
}
/**
 * execute_command - Execute a command with its arguments
 *
 * @buffer: The command line input to be executed
 */
void execute_command(char *buffer)
{
	char *args[32];
	int i;

	char *token = strtok(buffer, " ");

	buffer[strlen(buffer) - 1] = '\0';

	for (i = 0;  token != NULL; i++)
	{
		args[i] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	if (execvp(args[0], args) == -1)
	{
		perror(args[0]);
	}
	exit(0);
}
/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 on success
 */
int main(void)
{
	handle_user_input();
	return (0);
}
