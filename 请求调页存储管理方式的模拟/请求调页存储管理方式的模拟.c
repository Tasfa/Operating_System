#include<stdlib.h>

#include<stdio.h>
#define Bsize 4
typedef struct BLOCK//����һ��������--���������
{  
   int pagenum;//ҳ��
   int accessed;//�����ֶΣ���ֵ��ʾ���δ������
}BLOCK; 
int pc;//�����������������¼ָ������
int n;//ȱҳ��������������¼ȱҳ�Ĵ��� 
float r;//��¼ȱҳ��
static int temp[320];//�����洢320�������
BLOCK block[Bsize]; //����һ��СΪ4�����������
void init( )  //�����ʼ������
{  
 int i=0;
   for(i=0;i<Bsize;i++) 
   {
    block[i].pagenum=-1; //��ʼ��ÿ�������ҳ�Ŷ���-1����ʾ��û�з����ҳ
       block[i].accessed=0;  //��ʼ�������ֶζ���0����ʾ��û�б�����
       pc=n=0;               
   }
}
//-------------------------------------------------------------
int findExist(int curpage)  //������������Ƿ��и�ҳ��
{
 
 int i;
    for(i=0; i<Bsize; i++)
 {
       if(block[i].pagenum == curpage )   //����ҵ�һ��������ҳ����Ҫ����ĸ�ҳ��ҳ����ȣ��ͽ�����block�����е�λ�÷���
 
           return i;
 }
    return -1;   //���򣬷���-1
}
//-------------------------------------------------------------
int findSpace( )    //�����Ƿ��п��������
{   
 int i=0;
 for(i=0; i<Bsize; i++)
  {
  if(block[i].pagenum == -1)    //����ҵ���������ҳ��Ϊ-1����ʾ������黹û�б����䵽�ض���ҳ
        return i;//�����е�block��λ�÷���
 } 
    return -1;
}
//-------------------------------------------------------------
int findReplace( )   //ͨ���Ƚ�4�������������accessed���ҵ�����Ӧ���û���ҳ��
{
 int i=0;
   int pos = 0;
   for(i=0; i<Bsize; i++)
   {
    if(block[i].accessed >block[pos].accessed)   
         pos = i;//�ҵ�Ӧ���û�ҳ�棬����BLOCK��λ��
   }
   return pos;
}
//-------------------------------------------------------------
void display( )
{
 int i=0;
   for(i=0; i<Bsize; i++)
   {
       if(block[i].pagenum != -1)     //������鱻�����ʱ�򣬴�ӡ�����ҳ��
  printf(" %02d",block[i].pagenum);
   }
   printf("\n");
}
//-------------------------------------------------------------
void suijishu( )           //����320�������,��ʾ���洢��temp[320]
{  
 int i=0;
 int flag=0;
    scanf("%d",&pc);       //�����ʼλ��
    printf("******����Ҫ�������320���������*******\n");
    for(i=0;i<320;i++)
 {    
  temp[i]=pc;  
  //�ּ��������������˳�����ָ�����ǰ��ַ���ߺ��ַ
  if(flag%2==0) pc=++pc%320;     
        if(flag==1) pc=rand( )% (pc-1);
        if(flag==3) pc=pc+1+(rand( )%(320-(pc+1)));
        flag=++flag%4;
  printf(" %03d",temp[i]);
        if((i+1)%10==0) 
    printf("\n");
 } 
}
//-------------------------------------------------------------
void pagestring( )    
{   
 int i=0;
 for(i=0;i<320;i++)
 {
    printf(" %02d",temp[i]/10);   //��ӡָ��������ҳ�ţ�ÿʮ��ָ����һ��ҳ
       if((i+1)%10==0)            //ÿʮ���Ͷ���
     printf("\n");
 }
}
//-------------------------------------------------------------
void OPT( )                      //����û��㷨
{
 int exist,space,position ;
 int curpage,k,j,i=0;
 
 for(i=0;i<320;i++)
 {    
  pc=temp[i];    //ÿһ�ζ���Ҫִ�е�ָ���PC
  curpage=pc/10;    //�������ڵ�ҳ��
  exist = findExist(curpage);   //ͨ�������������ҳ�Ƿ��Ѿ������������
    if(exist==-1)    //���û�з���
    {
   space = findSpace ( );  //ͨ�������ҿ��������
            if(space != -1)    //����ڴ�û�������Ͱ��ҵ�������鸳����ҳ�������޸�ҳ�ź�ȱҳ��
   {
    block[space].pagenum = curpage;  
                display( );
    n=n+1;
   }
            else
   { 
    //����ڴ����Ѿ����ˣ��Ͱ���OPT�����û�
    //�ڼ���������н��бȽ�
    for(k=0;k<Bsize;k++)
    {
     //��δ����ָ���У��ҵ�������ʹ�õ�����飬Ҳ���Ǹ�ҳ�������޶�Ӧ��ָ��
     for(j=i;j<320;j++)
     {
      if(block[k].pagenum!= temp[j]/10)
      { 
       //���������ָû��ָ���ҳ��������ȣ���Զ���������ϣ���������Ϊ�ܴ����
       block[k].accessed = 1000; 
      }
                        else
      {
       //����������˵���ڵ�j��ָ���ʱ��Ż����ϸ�ҳ�棬���԰�accessed����Ϊj
       block[k].accessed = j;
       break;//�ҵ��������Ҫ�õ���ǰҳ�ŵ�ָ��֮�������ѭ��
                           
      }
     }
    }
               
    position = findReplace( );    //����findReplace�������Ƚϳ����ʱ�򲻻��õ������
    
    block[position].pagenum = curpage;  //�޸���ز��� 
                display( );
    n++;
   }
  }
 }
 //����ȱҳ������ȱҳ��
	r=((float)(n*100))/320;
	printf("ȱҳ����:%d\n",n);
	printf("ȱҳ��:%f%\n",r);
}
//-------------------------------------------------------------  
void LRU( )      //������ûʹ���㷨
{
 int i,j;
 int exist,space,position ;
 int curpage;
    for(i=0;i<320;i++)
 {   
  //����������һ�����ȼ���ҳ���Լ���ҳ���Ƿ�����������
  pc=temp[i]; 
  curpage=pc/10;
  exist = findExist(curpage);
        if(exist==-1)
  {
   space = findSpace( );
            if(space != -1)
   {
    block[space].pagenum = curpage;  
                display( );
    n=n+1;
   }
            else
   {
                position = findReplace( );   //���ݺ����ҵ������û���õ�ҳ��
                block[position].pagenum = curpage;   //�޸���ز���
                display( );
    n++;
   }
  }
        else 
   block[exist].accessed = -1;//���ҳ����ڣ��ͽ��շ��ʹ���BLOCK��ҳ��accessed��Ϊ-1��������Ϣ
        for(j=0; j<4; j++)
        {
   block[j].accessed++;   //��������û�б����ʵ�ҳ���accessed�ͻ�+1
  }
 }
	r=((float)(n*100))/320;
	printf("ȱҳ����:%d\n",n);
	printf("ȱҳ��:%f%\n",r);
}
//-------------------------------------------------------------
void FIFO( )       //�Ƚ��ȳ��㷨
{
 int i,j;
 int exist,space,position ;
 int curpage;
    for(i=0;i<320;i++)
 {   
  //��Щ�����������㷨��ͬ
  pc=temp[i]; 
  curpage=pc/10;
  exist = findExist(curpage);
        if(exist==-1)
        {
   space = findSpace( );
            if(space != -1)
   {
    block[space].pagenum = curpage;  
                display( );
    n=n+1;
   }
            else
   {
                position = findReplace( );   
                block[position].pagenum = curpage;   
                display( );
    n++;
    //�µ���ҳ���������accessed�ͻ�-1 
    block[position].accessed--;
   }
  }
  for(j=0; j<Bsize; j++)
        block[j].accessed++;   //�����������ͻ��1�����������Ƚ���������.accessed�ͻ�ȸս����Ҫ��
 }
	r=((float)(n*100))/320;
	printf("ȱҳ����:%d\n",n);
	printf("ȱҳ��:%f%\n",r);
}
//*************************************************************
void main( )
{ 
  int  select;
  printf("�������һ��ָ���(0~320)��");
  suijishu( );
  printf("*****��Ӧ�ĵ���ҳ�����*******\n");
  pagestring( );
  do
  { 
   printf("****************************************\n");
      printf("------1:OPT   2:LRU  3:FIFO  4:�˳�-----\n");
      printf("****************************************\n");
      printf("          ��ѡ��һ��ҳ���û��㷨:"); 
   scanf("%d",&select);
      printf("****************************************\n");
   init();
  
  switch(select)
  {
  case 1:printf("����û��㷨OPT:\n");
             printf("*****************\n");
             OPT( );
          break;
      case 2:printf("������δʹ���û��㷨LRU:");
             printf("**************************");
             LRU( );
             break;
      case 3:printf("�Ƚ��ȳ��û��㷨FIFO:");
   printf("*********************");
             FIFO( );
          break;
      defult: ;
   }
 }while(select!=4);
}	          