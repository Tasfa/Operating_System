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
      printf("�ɹ������ӽ���1,���ʶ��Ϊ%d\n",getpid());
    }
  else{
      printf("�����̣���ʶ��Ϊ%d\n",getpid());
      fpid2 = fork();
      if(fpid2<0)
          {
            printf("error!\n");
            exit(1);
          }
      else if(fpid2==0){
            printf("�ɹ������ӽ���2,���ʶ��Ϊ%d\n",getpid());
          }
      else{
            printf("�����̣���ʶ��Ϊ%d\n",getpid());
          }

    }
  return 0;
}