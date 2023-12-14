#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 on success
 */
int main(void)
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
			buffer[strlen(buffer) - 1] = '\0';
			if (execlp(buffer, buffer, NULL) == -1)
			{
				perror(buffer);
			}
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}

	free(buffer);
	return (0);
}
