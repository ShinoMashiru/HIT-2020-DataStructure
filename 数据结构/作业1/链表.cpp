#include<stdio.h>
#include<stdlib.h>
struct LIST                      //��������ṹ�� 
{
	int x;
	struct LIST* next;
};
typedef struct LIST List;       
typedef struct LIST position;    //λ��
List* Add(List* L);              //����½ڵ�
position* Locate(int x,List* L); //��λ�ڵ㣨�ҵ������x���ڵ㣬���ؽڵ��ַ��
List* Delete(position* p,List* L);       //ɾ�������ڵ㣨����1��
List* DeleteRepeat(List* L);     //�������ź�������Ա�ɾ�������ظ�Ԫ�أ�����2��
List* Reverse(List* L);          //���Ա������㷨������3��
List* Left(int k,List* L);       //���Ա�ѭ������kλ������4��
List* Right(int k,List* L);      //���Ա�ѭ������kλ������4��
List* Merge(List* L1,List* L2);  //�ϲ��������ź�������Ա�����5��
List* Output(List* L);             //�����ӡ���� 
List* Input(List* L);              //���봴������ 
void Menu();                      //���ܲ˵�
int main()
{
	Menu();
	return 0;
} 
List* Add(List* L)               //����½ڵ�
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

position* Locate(int x,List* L)  //��λ�ڵ㣨�ҵ������x���ڵ㣬���ؽڵ��ַ��
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

List* Delete(position* p,List* L)  //ɾ�������ڵ㣨����1��
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

List* DeleteRepeat(List* L)      //�������ź�������Ա�ɾ�������ظ�Ԫ�أ�����2��
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

List* Reverse(List* L)           //���Ա������㷨������3��
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

List* Left(int k,List* L)       //���Ա�ѭ������kλ������4��
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

List* Right(int k,List* L)        //���Ա�ѭ������kλ������4��
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

List* Merge(List* L1,List* L2)   //�ϲ��������ź�������Ա�����5��
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

List* Output(List* L)              //�����ӡ���� 
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

List* Input(List* L)               //���봴������ 
{
	int length;
	printf("��Ҫ������������Ϊ:\n");
	scanf("%d",&length);
	for(int i=1;i<=length;i++)
	{
		printf("�������%d��Ԫ��:",i);
		L=Add(L);
	}
	return L;
} 

void Menu()                       //���ܲ˵�
{
	List* L;
	List* L1;
	List* L2;
	L=NULL;
	L1=NULL;
	L2=NULL;
	int flag;
	printf("1.ɾ������Ԫ��\n");
	printf("2.�������ź�������Ա�ɾ�������ظ�Ԫ��\n");
	printf("3.���Ա������㷨\n");
	printf("4.���Ա�ѭ������kλ\n");
	printf("5.���Ա�ѭ������kλ\n");
	printf("6.�ϲ��������ź�������Ա�\n");
	printf("ѡ����"); 
	scanf("%d",&flag);
	switch(flag)
	{
		case 1:
			position* m; 
			int k;
			L=Input(L);
			printf("��ʼ˳���:\n");
			Output(L);
			printf("ѡ��Ҫɾ����Ԫ�����:");
			scanf("%d",&k);
			m=Locate(k,L);
			L=Delete(m,L);
			printf("������˳���:\n");
			Output(L);
			break;
		case 2:
			L=Input(L);
			printf("��ʼ˳���:\n");
			L=Output(L);
			L=DeleteRepeat(L);
			printf("������˳���:\n");
			Output(L);
		    break;
		case 3:
			L=Input(L);
			printf("��ʼ˳���:\n");
			Output(L);
			L=Reverse(L);
			printf("������˳���:\n");
			Output(L);
		    break;
		case 4:
		   	int i;
			L=Input(L);
			printf("��ʼ˳���:\n");
			Output(L);
			printf("ѡ��Ҫ��ѭ����λ��:");
			scanf("%d",&i);
			L=Left(i,L);
			printf("������˳���:\n");
			Output(L);
		    break;	
		case 5:
		   	int j;
			L=Input(L);
			printf("��ʼ˳���:\n");
			Output(L);
			printf("ѡ��Ҫ��ѭ����λ��:");
			scanf("%d",&j);
			L=Right(j,L);
			printf("������˳���:\n");
			Output(L);
		    break;
		case 6:
			L1=Input(L1);
			L2=Input(L2);
			printf("��ʼ˳���:\n");
			Output(L1);	
			Output(L2);
			L1=Merge(L1,L2);
			printf("������˳���:\n");
			Output(L1);
			break;
		default:
		    exit(0);			
	}
	
} 






















































