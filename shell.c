/****************************************************************** 
 * Small shell program created to perform various shell functions
 * such as exit, cd, showpid, and ls. This program uses the fork()
 * system call to perform these shell functions.
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//Function for the built-in commands.
void builtCmds(char **args, pid_t pid)
{
	if (strcmp(args[0], "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		chdir(args[1]);
	}
	else if (strcmp(args[0], "showpid") == 0)
	{
		printf("Current process id is: %d\n", getpid());
		printf("Child process id is: %d\n", pid);
	}	
}

int main(int argc, char* argv[])
{
	char cwd[100];
	char input[100];
	char *args[30];
	char *token;
	int i;
	int k = 0;
	int status;
	pid_t pid;
	
	do {
		pid = fork();
		
		if (pid < 0) //Prints if the fork failed
		{
			printf("Forking Failed\n");
		}
		else if (pid == 0) //Child Process
		{
			if (execvp(args[0], args) < 0 && (strcmp(args[0], "exit") != 0 && strcmp(args[0], "cd") != 0 && strcmp(args[0], "showpid") != 0))
			{
				printf("Error: Command could not be executed\n");
			}
			
			exit(0);
		}
		else
		{
			waitpid(pid, &status, WUNTRACED);
		
			//Chose the color red for my prompt.
			printf("\033[1;31m");
			printf("%s$ ", getcwd(cwd, 100));
			fgets(input, 100, stdin);
			input[strlen(input) - 1] = '\0';
		
			//Allocated memory for the arguments.
			for (i = 0; i < 30; i++)
			{
				args[i] = (char*) malloc(20 * sizeof(char));
			}
		
			//Seperating the arguments into tokens and adding them to the arguments array.
			token = strtok(input, " ");
			strcpy(args[k++], token);
		
			while (token != NULL)
			{
				token = strtok(NULL, " ");
			
				if (token == NULL)
				{
					break;
				}
	
				strcpy(args[k++], token);
			}
		
			args[k] = NULL;
			
			if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "cd") == 0 || strcmp(args[0], "showpid") == 0)
			{
				builtCmds(args, pid);
			}
			
			k = 0;
		}
		
		fflush(stdin);
	}
	while (1);

	return 0;
}
