#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>


int process_str(char *str,char arglist[100][100],int *nargs)
{
	int i=0,j=0,k=0;
	while(str[i]!='\0')
	{

    	if (str[i]=='\n')
    	{
        	i++;
        	continue;

    	}
    	else if(str[i]!= ' ')
    	{
        	arglist[j][k++]=str[i++];
    	}
  	 
    	else
    	{
        	(*nargs)++;
        	arglist[j][k]='\0';

        	j++;
        	k=0;
        	i++;

    	}
	}
	return 0;
}

void prompt()
{
 fprintf(stderr, "akesh@atlas:-$ " );
}


int main( int argc, char **argv)
{
	int n,argno=0,i=0,fd1,fd2,pos,h, hcnt=0;
	char ch;
	char history[50][100];
	char path[100],buf[100],path1[100],path2[100];
	int pid;
	char str[100], arglist[100][100];
	printf("WELCOME TO LINUX MINI_SHELL\n");
	printf("My minishell commands are mycat, myhead, mytail, mycp, myrm, mywc, history, myhelp, exit\n");
	while(1)
	{
    	strcpy(path,"./");
    	argno=0;
    	prompt();
	fflush(stdin);
    	n= read(0,str,100);
    	memset(arglist,0,sizeof(arglist));
    	str[n]='\0';
    	process_str(str,arglist,&argno);
	hcnt=hcnt%50;
	strcpy(history[hcnt++],str);
	for(i=0;i<=argno;i++)
    	{
        	printf("Arguments passed = '%s' \n",arglist[i]);

	}
	pid=fork();
	if(pid==0)
	{


		if(strcmp(arglist[0],"history")==0)
		{
			for(int i=0; i<hcnt;i++)
			{
				printf("%s",history[i]);
			}
		}

		else if(strcmp(arglist[0],"myhelp")==0)
		{
		printf("This is myshell which supports the following commands\n");
		printf("mycat	- displays context of a file\n");
		printf("myhead	- displays first 10 lines of a file\n");
		printf("mytail 	- displays last 10 lines of a file\n");
		printf("mycp	- copies data from one file to another\n");
		printf("myrm	- Delets the file\n");
		printf("mywc	- counts the characters/words/lines of a file\n");
		printf("history - shows the history of commands that used\n");
		printf("clear	- clears the screen\n");
		printf("exit	- exits from the shell\n");
		}
			
		else if(strcmp(arglist[0],"mycp")==0)
            	{
            	printf("This is my version of cp command\n");
            	strcat(path,arglist[i]);
            	fd1 = open(arglist[1],O_RDONLY);
                	if(fd1<0)
            	{
                	printf("Open Error\n");
            	}
			else
			{
            	strcpy(path,"./");
            	strcat(path,arglist[2]);
            	printf("dest path = %s\n",path);
            	fd2= open(arglist[2],O_RDWR|O_CREAT, 0666);

            			if(fd2<0)
            			{
                	printf("Open Error\n");
            			}
				else
				{
            	while((n=read(fd1,buf,100))>0)
            	{
                	write(fd2,buf,n);
            	}
		printf("Successfully copied\n");
            	close(fd1);
            	close(fd2);
				}
			}
            	}



        	else if(strcmp(arglist[0],"mymv")==0)
           	{
			fd1 = open(arglist[1],O_RDONLY);
			fd2 =open(arglist[1],O_RDONLY);
                if(fd1<0||fd2<0){
                        printf("source/destination file not found, cat not possible\n");
                }
		else 
		{
        	strcpy(path1,"./");
        	strcpy(path2,"./");
        	strcat(path1,arglist[1]);
        	strcat(path2,arglist[2]);
        	rename(path1,path2);
		printf("sucessfully movied the data\n");
		}

           	}


        	else if(strcmp(arglist[0],"mycat")==0)
            	{
            	printf("This is my version of cat command\n");
            	fd1 = open(arglist[1],O_RDONLY);
		if(fd1<0){
			printf("source file not found, cat not possible\n");
		}
		else
		{
            	while(1)
            	{
                	n = read(fd1,&ch,1);
                	if (n==0)
                    	break;
                	else
                    	printf("%c",ch);
            	}
            	close(fd1);
		}
            	}


        	else if(strcmp(arglist[0],"myrm")==0)
	    	{
        	printf("This is my version of rm command\n");
        	fd1=open(arglist[1],O_RDONLY);
        	if(fd1<0)
        	{
            	printf("Source File not found, Copy not possible\n");
        	}
		else
		{
        	close(fd1);
        	unlink(arglist[1]);
		printf("sucessfully removed\n");
		}
    	}



    	else if(strcmp(arglist[0],"mytail")==0)
    	{
        	FILE * fp;
    	fp = fopen(arglist[1],"r");
 	 
    	if( fp == NULL )
       	{
    	printf("\n%s file can not be opened !!!\n",arglist[1]);   
        }
	else
       	{
    	char message[10][511],buffer[511];
    
    	while(fgets(buffer,511,fp))
		{
        	strcpy(message[i++],buffer);
        	if (i>9) i=0;
	    	}
    	fclose(fp);
    	int n=0;
    	while(n<10)
    	printf("%s",message[(i+n++)%10]); 
    	}
	}



    	else if(strcmp(arglist[0],"myhead")==0)
    	{
        	FILE	*   fp;     	 
        	char *line = NULL;
        	size_t len  = 0;
        	int cnt = 0;    
    	 
        	fp = fopen(arglist[1],"r");
        	if( fp == NULL )
       		{
        	printf("\n%s file can not be opened !!!\n",arglist[1]);
        	   
        	}
 		else
		{
        	while (getline(&line, &len, fp) != -1)
        	{
            	cnt++;
            	if ( cnt > 10 )
                	break;
            	printf("%s",line);
           	fflush(stdout);
        	}
        	fclose(fp);
		}
    	}
 	
	else if(strcmp(arglist[0],"mywc")==0)
	{
	int w=0,l=0,c=0;
	fd1=open(arglist[1],O_RDONLY);
	if(fd1<0)
	{
		printf("souce file not found, copy not possible");
		exit(0);
	}
	else
	{
		while(1)
		{
			n=read(fd1,&ch,1);
			if(n==0)
				break;
			else {

				if(ch==' ')
				{	
                        	        c++;
                                	w++;
                      		  }
				else if(ch=='\n')
				{	
                	                
                        	        l++;
					w++;
	                        }
				else {
					c++;
				}
        	                
			}
		}
	printf(" characters =%d words =%d  lines =%d \n",c,w,l);
        close(fd1);

	}
	}


 	else if(strcmp(arglist[0],"exit")==0)
	{
    	printf("Exiting from the Mini_Shell\n");
    	exit(1);
	}

	else if(strcmp(arglist[0],"clear")==0)
	{
	system("clear");
	printf("WELCOME TO LINUX MINI_SHELL\n");
        printf("My minishell commands are mycat, myhead, mytail, mycp, myrm, myhistory, exit\n");

	}

	else
	{
		printf("Wrong command passed\n");
		printf("Use myhelp command for more information\n");
	}
	}
    	else if(pid>0)
    	{
    	 wait(NULL);
    	 exit(0);
	}
	

}
}

