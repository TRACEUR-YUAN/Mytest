#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LINE 80 


int Input(char * command, const char* delim, char* args[]);
int contain(char * str, int length, char c);
void freeMem(char * args[], int length);


int main(void)
{  
	char *args[MAX_LINE/2 + 1];
	int should_run = 1; 
	int index = 0;    
	char command[MAX_LINE];   

	while (should_run) 
	{        
		printf("osh> ");      
		fflush(stdout);       
		fgets(command, MAX_LINE, stdin);  
		index = Input(command, " !&\n", args);  
		if(args[0] != NULL && strcmp(args[0], "exit") == 0)
		{         	
			should_run = 0;  
		} 
		else
		{     
			pid_t pid;  
			pid = fork();    
			if (pid < 0) 
			{          
				exit(-1);    
			}  
			else if (pid == 0)
			{ 
				if (execvp(*args, args) < 0) 
				{         
					exit(-1); 
				} 
			}   
			else 
			{  
				if(contain(command, (int)strlen(command), '&') == 0)
				{    
					while (wait(NULL) != pid);   
				}  
			}  	
		}    
		memset(command, 0, strlen(command) * sizeof(char));    
		freeMem(args, index);   
	}   

	return 0;
	}

	
	
int Input(char * command, const char* delim, char* args[])
{   
	char *s = strdup(command);   
	char *token;
	int n = 0;
	for(token = strsep(&s, delim);token != NULL; token = strsep(&s, delim)) 
	{       
		if(strlen(token) > 0) 
		{
			args[n] = (char*) malloc(strlen(token) * sizeof(char));
            strcpy(args[n++], token);    
		}  
	} 
	free(s);  
	return n;
}

int contain(char * str, int length, char c)
{
	for(int i = 0; i < length; i++) 
	{        
		if(*(str + i) == c) 
		{            
			return 1;        
		}    
	}    
	return 0;
}

void freeMem(char * args[], int length)
{    
	for(int i = 0; i < length; i++) 
	{
		if(args[i] != NULL)
		{
			free(args[i]);          
			args[i] = NULL;      
		}    
	}
} 
 
	
	
	