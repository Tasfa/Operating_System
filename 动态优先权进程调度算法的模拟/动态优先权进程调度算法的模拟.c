#include <stdio.h>
#define N 5
void init();
void print();
int getRunning();
void sort();
int run(int time);
enum STATE{Ready,Run,Block,RunOut};
struct PROCESS{
	int ID;
	int Priority;
	int Cputime;
	int Alltime;
	int Startblock;
	int Blocktime;
	enum STATE State;
}Process[N];
int READY[N];
int BLOCK[N];
int RUNOUT[N][2];
int main(){
	int Time=0;
	init();
	printf("Time:%d\n",Time);
	sort();
	print();
	while(1){		
		Time++;
		getchar();	
		printf("Time:%d\n",Time);
		if(run(Time))
			break;
	//	sort();			
	}
	//print(Time);
	return 0;
}
void init()
{
	int i;	
	//printf("Input properties of %d process(PRIORITY,ALLTIME,STARTBLOCK,BLOCKTIME):\n",
	//		N);
	for(i=0;i<N;++i){
		READY[i]=-1;
		BLOCK[i]=-1;
		RUNOUT[i][0]=-1;
		RUNOUT[i][1]=-1;
		Process[i].ID=i;
		Process[i].Cputime=0;
		Process[i].State=Ready;		
		Process[i].Startblock=-1;Process[i].Blocktime=0;
	}
	Process[0].Priority=9;Process[0].Alltime=3;Process[0].Startblock=2;Process[0].Blocktime=3;
	Process[1].Priority=38;Process[1].Alltime=3;
	Process[2].Priority=30;Process[2].Alltime=6;
	Process[3].Priority=29;Process[3].Alltime=3;
	Process[4].Priority=0;Process[4].Alltime=4;
}
void print()
{
	int i;
	if(getRunning()>=0)
		printf("\tRUNNING PROG: %d\n",getRunning());
	printf("\tREADY_QUEUE:");
	for(i=0;i<N;++i){
		if(READY[i]>=0)
			printf("->%d",Process[READY[i]].ID);
		else{
			break;
		} 
	}
	printf("\n\tBLOCK_QUEUE:");
	for(i=0;i<N;++i){
		if(BLOCK[i]>=0)
			printf("->%d",Process[BLOCK[i]].ID);
		else{
			break;
		}
	}
	printf("\n=====================================================\n");
	printf("ID\t");
	for(i=0;i<N;++i){
		printf("\t%d",Process[i].ID);
	}
	printf("\nPRIORITY");
	for(i=0;i<N;++i){
		printf("\t%d",Process[i].Priority);
	}
	printf("\nCPUTIME\t");
	for(i=0;i<N;++i){
		printf("\t%d",Process[i].Cputime);
	}
	printf("\nALLTIME\t");
	for(i=0;i<N;++i){
		printf("\t%d",Process[i].Alltime);
	}
	printf("\nSTARTBLOCK");
	for(i=0;i<N;++i){
		printf("\t%d",Process[i].Startblock);
	}
	printf("\nBLOCKTIME");
	for(i=0;i<N;++i){
		printf("\t%d",Process[i].Blocktime);
	}
	printf("\nSTATE\t");
	for(i=0;i<N;++i){
		switch(Process[i].State){
		case 0:printf("\tReady");break;
		case 1:printf("\tRun"); 
			if(Process[i].Alltime==0)
			{
				Process[i].State=RunOut;
			}
			else Process[i].State=Ready; 
			break;
		case 2:printf("\tBlock");break;
		case 3:printf("\tRunOut");break;
		}
	}
	printf("\n");
	printf("\tRUNOUT LIST:");
	for(i=0;i<N;++i){
		if(RUNOUT[i][0]>=0)
			printf("->%d(%d)",Process[RUNOUT[i][0]].ID,RUNOUT[i][1]);
		else{
			printf("\n");
			break;
		} 
	}
	printf("\n");
}
int getRunning()
{
	int i;
	for(i=0;i<N;++i){
		if(Process[i].State==Run)
			return i;
	}
	for(i=0;i<N;++i){
		if(Process[i].Startblock==0)
			return i;
	}
	return -1;
}
void sort()
{
	int i,j,k;
	for(i=0;i<N;++i){
		READY[i]=-1;
		BLOCK[i]=-1;
	}
	for(i=0;i<N;++i){
		if(Process[i].State==Ready||Process[i].State==Run){
		//	Process[i].State=Ready;
			if(Process[i].Alltime==0)
				continue;
			for(j=0;j<N;++j){
				if(READY[j]<0)
				{
					READY[j]=i;
					break;
				}
				else if(Process[i].Priority<=Process[READY[j]].Priority)
				{ continue; }
				else{
					for(k=N-1;k>j;--k){
						READY[k]=READY[k-1];
					}
					READY[j]=i;
					break;
				}
			}
		}
		else if(Process[i].State==Block){
			for(j=0;j<N;++j){
				if(BLOCK[j]<0)
				{
					BLOCK[j]=i;
					break;
				}
				else if(Process[i].Blocktime>=Process[BLOCK[j]].Blocktime)
				{ continue; }
				else{
					for(k=N-1;k>j;--k){
						BLOCK[k]=BLOCK[k-1];
					}
					BLOCK[j]=i;
					break;
				}
			}
		}
	}
}
int run(int time)
{
	int i,runNum;
	runNum=READY[0];
	if(runNum<0&&BLOCK[0]<0){
		printf("Every process is OVER!\n");
		return 1;
	}
	else{
		if(runNum>=0){
			Process[runNum].Priority-=3;
			Process[runNum].Alltime-=1;
			Process[runNum].Cputime+=1;
			Process[runNum].State=Run;
			for(i=0;i<N;++i){
				if(i!=runNum){
					if(Process[i].State==Ready){
						Process[i].Priority+=1;
					}
					else if(Process[i].State==Block){
						Process[i].Blocktime-=1;
						if(Process[i].Blocktime==0){
							Process[i].State=Ready;
						}
					}
				}
			}
			//print();
			if(Process[runNum].Alltime==0)
			{
				//Process[runNum].State=RunOut;
				for(i=0;i<N;++i){
					if(RUNOUT[i][0]<0){
						RUNOUT[i][0]=runNum;
						RUNOUT[i][1]=time;
						break;
					}
				}
			}
			else if(Process[runNum].Startblock>=0){
				Process[runNum].Startblock-=1;
				if(Process[runNum].Startblock==0){
					Process[runNum].State=Block;
					//Process[runNum].Startblock-=1;
				}
			}
		}
	 else if(BLOCK[0]>=0){
			for(i=0;i<N;++i){
				if(Process[i].State==Block){
					Process[i].Startblock=-1;
					Process[i].Blocktime-=1;
					if(Process[i].Blocktime==0){
						Process[i].State=Ready;
					}
				}
			}
		//	print();
		}
	}
	sort();
	print();
	return 0;
}