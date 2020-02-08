#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <windows.h>
#include <cmath>
using namespace std;
#define N 50//列
#define M 8//行

int map[N][M];

typedef struct LinkList
{
	int x,y;
	struct LinkList *next;
}LL;

LL *head,*L1,*L2;
int kx,ky;
char key='d',last;

bool check(int x,int y)
{
	y%=N;
	if (x<1||x>=M-1||y<1||y>=N-1)
	{
		system("cls");
		printf("\n\n\n                   GAME OVER\n\n\n");
		Sleep(3000);
		exit(0);
		return false;
	}
	LL *p=head->next;
	while (p->next!=NULL)
	{
		p=p->next;
		if (p->x==x&&p->y==y)
		{
			system("cls");
			printf("\n\n\n                   GAME OVER\n\n\n");
			Sleep(3000);
			exit(0);
			return false;
		}
	}
	return true;
}

void create()
{
	bool flag;
	do
	{
		flag=true;
		kx=rand()%(M-2)+1;
		ky=rand()%(N-2)+1;
		LL *p=head->next;
		while (flag&&p!=NULL)
		{
			if (p->x==kx&&p->y==ky) flag=false;
			p=p->next;
		}
		if (flag) break;
	}while(1);
	//printf("%d %d\n",kx,ky);
}

bool eat(int x,int y)
{
	y%=N;
	if (x!=kx||y!=ky) return false;
	LL *q;
	q=(LL*)malloc(sizeof(LL));
	q->next=head->next;
	head->next=q;
	q->x=x;
	q->y=y;
	create();
	return true;
}

void up()
{
	if (!check(head->next->x-1,head->next->y)) return;
	if (eat(head->next->x-1,head->next->y)) return;
	LL *p=head,*q;
	while (p->next->next!=NULL) p=p->next;
	q=p->next;
	q->next=head->next;
	head->next=q;
	p->next=NULL;
	q->x=q->next->x-1;
	q->y=q->next->y;
	return;
}

void down()
{
	if (!check(head->next->x+1,head->next->y)) return;
	if (eat(head->next->x+1,head->next->y)) return;
	LL *p=head,*q;
	while (p->next->next!=NULL) p=p->next;
	q=p->next;
	q->next=head->next;
	head->next=q;
	p->next=NULL;
	q->x=q->next->x+1;
	q->y=q->next->y;
	return;
}

void left()
{
	if (!check(head->next->x,head->next->y-1)) return;
	if (eat(head->next->x,head->next->y-1)) return;
	LL *p=head,*q;
	while (p->next->next!=NULL) p=p->next;
	q=p->next;
	q->next=head->next;
	head->next=q;
	p->next=NULL;
	q->x=q->next->x;
	q->y=(q->next->y-1+N)%N;
	return;
}

void right()
{
	if (!check(head->next->x,head->next->y+1)) return;
	if (eat(head->next->x,head->next->y+1)) return;
	LL *p=head,*q;
	while (p->next->next!=NULL) p=p->next;
	q=p->next;
	q->next=head->next;
	head->next=q;
	p->next=NULL;
	q->x=q->next->x;
	q->y=(q->next->y+1+N)%N;
	return;
}

void draw()
{
	memset(map,0,sizeof(map));
	for (int i=0;i<N;i++) map[i][0]=map[i][M-1]=2;
	for (int i=0;i<M;i++) map[0][i]=map[N-1][i]=2;
	for (LL *p=head->next;p!=NULL;p=p->next) map[p->y][p->x]=1;
	map[ky][kx]=3;
}

int tr(int f[M])
{
	int num=0;
	for (int i=0;i<M;i++) num+=f[i]*(1<<(7-i));
	return num;
}

void print()
{
	char pr;
	for (int i=0;i<M;i++)
	{
		for (int j=0;j<N;j++)
		{
			switch (map[j][i])
			{
				case 0:pr='.';break;
				case 1:pr='@';break;
				case 2:pr='#';break;
				case 3:pr='%';break;
			}
			map[j][i]=min(map[j][i],1);
			printf("%c",pr);
		}
		printf("\n");
	}
	/*cout<<endl<<endl;
	for (int i=0;i<N;i++)
	{
		cout<<'0'<<'x';
		printf("%-4x",tr(map[i]));
	}*/
}

void gotoxy(int x, int y) //定位到第y行的第x列
{
    HANDLE hOutput;
    COORD loc;
    loc.X = x;
    loc.Y=y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, loc);
    return;
}

int main()
{
	head=(LL*)malloc(sizeof(LL));
	L1=(LL*)malloc(sizeof(LL));
	L2=(LL*)malloc(sizeof(LL));
	head->next=L1;
	L1->next=L2;
	L2->next=NULL;
	L1->x=1;L1->y=1;
	L2->x=1;L2->y=0;
	
	create();
	draw();
	print();
	while (1)
	{
		if (kbhit())
		{
			last=key;
			key=getch();
		}
		switch (key)
		{
			case 'w':
				up();
				break;
			case 's':
				down();
				break;
			case 'a':
				left();
				break;
			case 'd':
				right();
				break;
		}
		draw();
		gotoxy(0,0);
		print();
		Sleep(0);
	}
	
	return 0;
}
