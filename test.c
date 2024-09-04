#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

//Function for the built-in commands
void builtCmds(char** args) 
{
	if (strcmp(args[0], "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		chdir(args[1]);
		setenv(args[1], args[1], 1);
	}
	else if (strcmp(args[0], "showpid") == 0)
	{
		printf("%d\n", getpid());
	}
}

int main(int argc, char* argv[]) 
{
	char input[100];
	char s[100];
	char* token;
	char* args[80];
	char* dir;
	int i = 0;
	int k = 0;
	int status = 0;
	pid_t pid;

	do
	{
	 	//Chose the color red for my prompt
		printf("\033[1;31m");
		printf("%s$ ", getcwd(s,100));
		fgets(input, 100, stdin);
    		input[strlen(input) - 1] = '\0';

		//Allocated memory for the arguments.
    		for(i = 0; i < 10; i++)
    		{
	    		args[i] = (char*)malloc(20 * sizeof(char));
    		}

		//Seperating the arguments into tokens and adding them to the arguments array.
    		token = strtok(input," ");
    		strcpy(args[k++], token);

    		while (token != NULL)
    		{
      			token = strtok(NULL," ");

      			if(token == NULL)
			{
        			break;
			}

      			strcpy(args[k++], token);
    		}

    		args[k] = NULL;
    		pid = fork();

		//If statement if the first argument is a built-in command
		if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "cd") == 0 || strcmp(args[0], "showpid") == 0)
		{
			builtCmds(args);
		}

		if (pid < 0) // Prints if the fork failed
		{
			printf("Forking Failed\n");
		}
    		else if (pid == 0) //Child Process
    		{
      			if(execvp(args[0], args) < 0)
		  	{
       				printf("Error: Command could not be executed\n");
			}
			
			exit(0);
   		}
    		else //Parent Process
    		{
      			waitpid(pid, &status, WUNTRACED);
      			input[0] = '\0';
      			k = 0;
      			*args = NULL;
    		}
		
		fflush(stdin); 	
 	 } while(1);
}
