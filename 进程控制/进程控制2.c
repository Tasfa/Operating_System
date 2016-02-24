#include <stdio.h>
     #include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    int n;
    pid_t fpid;
    int fd[2],nby;
    char writes[100]="Hellow world , my pipe£¡my pid is:";
    char reads[100];
   
    if(pipe(fd)==-1)
    {
      printf("error in creating pipe!\n");
      exit(1);
    }
      fpid=fork();
     
      if(fpid==-1)
      {
	printf("error in fork!\n");
	exit(1);
      }
     
     if(fpid==0)
        {
            close(fd[0]);
	    char nums[20];
	    int  num;
	    num=getpid();
	    sprintf(nums,"%d\n",num);
	    strcat(writes,nums);
            n= write(fd[1],writes,sizeof(writes));
            printf("This is son,it's pid is: %d\n",getpid());
	    return 0;
        }
        else
        {
            close(fd[1]);
            nby=read(fd[0],reads,sizeof(reads));
            printf("This is parent,its's pid is :%d\n ",getpid());
	    printf("The parent receive the massage :%s",reads);
	    return 0;
        }       
return 0;}