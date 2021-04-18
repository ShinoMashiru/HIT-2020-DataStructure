#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define maxlength 100
typedef struct LIST									//定义链表结构体
{                                                     
	double coef;                 //系数 
	int exp;                     //指数 
	struct LIST* next;
}List; 
List* Creat()                                       //创建多项式(循环链表结构） 
{
    double coef;
    int exp;
    List *head,*p,*r;
    head=(List*)malloc(sizeof(List));
    head->coef=0;                                    //初始化
    head->exp=-1;
    p=head;
    printf("\n  请输入各项的系数和指数（如 1 2），均为0时结束输入\n");
    while(1)
    {
        printf("输入系数和指数:");
        scanf("%lf %d",&coef,&exp);
        if(coef==0)
        break;
        r=(List*)malloc(sizeof(List));
        r->coef=coef;
        r->exp=exp;
        p->next=r;
        p=r;
    }
    r->next=head;                                   //循环链表首尾相连
    return head;
}
void Print(List* L)                                 //打印多项式
{
	List* p=L->next;
	printf("\n");
	printf("运算后多项式为:");
	while(p!=L)
	{
		printf("%lfx^%d",p->coef,p->exp);
		if(p->next->coef>0)
		printf("+");
		p=p->next;
	}
	printf("\n");
}
List* Sort(List* L)									//任意多项式降幂排序
{
	double c;
	int e;
	List *p,*q;
	p=L->next;q=L->next;
	while(p->next!=L)
	{
		q=p->next;
		while(q->next!=L->next)
		{
			if(q->exp>p->exp)
			{
				c=p->coef;
				p->coef=q->coef;
				q->coef=c;
				e=p->exp;
				p->exp=q->exp;
				q->exp=e;	
			}
			q=q->next;
		}
		p=p->next;
	}
	return L;
}  										 
List* Add(List* L1,List* L2)				        //多项式相加函数,输出返回到L1链(类似作业1中合并两个排序好的链表，节省空间减少节点分配操作） 
{
    List *p,*q,*pr,*qr;
    float x;
    p=L1->next;
    q=L2->next;
    pr=L1;                                          //初始化 
    while((p!=L1)&&(q!=L2))                         //循环直到L1,或L2遍历到末尾 
    {
        if(p->exp>q->exp)                           //把L2插入到L1中，指数相等的项合并后插入 
        {
            pr=p;
            p=p->next;
        }
       if(p->exp<q->exp)
       {
           qr=q->next;
           q->next=p;
           pr->next=q;
           pr=q;
           q=qr;
       }
       if(p->exp==q->exp)
       {
           x=p->coef+q->coef;
           if(x!=0)
           {
               p->coef=x;
               pr=p;
           }
           else
           {
               pr->next=p->next;
               free(p);
           }
           p=pr->next;
           qr=q;
           q=q->next;
           free(qr);
       }
    }
    if(q!=L2)                                       //L2剩余部分插入到L1 
    {
        qr=q;
        while(qr->next!=L2)
            qr=qr->next;
        pr->next=q;
        qr->next=L1;
    }
    return L1;	
}
List* Mult(List* L1,List* L2)						//多项式相乘函数
{
    List *p,*q,*temp,*m,*n,*l;             		 //p,q指向L1,L2节点，temp乘法过程中新链表，m指向temp的节点，n给temp添加新节点，l乘积结果链表 
    int exp;                                     //整型指数
    float coef;                                  //系数 
    l=(List *)malloc(sizeof(List)); 			 //为最后输出的乘积链表l开辟头节点
    l->coef=0;
    l->next=l;               					 //循环链表尾指向头 
    p=L1->next;              					 //头节点未储存实际运算的数据，跳过 
    while(p!=L1)           						 //L1链表与L2各项相乘
    {
       temp=(List *)malloc(sizeof(List));   	 //在内部创头节点为新生链表准备 即L1中每一项与L2中各项相乘构成一新链表
       temp->next=NULL;                          //置空链表
       m=temp;                                   //m指针指向temp节点定位 
       q=L2->next;                               //初始化q指针 
        while(q!=L2)
        {
            n=(List *)malloc(sizeof(List)); 	 //建立新节点n
            exp=p->exp+q->exp;     				 //指数相加 
            coef=p->coef*q->coef;    			 //系数相乘
            n->coef=coef;        				 //新节点系数域赋值 
            n->exp=exp;           				 //新节点指数域赋值 
            m->next=n;           				 //添加新节点 
            m=m->next;         					 //后移指针m，用以下次添加新节点 
            q=q->next;         					 //指向L2下一项 
        }
        m->next=temp;                            //循环链表temp尾指向头节点 
        Add(l,temp);							 //temp加到l上 
        p=p->next;              				 //指向L1下一项
        free(temp);                             
    }
    return l;
}
List* Minus(List*L1,List* L2) 						//多项式相减函数,输出返回到L1链(L1-L2)
{
	List* p;                                        //L1-L2相当于将L2系数*-1后相加 
	p=L2->next;
	while(p->next!=L2->next)
	{
		p->coef=p->coef*(-1);
		p=p->next;
	}
	L1=Add(L1,L2); 
	return L1;
}
List* Div(List*L1,List* L2)                         //多项式除法函数(L1/L2)--屏幕 
{
	List *p,*q,*temp,*m,*n,*l,*s,*s1;            //p,q指向L1,L2节点，temp除法过程中储存乘法结果链表，m指向l的节点，n给l添加新节点，l除法结果链表,s->s1储存每次除法结果 
    int exp;                                     //整型指数
    float coef;                                  //系数 
    l=(List *)malloc(sizeof(List)); 			 //除法结果链
    l->coef=0;
    l->next=l;             					     //循环链表尾指向头 
	s=(List *)malloc(sizeof(List)); 	         //中间运算链s->s1
	s1=(List *)malloc(sizeof(List)); 
	s->next=s1;
	s1->next=s;  
	m=l;            					         
	p=L1->next;									 //头节点未储存实际运算的数据，跳过
	q=L2->next; 
    while(p->exp>=q->exp)           						 //L1链表与L2各项相乘
    { 
        n=(List *)malloc(sizeof(List)); 	 //建立新节点n
        exp=p->exp-q->exp;     				 //指数相加 
        coef=p->coef/q->coef;    			 //系数相除 
        n->coef=coef;        				 //新节点系数域赋值 
        n->exp=exp;           				 //新节点指数域赋值 
        m->next=n;           				 //添加新节点 
        m=m->next;         					 //后移指针m，用以下次添加新节点
		m->next=l; 
        s1->coef=coef;        				 //新节点系数域赋值 
        s1->exp=exp;           				 //新节点指数域赋值 
        temp=Mult(s,L2);
        L1=Minus(L1,temp);
        p=L1->next;
		free(temp);                   
    }
    printf("商式的");
	Print(l); 
    printf("余项的"); 
    Print(L1);
	
}
List* Dif(List* L,int k)                       		//多项式k阶导数
{
	List* p,*q,*pr;
	p=L->next;
	pr=p;
	while(p!=L)
	{
		if(p->exp>=k)
		{
			for(int i=p->exp;i>p->exp-k;i--)
			p->coef=p->coef*i;
			p->exp=p->exp-k;
			pr=p;p=p->next;
		}else
		{
			p=p->next;
			pr->next=p;
		}
	}
	return L;
} 
double Value(List* L,double x)                      //x代入多项式求值 
{
	double sum=0;
	List* p=L->next;
	while(p!=L)
	{
		sum+=(pow(x,p->exp))*p->coef;	
		p=p->next;
	}	
	return sum;
}
List* Read(char s[])								//读入文本文件中的多项式(输入格式 系数1x^指数1 系数2x^指数2 省略运算符（加号）两项之间有空格） 
{
	List* l,*q,*n;
	int size;
	char*p=s;
	int i=0;int count=0;
	while(s[i]!='\0')
	{
		if(s[i]==' ')
		count++;
		i++;
	}
	l=(List *)malloc(sizeof(List));
	l->next=l;q=l;l->coef=0;
	for(int j=0;j<count;j++)
	{
		n=(List *)malloc(sizeof(List));
		q->next=n;
		q=q->next;
		q->next=l;
	    sscanf(p,"%lfx^%d%n ",&n->coef,&n->exp,&size);
	    p+=size;
	}
	return l;				
} 
void Write(List* L,FILE* fp)                        //将链表写入在文本文件末尾 
{
	List* p=L->next;
	fprintf(fp,"\n");
	fprintf(fp,"运算后多项式为:");
	while(p!=L)
	{
		fprintf(fp,"%lfx^%d",p->coef,p->exp);
		if(p->next->coef>0)
		fprintf(fp,"+");
		p=p->next;
	}
	fprintf(fp,"\n");
}
List* fDiv(List*L1,List* L2,FILE* fp)               //多项式除法函数(L1/L2)--文件 
{
	List *p,*q,*temp,*m,*n,*l,*s,*s1;            //p,q指向L1,L2节点，temp除法过程中储存乘法结果链表，m指向l的节点，n给l添加新节点，l除法结果链表,s->s1储存每次除法结果 
    int exp;                                     //整型指数
    float coef;                                  //系数 
    l=(List *)malloc(sizeof(List)); 			 //除法结果链
    l->coef=0;
    l->next=l;             					     //循环链表尾指向头 
	s=(List *)malloc(sizeof(List)); 	         //中间运算链s->s1
	s1=(List *)malloc(sizeof(List)); 
	s->next=s1;
	s1->next=s;  
	m=l;            					         
	p=L1->next;									 //头节点未储存实际运算的数据，跳过
	q=L2->next; 
    while(p->exp>=q->exp)           						 //L1链表与L2各项相乘
    { 
        n=(List *)malloc(sizeof(List)); 	 //建立新节点n
        exp=p->exp-q->exp;     				 //指数相加 
        coef=p->coef/q->coef;    			 //系数相除 
        n->coef=coef;        				 //新节点系数域赋值 
        n->exp=exp;           				 //新节点指数域赋值 
        m->next=n;           				 //添加新节点 
        m=m->next;         					 //后移指针m，用以下次添加新节点
		m->next=l; 
        s1->coef=coef;        				 //新节点系数域赋值 
        s1->exp=exp;           				 //新节点指数域赋值 
        temp=Mult(s,L2);
        L1=Minus(L1,temp);
        p=L1->next;
		free(temp);                   
    }
    fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","a");
	fprintf(fp,"商式为:");
	p=l->next;
	while(p!=l)
	{
		fprintf(fp,"%lfx^%d",p->coef,p->exp);
		if(p->next->coef>0)
		fprintf(fp,"+");
		p=p->next;
	}
	fprintf(fp,"\n");
	p=L1->next; 
    fprintf(fp,"余项为"); 
    while(p!=L1)
	{
		fprintf(fp,"%lfx^%d",p->coef,p->exp);
		if(p->next->coef>0)
		fprintf(fp,"+");
		p=p->next;
	}
	fclose(fp);
}
void Menu1()                                        //菜单-屏幕 
{
	List *L1,*L2;
	int flag,k;
	double x;
	printf("1.任意输入多项式，输出按降幂排列\n");
	printf("2.多项式加法\n");
	printf("3.多项式减法\n");
	printf("4.多项式乘法\n");
	printf("5.多项式除法\n");
	printf("6.多项式k阶导函数\n");
	printf("7.多项式x=x0处求值\n");
	printf("选择功能"); 
	scanf("%d",&flag);
	switch(flag)
	{
		case 1:
			L1=Creat();
			L1=Sort(L1);
			Print(L1);
			break;
		case 2:
			L1=Creat();
			L2=Creat();
			L1=Sort(L1);
			L2=Sort(L2); 
			L1=Add(L1,L2);
			Print(L1);
		    break;
		case 3:
			L1=Creat();
			L2=Creat();
			L1=Sort(L1);
			L2=Sort(L2);
			L1=Minus(L1,L2);
			Print(L1);
		    break;
		case 4:
		   	L1=Creat();
			L2=Creat();
			L1=Sort(L1);
			L2=Sort(L2);
			L1=Mult(L1,L2);
			Print(L1);
		    break;	
		case 5:
		   	L1=Creat();
			L2=Creat();
			L1=Sort(L1);
			L2=Sort(L2);
			L1=Div(L1,L2);
			Print(L1);
		    break;
		case 6:
			L1=Creat();
			L1=Sort(L1);
			printf("请输入求导阶数k：");
			scanf("%d",&k);
			L1=Dif(L1,k);
			Print(L1);
			break;
		case 7:
			L1=Creat();
			L1=Sort(L1);
			printf("请输入x0的值:");
			scanf("%lf",&x);
			x=Value(L1,x);
			printf("\n");
			printf("多项式的值为%lf",x);
			break;
		default:
		    exit(0);			
	}
}
void Menu2()										//菜单-文件 
{
	List *L1,*L2;
	char s[maxlength];
	int flag,k;
	double x;
	FILE* fp;
	printf("1.任意输入多项式，输出按降幂排列\n");
	printf("2.多项式加法\n");
	printf("3.多项式减法\n");
	printf("4.多项式乘法\n");
	printf("5.多项式除法\n");
	printf("6.多项式k阶导函数\n");
	printf("7.多项式x=x0处求值\n");
	printf("选择功能"); 
	scanf("%d",&flag);
	switch(flag)
	{
		case 1:
			fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1);
			fclose(fp);
			fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","a");
			Write(L1,fp);
			fclose(fp);
			break;
		case 2:
			fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1); 
			fgets(s,maxlength,fp);
			L2=Read(s);
			L2=Sort(L2);
			fclose(fp);
			fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","a");
			L1=Add(L1,L2);
			Write(L1,fp);
			fclose(fp);
			break;
		case 3:
			fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1); 
			fgets(s,maxlength,fp);
			L2=Read(s);
			L2=Sort(L2);
			fclose(fp);
			fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","a");
			L1=Minus(L1,L2);
			Write(L1,fp);
			fclose(fp);
			break;
		case 4:
		    fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1); 
			fgets(s,maxlength,fp);
			L2=Read(s);
			L2=Sort(L2);
			fclose(fp);
			fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","a");
			L1=Mult(L1,L2);
			Write(L1,fp);
			fclose(fp);
			break;
		case 5:
		   	fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1); 
			fgets(s,maxlength,fp);
			L2=Read(s);
			L2=Sort(L2);
			fclose(fp);
			fDiv(L1,L2,fp);
			break;
		case 6:
			fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1); 
			fgets(s,maxlength,fp);
			fclose(fp);
			sscanf(s,"%d",&k);
			L1=Dif(L1,k);
			fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","a");
			Write(L1,fp);
			fclose(fp);
			break;
		case 7:
			fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1); 
			fgets(s,maxlength,fp);
			sscanf(s,"%lf",&x);
			x=Value(L1,x);
			fclose(fp);
			fp=fopen("C:\\Users\\dell\\Desktop\\多项式.txt","a");
			fprintf(fp,"\n");
			fprintf(fp,"%lf",x);
			break;
		default:
		    exit(0);
	}
} 
int main()
{
	int flag;
	printf("1.屏幕输入输出	2.文件输入输出"); 
	scanf("%d",&flag);
	if(flag==1)
	Menu1();
	if(flag==2)
	Menu2();
}













