#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main()
{
	pid_t pid = -1;
	int status,i,ret = 0;
	char *args[MAX_LINE/2 + 1];
	int should_run = 1;
	
	while(should_run)
	{
		printf("osh>");
		fflush(stdout);
		scanf("%s",args[0]);
		
		//判断参数是否含有&
		for(i = 0; i < (MAX_LINE/2 + 1); i++)
		{
				if(args[i] == "&")
				{
					ret = 1;
				}				
		}
		pid = fork();
		if(pid = 0)
		{
			execvp(args[0],args);
			exit(0);
		}
		//父进程
		if(pid > 0)
		{
			if(ret = 1)
			{
				wait(&status);
			}
		}
		
		
		
	}
	
	return 0;
}






