#include<stdio.h>
#include<stdlib.h>
struct LIST                      //定义链表结构体 
{
	int x;
	struct LIST* next;
};
typedef struct LIST List;       
typedef struct LIST position;    //位置
List* Add(List* L);              //添加新节点
position* Locate(int x,List* L); //定位节点（找到链表第x个节点，返回节点地址）
List* Delete(position* p,List* L);       //删除给定节点（功能1）
List* DeleteRepeat(List* L);     //对于已排好序的线性表，删除所有重复元素（功能2）
List* Reverse(List* L);          //线性表逆置算法（功能3）
List* Left(int k,List* L);       //线性表循环左移k位（功能4）
List* Right(int k,List* L);      //线性表循环右移k位（功能4）
List* Merge(List* L1,List* L2);  //合并两个已排好序的线性表（功能5）
List* Output(List* L);             //输出打印链表 
List* Input(List* L);              //输入创建链表 
void Menu();                      //功能菜单
int main()
{
	Menu();
	return 0;
} 
List* Add(List* L)               //添加新节点
{
	position* p=NULL;
	position* pr=L;
	int data;
	p=(List*)malloc(sizeof(List));
	if(p==NULL)
	{
		printf("space is not enough!");
		exit(0);
	}
	if(L==NULL)
	{
		L=p;
		scanf("%d",&data);
		L->x=data;
		L->next=NULL;
		return L;
	}else
	{
		while(pr->next!=NULL)
		{
			pr=pr->next;
		}
		pr->next=p;
		scanf("%d",&data);
		p->x=data;
		p->next=NULL;
		return L;
	}
}

position* Locate(int x,List* L)  //定位节点（找到链表第x个节点，返回节点地址）
{
	position* p;
	int count;
	p=L;
    for(count=1;count<x;count++)
    {
    	p=p->next;
	}
    return p;
}

List* Delete(position* p,List* L)  //删除给定节点（功能1）
{
	position* q=L;
	if(p==L)
	{
		L=L->next;
		return L;
	}else
	{
		while(q->next!=p)
	    {
		   q=q->next;
	    }
	    q->next=p->next;
	    free(p);
	    return L;
	}
}

List* DeleteRepeat(List* L)      //对于已排好序的线性表，删除所有重复元素（功能2）
{
	position* p;
	position* q;
	p=L;
	q=p->next;
	while(p->next!=NULL)
	{
		while((p->x==q->x)&&(q->next!=NULL))
		{
			q=q->next;
		}
		if(p->x==q->x)
		{
			p->next=NULL;
		}else
		{
			p->next=q;
	        p=p->next;
			q=q->next;
		}
	}
	return L;
}

List* Reverse(List* L)           //线性表逆置算法（功能3）
{
	position* p;
	position* q;
	p=NULL;
	while(L->next!=NULL)
	{
		q=L;
		L=q->next;
		q->next=p;
		p=q;
	}
	L->next=p;
	return L;
}

List* Left(int k,List* L)       //线性表循环左移k位（功能4）
{
	int i;
	position* p;
	position* q;
	p=L;
	for(int i=1;i<k;i++)
	{
		p=p->next;
		q=p->next;
		
	}
		p->next=NULL;
		p=q;
		while(q->next!=NULL)
		{
			q=q->next;
		}
        q->next=L;
		L=p;
		return L;
}

List* Right(int k,List* L)        //线性表循环右移k位（功能4）
{
	int count;
	count =1;
	position* p =L;
	while(p->next!=NULL)
	{
		p=p->next;
		count++;
	}
	L=Left(count-k,L);
	return L;
}

List* Merge(List* L1,List* L2)   //合并两个已排好序的线性表（功能5）
{
	position *p;
	position *q;
	position *pr;
	position *qr;
	p=L1;
	q=L2;
	if(L1->x>L2->x)
	{
		q=q->next;
		L2->next=p;
		L1=L2;
		L2=NULL;
		p=L1;
	}
	while(q->next!=NULL)
	{
		while(1)
		{
			if(p->next==NULL||p->next->x>q->x)
			{
				break;
			}
			p=p->next;
		}
		if(p->next!=NULL)
		{
			qr=q;
			q=q->next;
			qr->next=p->next;
			p->next=qr;
			p=qr;
		}else if(p->next==NULL)
		{
		    qr=q;
		    q=q->next;
		    p->next=qr;
		    qr->next=NULL;
		}
	}
	if(p->next!=NULL)
	{
		while(1)
		{
			if(p->next==NULL||p->next->x>q->x)
			{
				break;
			}
			p=p->next;
		}
		if(p->next!=NULL)
		{
			q->next=p->next;
			p->next=q;
		}else if(p->next==NULL)
		{
			p->next=q;
			q->next=NULL;
		}
	}else if(p->next==NULL)
	{
		p->next=q;
		q->next=NULL;
	}
	
	return L1;
}

List* Output(List* L)              //输出打印链表 
{
	position* p=L;
	while(p->next!=NULL)
	{
		printf("%d   ",p->x);
		p=p->next;
	}
	printf("%d   ",p->x);
	printf("\n");
	return L;
} 

List* Input(List* L)               //输入创建链表 
{
	int length;
	printf("你要创建的链表长度为:\n");
	scanf("%d",&length);
	for(int i=1;i<=length;i++)
	{
		printf("请输入第%d个元素:",i);
		L=Add(L);
	}
	return L;
} 

void Menu()                       //功能菜单
{
	List* L;
	List* L1;
	List* L2;
	L=NULL;
	L1=NULL;
	L2=NULL;
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
			position* m; 
			int k;
			L=Input(L);
			printf("初始顺序表:\n");
			Output(L);
			printf("选择要删除的元素序号:");
			scanf("%d",&k);
			m=Locate(k,L);
			L=Delete(m,L);
			printf("操作后顺序表:\n");
			Output(L);
			break;
		case 2:
			L=Input(L);
			printf("初始顺序表:\n");
			L=Output(L);
			L=DeleteRepeat(L);
			printf("操作后顺序表:\n");
			Output(L);
		    break;
		case 3:
			L=Input(L);
			printf("初始顺序表:\n");
			Output(L);
			L=Reverse(L);
			printf("操作后顺序表:\n");
			Output(L);
		    break;
		case 4:
		   	int i;
			L=Input(L);
			printf("初始顺序表:\n");
			Output(L);
			printf("选择要左循环的位数:");
			scanf("%d",&i);
			L=Left(i,L);
			printf("操作后顺序表:\n");
			Output(L);
		    break;	
		case 5:
		   	int j;
			L=Input(L);
			printf("初始顺序表:\n");
			Output(L);
			printf("选择要右循环的位数:");
			scanf("%d",&j);
			L=Right(j,L);
			printf("操作后顺序表:\n");
			Output(L);
		    break;
		case 6:
			L1=Input(L1);
			L2=Input(L2);
			printf("初始顺序表:\n");
			Output(L1);	
			Output(L2);
			L1=Merge(L1,L2);
			printf("操作后顺序表:\n");
			Output(L1);
			break;
		default:
		    exit(0);			
	}
	
} 






















































