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
		if (access(buffer, F_OK | X_OK) != 0)
		{
			perror(buffer);
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
	char *token;
	char *path;
	char *path_token;

	token = strtok(buffer, " ");

	buffer[strlen(buffer) - 1] = '\0';

	path = getenv("PATH");
	path_token = strtok(path, ":");

	for (i = 0;  token != NULL; i++)
	{
		args[i] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;

	while (path_token != NULL)
	{
		char *full_path = malloc(strlen(path_token) + strlen(args[0]) + 2);

		sprintf(full_path, "%s/%s", path_token, args[0]);
		if (access(full_path, X_OK) == 0)
		{
			if (execve(full_path, args, NULL) == -1)
			{
				perror(args[0]);
			}
			free(full_path);
			exit(0);
		}
		free(full_path);
		path_token = strtok(NULL, ":");
	}
	perror(args[0]);
	exit(127);
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
