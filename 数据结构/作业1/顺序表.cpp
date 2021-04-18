#include<stdio.h>
#include<stdlib.h>
#define maxlength 100             
struct LIST                       //定义结构体LIST 
{
	int number[maxlength];        //数组域 
	int last;                     //最后一个元素 
}; 
typedef LIST List;
typedef int position;             //定位
void Insert(int x,position p,List* L); //插入新元素 
void Delete(position p,List* L);  //删除给定元素（功能1）
void DeleteRepeat(List* L);       //对于已排好序的线性表，删除所有重复元素（功能2）
void Reverse(List* L);            //线性表逆置算法（功能3） 
void Left(int k,List* L);         //线性表循环左移k位（功能4）
void Right(int k,List* L);        //线性表循环右移k位（功能4）
void Merge(List* L1,List* L2);    //合并两个已排好序的线性表（功能5）
void Output(List* L);             //输出打印顺序表 
void Input(List* L);              //输入创建顺序表 
void Menu();                      //功能菜单  



int main()
{
	Menu();
	return 0;
}




void Insert(int x,position p,List* L)  //插入新元素
{
	if(L->last>=maxlength-1)
	printf("list is full!");
	else if(p>L->last+1||p<1)
	printf("position does not exist");
	else if(p==L->last+1)
	{
		L->number[p]=x;
		L->last=L->last+1;
	}
	else
	{
		int q;
		for(q=L->last;q>=p;q--)
		{
			L->number[q+1]=	L->number[q];
		}
		L->number[p]=x;
		L->last=L->last+1;
	}
} 
void Delete(position p,List* L)   //删除给定元素（功能1）
{
	position q;
	if(p>L->last||p<1)
    printf("position does not exist!");
    else
    {
    	L->last=L->last-1;
    	for(q=p;q<=L->last;q++)
    	{
    		L->number[q]=L->number[q+1];
		}
	}
}

void DeleteRepeat(List* L)        //对于已排好序的线性表，删除所有重复元素（功能2）
{
	position i;
	for(i=1;i<L->last;i++)
	{
		if(L->number[i]==L->number[i+1])
		{
			Delete(i+1,L);
			i--;
		}
	}
} 

void Reverse(List* L)             //线性表逆置算法（功能3）
{
	position q;
	for(q=1;q<=L->last/2;q++)
	{
		int temp;
		temp=L->number[q];
		L->number[q]=L->number[L->last+1-q];
		L->number[L->last+1-q]=temp;
	}
}

void Left(int k,List* L)          //线性表循环左移k位（功能4）
{
	position i;
	for(i=1;i<=k/2;i++)
	{
		int temp;
		temp=L->number[i];
		L->number[i]=L->number[k+1-i];
		L->number[k+1-i]=temp;
	}
	for(i=k+1;i<=(L->last+k+1)/2;i++)
	{
		int temp;
		temp=L->number[i];
		L->number[i]=L->number[L->last+k+1-i];
		L->number[L->last+k+1-i]=temp;
	}
	Reverse(L);
}

void Right(int k,List* L)          //线性表循环右移k位（功能4）
{
	Left(L->last-k,L);
} 

void Merge(List* L1,List* L2)       //合并两个已排好序的线性表（功能5）(将L2合并到L1） 
{
	position p,q;
	if(L1->last+L2->last>=maxlength-1)
	{
		printf("space is not enough");
	}else
	{
		p=1;
		for(q=1;q<=L2->last;q++)
		{
			while((L2->number[q]>L1->number[p])&&(p<=L1->last))
			{
				p++;
			}
			Insert(L2->number[q],p,L1);
		}
	}
}

void Output(List* L)              //输出打印顺序表 
{
	int i;
	for(i=1;i<=L->last;i++)
	{
		printf("%d   ",L->number[i]);
	}
	printf("\n");
} 

void Input(List* L)               //输入创建顺序表 
{
	int length;
	printf("你要创建的顺序表长度为:\n");
	scanf("%d",&length);
	L->last=length;
	for(int i=1;i<=L->last;i++)
	{
		printf("请输入第%d个元素",i);
		scanf("%d",&L->number[i]);
	}
} 

void Menu()                       //功能菜单
{
	List L;
	List L1,L2;
	int flag;
	printf("1.删除给定元素\n");
	printf("2.对于已排好序的线性表，删除所有重复元素\n");
	printf("3.线性表逆置算法\n");
	printf("4.线性表循环左移k位\n");
	printf("5.线性表循环右移k位\n");
	printf("6.合并两个已排好序的线性表\n");
	printf("选择功能"); 
	scanf("%d",&flag);
	switch(flag)
	{
		case 1:
			position p; 
			Input(&L);
			printf("初始顺序表:\n");
			Output(&L);
			printf("选择要删除的元素序号:");
			scanf("%d",&p);
			Delete(p,&L);
			printf("操作后顺序表:\n");
			Output(&L);
			break;
		case 2:	
			Input(&L);
			printf("初始顺序表:\n");
			Output(&L);
			DeleteRepeat(&L);
			printf("操作后顺序表:\n");
			Output(&L);
		    break;
		case 3:
			Input(&L);
			printf("初始顺序表:\n");
			Output(&L);
			Reverse(&L);
			printf("操作后顺序表:\n");
			Output(&L);
		    break;
		case 4:
		   	int k;
			Input(&L);
			printf("初始顺序表:\n");
			Output(&L);
			printf("选择要左循环的位数:");
			scanf("%d",&k);
			Left(k,&L);
			printf("操作后顺序表:\n");
			Output(&L);
		    break;	
		case 5:
		   	int j;
			Input(&L);
			printf("初始顺序表:\n");
			Output(&L);
			printf("选择要右循环的位数:");
			scanf("%d",&j);
			Right(j,&L);
			printf("操作后顺序表:\n");
			Output(&L);
		    break;
		case 6:
			Input(&L1);
			Input(&L2);
			printf("初始顺序表:\n");
			Output(&L1);	
			Output(&L2);
			Merge(&L1,&L2);
			printf("操作后顺序表:\n");
			Output(&L1);
			break;
		default:
		    exit(0);			
	}
	
} 
























































