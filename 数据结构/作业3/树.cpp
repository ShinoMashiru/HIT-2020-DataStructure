#include<stdio.h>
#include<stdlib.h>
#define maxlength 100
typedef struct Tree									  //���Ľڵ� 
{
    int data;
    Tree  *Lchild;
    Tree  *Rchild;
}Tree; 
typedef struct QueueNode							  //���еĽڵ� 
{
	Tree* data;
	QueueNode *next;
}QueueNode;
typedef struct Queue                                  //���е�ͷβָ�빹�ɵĽṹ�� 
{
	QueueNode* front;
	QueueNode* rear;
}Queue;
Tree* Creat()                                         //�����������(�Ƚ����������䣬��ڵ��Ϊ-1�������������������У� 
{
	int k;
    Tree  *T;
    printf("��������ڵ�:");
    scanf("%d",&k);
    if(k==-1)                                         //����Ϊ-1��ʾָ���ָ�� 
	{
		T=NULL;
	}else
    {
        T=(Tree*)malloc(sizeof(Tree));
        T->data=k;
        printf("\n������%d�������ӽ��(���û����ô����-1�����):",T->data );
        T->Lchild=Creat();
        printf("\n������%d�������ӽ��(���û����ô����-1�����):",T->data );
        T->Rchild=Creat();
    }
    return T;
}
void PreOrder(Tree* T)                                //����ݹ���������� 
{
	if(T!=NULL)
	{
		printf("%d ",T->data);
		PreOrder(T->Lchild);
		PreOrder(T->Rchild);
	}
}
void nPreOrder(Tree* T)								  //����ǵݹ���������� 
{
	Tree* STACK[maxlength];                           //��ջ����������ʵĽڵ� 
    int top=0;
    while(T!=NULL||top!=0)
    {
    	while(T!=NULL)
    	{
    		printf("%d ",T->data);
    		STACK[++top]=T;
    		T=T->Lchild;
		}
		if(top!=0)
		{
			T=STACK[top--];                            
			T=T->Rchild;
		}
	}
}
void InOrder(Tree* T)								  //����ݹ���������� 
{
	if(T!=NULL)
	{
		InOrder(T->Lchild);
		printf("%d ",T->data);
		InOrder(T->Rchild);
	}
}
void nInOrder(Tree* T)                                //����ǵݹ���������� 
{
	Tree* STACK[maxlength];                           //��ջ������������Ľڵ� 
    int top=0;
    while(T!=NULL||top!=0)
    {
    	while(T!=NULL)
    	{
    		STACK[++top]=T;
    		T=T->Lchild;
		}
		if(top!=0)
		{
			T=STACK[top--];
			printf("%d ",T->data);
			T=T->Rchild;
		}
	}
}
void PostOrder(Tree* T)                               //����ݹ���������� 
{
	if(T!=NULL)
	{
		PostOrder(T->Lchild);
		PostOrder(T->Rchild);
		printf("%d ",T->data);
	}
}
void nPostOrder(Tree* T)                              //����ǵݹ���������� 
{
	typedef struct STACK                              //ջ�����������Ľڵ㣬flag��־ 
	{
		Tree* p;
		int flag=0;
	}STACK;
	STACK s[maxlength];
	int top=0;
	while((T!=NULL)||(top!=0))
	{
		while(T!=NULL)
		{
			top++;s[top].p=T;s[top].flag=1;T=T->Lchild;
		}
		while(top!=0&&s[top].flag==2)
		{
			T=s[top].p;top--;printf("%d ",T->data);  //ջ�ǿ���flag=2ʱ��ջ������ڵ� 
		}
		if(top!=0)
		{
			s[top].flag=2;T=s[top].p->Rchild;        //ջ�ǿ�ʱ��ջ��Ԫ�ر�־��Ϊ2 
		}else
		{
			T=NULL;                                  //�߽���������ֹջ��ʱTָ��ͷ�ڵ� 
		}
	}
}
Queue* init(Queue* p)                                 //��ʼ������ 
{
	p->front=(QueueNode*)malloc(sizeof(QueueNode));   //���еı�ͷ 
	p->front->next=NULL;
	p->rear=p->front;
	return p;
}
Queue* enqueue(Queue* p,Tree* t)                      //��Ӳ��� 
{
	QueueNode* n=(QueueNode*)malloc(sizeof(QueueNode));
	n->data=t;
	n->next=NULL;
	p->rear->next=n;
	p->rear=n;
	return p;
}
Tree* dequeue(Queue* p)                               //���Ӳ��������س��ӽڵ�ָ������ָ�� 
{
	QueueNode* Temp=(QueueNode*)malloc(sizeof(QueueNode));
	Temp=p->front->next;
	if(Temp->next==NULL)
	{
		p->rear=p->front;
	}else
	{
		p->front->next=Temp->next;
	}
	Tree* x=Temp->data;
	free(Temp);
	return x;
}
void LevelOrder(Tree* T)                              //�ǵݹ������������� 
{
    Queue *p=(Queue*)malloc(sizeof(Queue));Tree* x;   //pΪָ�����ͷβָ��ڵ��ָ�� 
    p=init(p);                                        //��ʼ������ 
    p=enqueue(p,T);                                   //������� 
    while(p->rear!=p->front)                          //ѭ��ֱ������Ϊ�� 
	{
    	x=dequeue(p);                                 //����Ԫ�س��ӣ�������׵����ڵ� 
    	printf("%d ",x->data);
    	if(x->Lchild!=NULL){                          //������ڵ����������������� 
		p=enqueue(p,x->Lchild);}
   	    if(x->Rchild!=NULL){
        p=enqueue(p,x->Rchild);}
    }
}
int isCBT(Tree* T)                                    //�ж��Ƿ�Ϊ��ȫ������ 
{
    Queue *p=(Queue*)malloc(sizeof(Queue));           //ָ�����ͷβָ��ڵ��ָ�� 
    p=init(p);                                        //��ʼ������ 
    enqueue(p,T);                                     //������� 
    int leaf=0;                                       //leaf�ж��Ƿ����Ҷ�׶Σ����ĳ�ڵ���������������Ҷ�׶� 
    while(p->rear!=p->front)                          //ѭ��ֱ������Ϊ�� 
	{
    	Tree* x=dequeue(p);
    	if(leaf==0)                                   //��Ҷ�׶� 
	    {
			if(x->Lchild==NULL)                       //���ڵ�������Ϊ�յ���� 
	    	{
	    		if(x->Rchild!=NULL)                   //��ʱ���������ǿգ��ز�����ȫ������������0 
	    		{
	    			return 0;
				}else if(x->Rchild==NULL)             //����ʱ������Ϊ�գ�����Ҷ�׶� 
				{
					leaf=1;
				}
			}else if(x->Lchild!=NULL)                 //�������ǿ� 
			{
	   			enqueue(p,x->Lchild);                 //��������� 
	   	    	if(x->Rchild!=NULL)                   //���������ǿգ���������� 
	        	{
	        		enqueue(p,x->Rchild);
				}else if(x->Rchild==NULL)             //���������գ�����Ҷ�׶� 
				{
					leaf=1;
				}
	        }
	    }else if(leaf==1)                             //Ҷ�׶� 
	    {
	    	if(x->Lchild==NULL&&x->Rchild==NULL)      //��ʣ��ڵ������������������ȫ������������0 
	    	{
			}
	    	else
	    	return 0;
		}
    }
    return 1;                                         //�ж���ϣ�Ϊ��ȫ������ 
}
int size(Queue* p)                                    //��ǰ���еĳ��� 
{
	QueueNode* q;
	q=p->front;
	int count=0;
	while(q!=p->rear)
	{
		count++;
		q=q->next;
	}
	return count;
}
int width(Tree* T)									  //�ǵݹ���������Ŀ�� 
{                                             		  
	 if(T==NULL)
	 {
	     return 0;
	 }
	 int max=1;                                       //max��������������֮�����ֵ 
	 Queue *s=(Queue*)malloc(sizeof(Queue));          //��ʼ�� 
	 s=init(s);
	 enqueue(s,T);                                    //������� 
	 while(true)
	 {
 	    int len=size(s);                              //��ǰ��(���У��ĳ��� 
	    if(len==0) break;                             //���г���Ϊ0����ֹѭ�� 
	    while(len>0)                                  //�����г��ȴ���0�����Ͻ��������ڵ���ӣ�ͬʱ������������� 
		{                                             //��������Ԫ��ȫ�����ӣ�lenΪ0��ѭ��ֹͣ��ͬʱ������Ԫ��Ϊ��һ��ȫ���ڵ� 
		    Tree* t=dequeue(s);
	   		if(t->Lchild)
	    	enqueue(s,t->Lchild );
	   		if(s,t->Rchild)
	    	enqueue(s,t->Rchild ); 
			len--; 
  	    }
	if(max>=size(s))                                  //�Ƚ�����֮���ȣ��������ֵ 
	{
		max=max;
	}else
	{
		max=size(s);
	}
 	}
	 return max;                                     //����max��Ϊ���в������ֵ 
}
void Menu()                                           //�˵� 
{
	int flag;
	Tree* T;
	printf("��ѡ���ܣ�\n");
	printf("1.����ݹ����������\n");
	printf("2.����ǵݹ����������\n");
	printf("3.����ݹ����������\n");
	printf("4.����ǵݹ����������\n");
	printf("5.����ݹ����������\n");
	printf("6.����ǵݹ����������\n");
	printf("7.����ǵݹ����������\n");
	printf("8.�ж��Ƿ�Ϊ��ȫ������\n");
	printf("9.�ǵݹ�����������\n");
	scanf("%d",&flag);
	switch(flag)
	{
		case 1:
			T=Creat();
			printf("�������У�"); 
			PreOrder(T);
			break;
		case 2:
			T=Creat();
			printf("�������У�"); 
			nPreOrder(T);
			break;
		case 3:
			T=Creat();
			printf("�������У�"); 
			InOrder(T);
			break;
		case 4:
			T=Creat();
			printf("�������У�"); 
			nInOrder(T);
			break;	
		case 5:
			T=Creat();
			printf("�������У�"); 
			PostOrder(T);
			break;	
		case 6:
			T=Creat();
			printf("�������У�"); 
			nPostOrder(T);
			break;
		case 7:
			T=Creat();
			printf("�������У�"); 
			LevelOrder(T);
			break;	
		case 8:
			T=Creat();
			flag=isCBT(T);
			printf("\n");
			if(flag==1)
			printf("����ȫ������");
			if(flag==0)
			printf("����ȫ������"); 
			break;	
		case 9:
			T=Creat();
			flag=width(T);
			printf("���Ϊ%d",flag);
			break;				
	}
}
int main()
{
	Menu();
}














