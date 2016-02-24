#include<stdlib.h>

#include<stdio.h>
#define Bsize 4
typedef struct BLOCK//声明一种新类型--物理块类型
{  
   int pagenum;//页号
   int accessed;//访问字段，其值表示多久未被访问
}BLOCK; 
int pc;//程序计数器，用来记录指令的序号
int n;//缺页计数器，用来记录缺页的次数 
float r;//记录缺页率
static int temp[320];//用来存储320条随机数
BLOCK block[Bsize]; //定义一大小为4的物理块数组
void init( )  //程序初始化函数
{  
 int i=0;
   for(i=0;i<Bsize;i++) 
   {
    block[i].pagenum=-1; //初始化每个物理块页号都是-1，表示还没有分配给页
       block[i].accessed=0;  //初始化访问字段都是0，表示还没有被访问
       pc=n=0;               
   }
}
//-------------------------------------------------------------
int findExist(int curpage)  //查找物理块中是否有该页面
{
 
 int i;
    for(i=0; i<Bsize; i++)
 {
       if(block[i].pagenum == curpage )   //如果找到一个物理块的页号与要分配的该页的页号相等，就将其在block数组中的位置返回
 
           return i;
 }
    return -1;   //否则，返回-1
}
//-------------------------------------------------------------
int findSpace( )    //查找是否有空闲物理块
{   
 int i=0;
 for(i=0; i<Bsize; i++)
  {
  if(block[i].pagenum == -1)    //如果找到有物理块的页号为-1，表示该物理块还没有被分配到特定的页
        return i;//将空闲的block的位置返回
 } 
    return -1;
}
//-------------------------------------------------------------
int findReplace( )   //通过比较4个物理块中最大的accessed，找到查找应予置换的页面
{
 int i=0;
   int pos = 0;
   for(i=0; i<Bsize; i++)
   {
    if(block[i].accessed >block[pos].accessed)   
         pos = i;//找到应予置换页面，返回BLOCK中位置
   }
   return pos;
}
//-------------------------------------------------------------
void display( )
{
 int i=0;
   for(i=0; i<Bsize; i++)
   {
       if(block[i].pagenum != -1)     //当物理块被分配的时候，打印分配的页号
  printf(" %02d",block[i].pagenum);
   }
   printf("\n");
}
//-------------------------------------------------------------
void suijishu( )           //产生320条随机数,显示并存储到temp[320]
{  
 int i=0;
 int flag=0;
    scanf("%d",&pc);       //输入初始位置
    printf("******按照要求产生的320个随机数：*******\n");
    for(i=0;i<320;i++)
 {    
  temp[i]=pc;  
  //分几种情况，决定是顺序产生指令还是在前地址或者后地址
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
    printf(" %02d",temp[i]/10);   //打印指令所出的页号，每十个指令在一个页
       if((i+1)%10==0)            //每十个就断行
     printf("\n");
 }
}
//-------------------------------------------------------------
void OPT( )                      //最佳置换算法
{
 int exist,space,position ;
 int curpage,k,j,i=0;
 
 for(i=0;i<320;i++)
 {    
  pc=temp[i];    //每一次都将要执行的指令赋给PC
  curpage=pc/10;    //计算所在的页号
  exist = findExist(curpage);   //通过函数查找这个页是否已经分配了物理块
    if(exist==-1)    //如果没有分配
    {
   space = findSpace ( );  //通过函数找空闲物理块
            if(space != -1)    //如果内存没有满，就把找到的物理块赋给该页，并且修改页号和缺页数
   {
    block[space].pagenum = curpage;  
                display( );
    n=n+1;
   }
            else
   { 
    //如果内存区已经满了，就按照OPT进行置换
    //在几个物理块中进行比较
    for(k=0;k<Bsize;k++)
    {
     //在未来的指令中，找到最慢被使用的物理块，也就是该页号找有无对应的指令
     for(j=i;j<320;j++)
     {
      if(block[k].pagenum!= temp[j]/10)
      { 
       //这种情况是指没有指令的页号与它相等，永远都不会用上，所以设置为很大的数
       block[k].accessed = 1000; 
      }
                        else
      {
       //这个情况就是说，在第j条指令的时候才会用上该页面，所以把accessed设置为j
       block[k].accessed = j;
       break;//找到了最近需要用到当前页号的指令之后就跳出循环
                           
      }
     }
    }
               
    position = findReplace( );    //调用findReplace函数，比较出最久时候不会用的物理块
    
    block[position].pagenum = curpage;  //修改相关参数 
                display( );
    n++;
   }
  }
 }
 //计算缺页次数和缺页率
	r=((float)(n*100))/320;
	printf("缺页次数:%d\n",n);
	printf("缺页率:%f%\n",r);
}
//-------------------------------------------------------------  
void LRU( )      //最近最久没使用算法
{
 int i,j;
 int exist,space,position ;
 int curpage;
    for(i=0;i<320;i++)
 {   
  //这里与上面一样，先计算页号以及该页号是否分配了物理块
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
                position = findReplace( );   //根据函数找到了最久没有用的页面
                block[position].pagenum = curpage;   //修改相关参数
                display( );
    n++;
   }
  }
        else 
   block[exist].accessed = -1;//如果页面存在，就将刚访问过的BLOCK中页面accessed设为-1，更新信息
        for(j=0; j<4; j++)
        {
   block[j].accessed++;   //而其他的没有被访问的页面的accessed就会+1
  }
 }
	r=((float)(n*100))/320;
	printf("缺页次数:%d\n",n);
	printf("缺页率:%f%\n",r);
}
//-------------------------------------------------------------
void FIFO( )       //先进先出算法
{
 int i,j;
 int exist,space,position ;
 int curpage;
    for(i=0;i<320;i++)
 {   
  //这些和上面两种算法相同
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
    //新调用页面的物理块的accessed就会-1 
    block[position].accessed--;
   }
  }
  for(j=0; j<Bsize; j++)
        block[j].accessed++;   //而其他物理快就会加1，这样其他先进入物理块的.accessed就会比刚进入的要大
 }
	r=((float)(n*100))/320;
	printf("缺页次数:%d\n",n);
	printf("缺页率:%f%\n",r);
}
//*************************************************************
void main( )
{ 
  int  select;
  printf("请输入第一条指令号(0~320)：");
  suijishu( );
  printf("*****对应的调用页面队列*******\n");
  pagestring( );
  do
  { 
   printf("****************************************\n");
      printf("------1:OPT   2:LRU  3:FIFO  4:退出-----\n");
      printf("****************************************\n");
      printf("          请选择一种页面置换算法:"); 
   scanf("%d",&select);
      printf("****************************************\n");
   init();
  
  switch(select)
  {
  case 1:printf("最佳置换算法OPT:\n");
             printf("*****************\n");
             OPT( );
          break;
      case 2:printf("最近最久未使用置换算法LRU:");
             printf("**************************");
             LRU( );
             break;
      case 3:printf("先进先出置换算法FIFO:");
   printf("*********************");
             FIFO( );
          break;
      defult: ;
   }
 }while(select!=4);
}	          