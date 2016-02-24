#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
  int fpid1,fpid2;
  fpid1 = fork();
  if(fpid1<0 )
    {
      printf("error!\n");
      exit(1);
    }
  else if(fpid1==0)
    {
      printf("成功创建子进程1,其标识数为%d\n",getpid());
    }
  else{
      printf("父进程，标识数为%d\n",getpid());
      fpid2 = fork();
      if(fpid2<0)
          {
            printf("error!\n");
            exit(1);
          }
      else if(fpid2==0){
            printf("成功创建子进程2,其标识数为%d\n",getpid());
          }
      else{
            printf("父进程，标识数为%d\n",getpid());
          }

    }
  return 0;
}