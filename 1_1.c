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
		}
		
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



int mystrtok(char *argv[],char *string)
{
 int i=0;
 char delim[]=" ";
 char *p;
 argv[0]=strtok(string,delim);//字符串分割函数的使用 把命令分割开
 //printf("%s\n",argv[0]);
 while(argv[i]!=NULL)
 {
  argv[++i]=strtok(NULL,delim);
  //printf("%s is %d\n",argv[i],i);
 }
return 0;
}


char *getusername(char buffer[NUM])
{
 uid_t userid;
 char *username;
 char *hostname;
 char *ptr,*p;
 char buf1[1024],buf2[1024];
 char *delim=".";
 int id;
 getwd(buf2);//这段代码说明的是对命令提示的路径获得
 username=getenv("USER");//调用getenv函数，来获得shell命令的提示中的用户名
 strcpy(buffer,username);
 strcat(buffer,"@");
 id=gethostname(buf1,sizeof buf1);//调用此函数来获取shell命令的提示中的主机名
 p=strtok(buf1,delim);//对主机进行截取
 strcat(buffer,p);//字符串的连接函数
 ptr=strrchr(buf2,'/');//字符串的从后往前进行截取的函数，讲多得shell命令提示中的路径
 //比较字符串，判断用户的路径是在"/","~",还是其他当中
 if(strcmp(ptr,"/")==0)
 {
  ptr="/";
 }
 else if(strcmp(ptr,"~")==0)
 {
  ptr="~";
 }
 else
 {
  ptr=strtok(ptr,"/");
  
 }
 strcat(buffer," ");  //把获得的 [用户名@主机名  路径]连接在一起
 strcat(buffer,ptr);
return buffer;
}










