#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
  int status;
  int fpid;
  fpid = fork();

  if(fpid<0){
      printf("Error!\n");
      exit(0);
    }

  else if (fpid == 0){
      execl("/bin/echo","Hello World!",NULL);

    }

  else if(fpid > 0){
      int ret = waitpid(fpid,&status,0);
      printf("子进程标识数为 %d\n",ret);
    }
  return 0;
}