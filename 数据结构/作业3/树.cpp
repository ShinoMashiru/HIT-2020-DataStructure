#include<stdio.h>
#include<stdlib.h>
#define maxlength 100
typedef struct Tree									  //树的节点 
{
    int data;
    Tree  *Lchild;
    Tree  *Rchild;
}Tree; 
typedef struct QueueNode							  //队列的节点 
{
	Tree* data;
	QueueNode *next;
}QueueNode;
typedef struct Queue                                  //队列的头尾指针构成的结构体 
{
	QueueNode* front;
	QueueNode* rear;
}Queue;
Tree* Creat()                                         //先序构造二叉树(先将二叉树扩充，外节点标为-1，输入扩充后的先序序列） 
{
	int k;
    Tree  *T;
    printf("请输入根节点:");
    scanf("%d",&k);
    if(k==-1)                                         //输入为-1表示指向空指针 
	{
		T=NULL;
	}else
    {
        T=(Tree*)malloc(sizeof(Tree));
        T->data=k;
        printf("\n请输入%d结点的左子结点(如果没有那么输入-1代表空):",T->data );
        T->Lchild=Creat();
        printf("\n请输入%d结点的右子结点(如果没有那么输入-1代表空):",T->data );
        T->Rchild=Creat();
    }
    return T;
}
void PreOrder(Tree* T)                                //先序递归遍历二叉树 
{
	if(T!=NULL)
	{
		printf("%d ",T->data);
		PreOrder(T->Lchild);
		PreOrder(T->Rchild);
	}
}
void nPreOrder(Tree* T)								  //先序非递归遍历二叉树 
{
	Tree* STACK[maxlength];                           //用栈保存先序访问的节点 
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
void InOrder(Tree* T)								  //中序递归遍历二叉树 
{
	if(T!=NULL)
	{
		InOrder(T->Lchild);
		printf("%d ",T->data);
		InOrder(T->Rchild);
	}
}
void nInOrder(Tree* T)                                //中序非递归遍历二叉树 
{
	Tree* STACK[maxlength];                           //用栈保存中序遍历的节点 
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
void PostOrder(Tree* T)                               //后序递归遍历二叉树 
{
	if(T!=NULL)
	{
		PostOrder(T->Lchild);
		PostOrder(T->Rchild);
		printf("%d ",T->data);
	}
}
void nPostOrder(Tree* T)                              //后序非递归遍历二叉树 
{
	typedef struct STACK                              //栈保存后序遍历的节点，flag标志 
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
			T=s[top].p;top--;printf("%d ",T->data);  //栈非空且flag=2时弹栈，输出节点 
		}
		if(top!=0)
		{
			s[top].flag=2;T=s[top].p->Rchild;        //栈非空时，栈顶元素标志变为2 
		}else
		{
			T=NULL;                                  //边界条件，防止栈空时T指向头节点 
		}
	}
}
Queue* init(Queue* p)                                 //初始化队列 
{
	p->front=(QueueNode*)malloc(sizeof(QueueNode));   //队列的表头 
	p->front->next=NULL;
	p->rear=p->front;
	return p;
}
Queue* enqueue(Queue* p,Tree* t)                      //入队操作 
{
	QueueNode* n=(QueueNode*)malloc(sizeof(QueueNode));
	n->data=t;
	n->next=NULL;
	p->rear->next=n;
	p->rear=n;
	return p;
}
Tree* dequeue(Queue* p)                               //出队操作，返回出队节点指向树的指针 
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
void LevelOrder(Tree* T)                              //非递归层序遍历二叉树 
{
    Queue *p=(Queue*)malloc(sizeof(Queue));Tree* x;   //p为指向队列头尾指针节点的指针 
    p=init(p);                                        //初始化队列 
    p=enqueue(p,T);                                   //树根入队 
    while(p->rear!=p->front)                          //循环直到队列为空 
	{
    	x=dequeue(p);                                 //队首元素出队，输出队首的树节点 
    	printf("%d ",x->data);
    	if(x->Lchild!=NULL){                          //如果树节点的有左右子树，入队 
		p=enqueue(p,x->Lchild);}
   	    if(x->Rchild!=NULL){
        p=enqueue(p,x->Rchild);}
    }
}
int isCBT(Tree* T)                                    //判断是否为完全二叉树 
{
    Queue *p=(Queue*)malloc(sizeof(Queue));           //指向队列头尾指针节点的指针 
    p=init(p);                                        //初始化队列 
    enqueue(p,T);                                     //树根入队 
    int leaf=0;                                       //leaf判断是否进入叶阶段，如果某节点无右子树，进入叶阶段 
    while(p->rear!=p->front)                          //循环直到队列为空 
	{
    	Tree* x=dequeue(p);
    	if(leaf==0)                                   //非叶阶段 
	    {
			if(x->Lchild==NULL)                       //若节点左子树为空的情况 
	    	{
	    		if(x->Rchild!=NULL)                   //此时若右子树非空，必不是完全二叉树，返回0 
	    		{
	    			return 0;
				}else if(x->Rchild==NULL)             //若此时右子树为空，开启叶阶段 
				{
					leaf=1;
				}
			}else if(x->Lchild!=NULL)                 //左子树非空 
			{
	   			enqueue(p,x->Lchild);                 //左子树入队 
	   	    	if(x->Rchild!=NULL)                   //若右子树非空，右子树入队 
	        	{
	        		enqueue(p,x->Rchild);
				}else if(x->Rchild==NULL)             //若右子树空，开启叶阶段 
				{
					leaf=1;
				}
	        }
	    }else if(leaf==1)                             //叶阶段 
	    {
	    	if(x->Lchild==NULL&&x->Rchild==NULL)      //若剩余节点存在左右子树，非完全二叉树，返回0 
	    	{
			}
	    	else
	    	return 0;
		}
    }
    return 1;                                         //判断完毕，为完全二叉树 
}
int size(Queue* p)                                    //求当前队列的长度 
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
int width(Tree* T)									  //非递归求二叉树的宽度 
{                                             		  
	 if(T==NULL)
	 {
	     return 0;
	 }
	 int max=1;                                       //max函数，储存两层之间最大值 
	 Queue *s=(Queue*)malloc(sizeof(Queue));          //初始化 
	 s=init(s);
	 enqueue(s,T);                                    //树根入队 
	 while(true)
	 {
 	    int len=size(s);                              //当前层(队列）的长度 
	    if(len==0) break;                             //队列长度为0，终止循环 
	    while(len>0)                                  //当队列长度大于0，不断将本层树节点出队，同时将左右子树入队 
		{                                             //当将本层元素全部出队，len为0，循环停止，同时队列中元素为下一层全部节点 
		    Tree* t=dequeue(s);
	   		if(t->Lchild)
	    	enqueue(s,t->Lchild );
	   		if(s,t->Rchild)
	    	enqueue(s,t->Rchild ); 
			len--; 
  	    }
	if(max>=size(s))                                  //比较两层之间宽度，返回最大值 
	{
		max=max;
	}else
	{
		max=size(s);
	}
 	}
	 return max;                                     //最终max即为所有层中最大值 
}
void Menu()                                           //菜单 
{
	int flag;
	Tree* T;
	printf("请选择功能：\n");
	printf("1.先序递归遍历二叉树\n");
	printf("2.先序非递归遍历二叉树\n");
	printf("3.中序递归遍历二叉树\n");
	printf("4.中序非递归遍历二叉树\n");
	printf("5.后序递归遍历二叉树\n");
	printf("6.后序非递归遍历二叉树\n");
	printf("7.层序非递归遍历二叉树\n");
	printf("8.判断是否为完全二叉树\n");
	printf("9.非递归求二叉树宽度\n");
	scanf("%d",&flag);
	switch(flag)
	{
		case 1:
			T=Creat();
			printf("先序序列："); 
			PreOrder(T);
			break;
		case 2:
			T=Creat();
			printf("先序序列："); 
			nPreOrder(T);
			break;
		case 3:
			T=Creat();
			printf("中序序列："); 
			InOrder(T);
			break;
		case 4:
			T=Creat();
			printf("中序序列："); 
			nInOrder(T);
			break;	
		case 5:
			T=Creat();
			printf("后序序列："); 
			PostOrder(T);
			break;	
		case 6:
			T=Creat();
			printf("后序序列："); 
			nPostOrder(T);
			break;
		case 7:
			T=Creat();
			printf("层序序列："); 
			LevelOrder(T);
			break;	
		case 8:
			T=Creat();
			flag=isCBT(T);
			printf("\n");
			if(flag==1)
			printf("是完全二叉树");
			if(flag==0)
			printf("非完全二叉树"); 
			break;	
		case 9:
			T=Creat();
			flag=width(T);
			printf("宽度为%d",flag);
			break;				
	}
}
int main()
{
	Menu();
}














