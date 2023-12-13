Simple Shell

This is a simple UNIX command line interpreter developed as part of a school project. The shell supports basic command execution and handles command lines with arguments.

Table of Contents
Description
How to Use
Project Structure
Authors
License
Description
The simple shell is a basic implementation of a command line interpreter following the project requirements. It supports interactive mode, handles simple commands, and processes command lines with arguments. The project adheres to the specified coding style, uses system calls, and includes essential features outlined in the project guidelines.

How to Use
Compilation:

bash
Copy code
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
Run in Interactive Mode:

bash
Copy code
./hsh
Example Usage:

bash
Copy code
($) /bin/ls
Exit Shell:

bash
Copy code
($) exit
Run in Non-Interactive Mode:

bash
Copy code
echo "/bin/ls" | ./hsh
Project Structure
main.c: Entry point for the shell.
shell.h: Header file containing function prototypes and necessary includes.
shell.c: Implementation of shell functionalities, including interactive mode and command processing.
README.md: Project documentation.
AUTHORS: File listing contributors to the project.
Other Files: Additional files as needed.
