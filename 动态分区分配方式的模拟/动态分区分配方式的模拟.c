#include"stdio.h"
#include"stdlib.h"

typedef struct mem
{
	int start;
	int end;
	struct mem *next;
}mem;
typedef struct work
{
	int id;
	int size;//memsize
	int start;
	struct work *next;
}work;
work* initwork(int id, int size)
{
	work *head = (work *)malloc(sizeof(head)+15*sizeof(int));
	head->id = id;
	head->start = 1;
	head->size = size;
	head->next = NULL;
	return head;

}
work* insertwork(int id, work *head, int start, int size)
{
	work *pi, *pb;//pi is the insert one ##pb is the point
	pi = (work*)malloc(sizeof(work));
	pi->id = id;
	pi->start = start;
	pi->size = size;
	pi->next = NULL;
	if (head == NULL){ head = pi; head->next = NULL; }
	pb = head;
	while (pb->next != NULL){ pb = pb->next; }
	pb->next = pi;
	return head;
}
mem *initmem(int size)
{
	mem *head = (mem*)malloc(sizeof(mem));
	head->start = 1;
	head->end = 640;
	head->next = NULL;
	return head;
}
mem *insertmem(mem *head, int start, int size)
{
	mem *pi, *pb, *pf;
	int pbsize;
	pb = head;
	pbsize = pb->end - pb->start + 1;
	pi = (mem*)malloc(sizeof(mem));
	pi->start = start;
	pi->end = size + start - 1;
	if (pb == NULL){ head = pi; pi->next = NULL; }
	else
	{
		while (pi->start > pb->start&&pb->next != NULL){ pf = pb; pb = pb->next; }
		if (pi->start < pb->start)
		{
			if (pb == head)
			{

				head = pi;//头节点
				pi->next = pb;
			}

			else
			{
				pf->next = pi;//其他位置
				pi->next = pb;

			}

		}
		else
		{
			pb->next = pi;
			pi->next = NULL;//在表末插入
		}
	}
	//合并相邻的内存
	pf = pb = head;
	while (pb->next != NULL)
	{
		if (pf->end + 2>pb->start)
		{
			pf->end = pb->end;
			pf->next = pb->next;
		}
		pf = pb;
		pb = pb->next;
	}
	return head;
}
int getstart(int id, work*head)
{
	work *pb;
	pb = head;
	while (pb != NULL)
	{
		if (pb->id == id)
		{
			return pb->start;
		}

		pb = pb->next;
	}

	return 0;
}
int alloc(mem *head, int size)
{
	mem *pb,*pi;
	pb = head;
	int a;
	int zhong=0;
	while (pb != NULL)
	{
		if (zhong == 1 && size <= (pb->end - pb->start + 1))
		{
			if (pb->end - pb->start + 1 < pi->end - pi->start + 1)
			{
				pi = pb;
			}
		}
		if (zhong==0 && size <= (pb->end - pb->start + 1) )
		{
			pi = pb;
			zhong = 1;
		}
		pb = pb->next;
	}
	 a = pi->start;
	 pi->start = pi->start + size;
	return a;
}
work*free1(int id, work *head)
{
	work *pb, *pf;
	while (head == NULL){ printf("no this nod"); goto end; }
	pb = head;
	while (pb->id != id&&pb->next != NULL)
	{

		pf = pb;
		pb = pb->next;
	}
	if (pb->id == id)
	{
		if (pb == head)head = pb->next;
		else pf->next = pb->next;

	}

end:
	return head;
}
void printw(work *head)
{
	work *pb;
	pb = head;
	while (pb != NULL)
	{
		printf("id    start    size---->\n");
		printf("%d%7d%8d\n", pb->id, pb->start, pb->size);
		pb = pb->next;
	}
}
void printm(mem *head)
{
	mem *pb;
	pb = head;
	while (pb != NULL)
	{
		printf("start    end---->\n");
		printf("%d%9d\n", pb->start, pb->end);
		pb = pb->next;
	}
}

void final_printf(mem *mhead, work *whead)
{
	printf("JOB LISTS\n");
	printw(whead);
	printf("========================\n");
	printf("FREE \n");
	printm(mhead);
	printf("\n");
}

int main()
{
	int wrec;//接收返回的地址
	int mrec;
	mem *mhead;
	mhead = initmem(640);
	work *whead;

	//1 
	whead = initwork(1, 130);
	wrec = alloc(mhead, 130);
	final_printf(mhead, whead);

	//2 
	wrec = alloc(mhead, 60);
	whead = insertwork(2, whead, wrec, 60);
	final_printf(mhead, whead);

	//3
	wrec = alloc(mhead, 100);
	whead = insertwork(3, whead, wrec, 100);
	final_printf(mhead, whead);

	//4
	mrec = getstart(2, whead);
	whead = free1(2, whead);
	mhead = insertmem(mhead, mrec, 60);
	final_printf(mhead, whead);

	//5
	wrec = alloc(mhead, 200);
	whead = insertwork(4, whead, wrec, 200);
	final_printf(mhead, whead);

	//6 
	mrec = getstart(3, whead);
	whead = free1(3, whead);
	mhead = insertmem(mhead, mrec, 100);
	final_printf(mhead, whead);

	//7
	mrec = getstart(1, whead);
	whead = free1(1, whead);
	mhead = insertmem(mhead, mrec, 130);
	final_printf(mhead, whead);

	//8
	wrec = alloc(mhead, 140);
	whead = insertwork(5, whead, wrec, 140);
	final_printf(mhead, whead);

	//9
	wrec = alloc(mhead, 60);
	whead = insertwork(6, whead, wrec, 60);
	final_printf(mhead, whead);

	//10
	wrec = alloc(mhead, 50);
	whead = insertwork(7, whead, wrec, 50);
	final_printf(mhead, whead);

	//11
	mrec = getstart(6, whead);
	whead = free1(6, whead);
	mhead = insertmem(mhead, mrec, 60);
	final_printf(mhead, whead);
	return 0;
}