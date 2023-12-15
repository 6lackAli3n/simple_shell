#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 on success
 */
int main(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	while (1)
	{
		printf("#cisfun$ ");
		characters = getline(&buffer, &bufsize, stdin);
		if (characters == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}
		buffer[strcspn(buffer, "\n")] = '\0';

		if (fork() == 0)
		{
			char **args = malloc(2 * sizeof(char *));

			if (args == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			args[0] = buffer;
			args[1] = NULL;

			execve(buffer, args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}
	free(buffer);
	return (0);
}
