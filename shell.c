#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * executeCommand - Executes a command and performs some operation.
 *
 * @command: The command to be executed.
 * Return: On success, returns 0. failure, returns -1
 */
int executeCommand(const char *command)
{
	if (fork() == 0)
	{
		/*Child process*/
		execlp(command, command, (char *)NULL);
		perror("Error executing command");
		exit(EXIT_FAILURE);
	}
	else
	{
		/*Parent process*/
		wait(NULL); /*Wait for the child to finish*/
	}
	return (0); /*Placeholder return value for success, modify as needed*/
}

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 on success
 */
int main(void)
{
	executeCommand("/bin/ls");

	for (int i = 0; i < 3; ++i)
	{
		executeCommand("/bin/ls");
	}
	for (int i = 0; i < 4; ++i)
	{
		executeCommand("/bin/ls");
	}
	if (fork() == 0)
	{
		/*Child process for copying*/
		execlp("/bin/cp", "cp", "/bin/ls", "hbtn_ls", (char *)NULL);
		perror("Error copying file");
		exit(EXIT_FAILURE);
	}
	else
	{
		/*Parent process*/
		wait(NULL); /*Wait for the copy process to finish*/
		if (fork() == 0)
		{
			/*Child process for executing ./hbtn_ls /var*/
			execlp("./hbtn_ls", "hbtn_ls", "/var", (char *)NULL);
			perror("Error executing hbtn_ls");
			exit(EXIT_FAILURE);
		}
		else
		{
			/*Parent process*/
			wait(NULL); /*Wait for the child to finish*/
		}
		}
	return (0);
}
