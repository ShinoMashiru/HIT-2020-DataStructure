#include<stdio.h>
#include<stdlib.h>
#define maxlength 100             
struct LIST                       //����ṹ��LIST 
{
	int number[maxlength];        //������ 
	int last;                     //���һ��Ԫ�� 
}; 
typedef LIST List;
typedef int position;             //��λ
void Insert(int x,position p,List* L); //������Ԫ�� 
void Delete(position p,List* L);  //ɾ������Ԫ�أ�����1��
void DeleteRepeat(List* L);       //�������ź�������Ա�ɾ�������ظ�Ԫ�أ�����2��
void Reverse(List* L);            //���Ա������㷨������3�� 
void Left(int k,List* L);         //���Ա�ѭ������kλ������4��
void Right(int k,List* L);        //���Ա�ѭ������kλ������4��
void Merge(List* L1,List* L2);    //�ϲ��������ź�������Ա�����5��
void Output(List* L);             //�����ӡ˳��� 
void Input(List* L);              //���봴��˳��� 
void Menu();                      //���ܲ˵�  



int main()
{
	Menu();
	return 0;
}




void Insert(int x,position p,List* L)  //������Ԫ��
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
void Delete(position p,List* L)   //ɾ������Ԫ�أ�����1��
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

void DeleteRepeat(List* L)        //�������ź�������Ա�ɾ�������ظ�Ԫ�أ�����2��
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

void Reverse(List* L)             //���Ա������㷨������3��
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

void Left(int k,List* L)          //���Ա�ѭ������kλ������4��
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

void Right(int k,List* L)          //���Ա�ѭ������kλ������4��
{
	Left(L->last-k,L);
} 

void Merge(List* L1,List* L2)       //�ϲ��������ź�������Ա�����5��(��L2�ϲ���L1�� 
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

void Output(List* L)              //�����ӡ˳��� 
{
	int i;
	for(i=1;i<=L->last;i++)
	{
		printf("%d   ",L->number[i]);
	}
	printf("\n");
} 

void Input(List* L)               //���봴��˳��� 
{
	int length;
	printf("��Ҫ������˳�����Ϊ:\n");
	scanf("%d",&length);
	L->last=length;
	for(int i=1;i<=L->last;i++)
	{
		printf("�������%d��Ԫ��",i);
		scanf("%d",&L->number[i]);
	}
} 

void Menu()                       //���ܲ˵�
{
	List L;
	List L1,L2;
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
			position p; 
			Input(&L);
			printf("��ʼ˳���:\n");
			Output(&L);
			printf("ѡ��Ҫɾ����Ԫ�����:");
			scanf("%d",&p);
			Delete(p,&L);
			printf("������˳���:\n");
			Output(&L);
			break;
		case 2:	
			Input(&L);
			printf("��ʼ˳���:\n");
			Output(&L);
			DeleteRepeat(&L);
			printf("������˳���:\n");
			Output(&L);
		    break;
		case 3:
			Input(&L);
			printf("��ʼ˳���:\n");
			Output(&L);
			Reverse(&L);
			printf("������˳���:\n");
			Output(&L);
		    break;
		case 4:
		   	int k;
			Input(&L);
			printf("��ʼ˳���:\n");
			Output(&L);
			printf("ѡ��Ҫ��ѭ����λ��:");
			scanf("%d",&k);
			Left(k,&L);
			printf("������˳���:\n");
			Output(&L);
		    break;	
		case 5:
		   	int j;
			Input(&L);
			printf("��ʼ˳���:\n");
			Output(&L);
			printf("ѡ��Ҫ��ѭ����λ��:");
			scanf("%d",&j);
			Right(j,&L);
			printf("������˳���:\n");
			Output(&L);
		    break;
		case 6:
			Input(&L1);
			Input(&L2);
			printf("��ʼ˳���:\n");
			Output(&L1);	
			Output(&L2);
			Merge(&L1,&L2);
			printf("������˳���:\n");
			Output(&L1);
			break;
		default:
		    exit(0);			
	}
	
} 
























































