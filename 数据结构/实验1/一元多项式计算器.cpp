#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define maxlength 100
typedef struct LIST									//��������ṹ��
{                                                     
	double coef;                 //ϵ�� 
	int exp;                     //ָ�� 
	struct LIST* next;
}List; 
List* Creat()                                       //��������ʽ(ѭ������ṹ�� 
{
    double coef;
    int exp;
    List *head,*p,*r;
    head=(List*)malloc(sizeof(List));
    head->coef=0;                                    //��ʼ��
    head->exp=-1;
    p=head;
    printf("\n  ����������ϵ����ָ������ 1 2������Ϊ0ʱ��������\n");
    while(1)
    {
        printf("����ϵ����ָ��:");
        scanf("%lf %d",&coef,&exp);
        if(coef==0)
        break;
        r=(List*)malloc(sizeof(List));
        r->coef=coef;
        r->exp=exp;
        p->next=r;
        p=r;
    }
    r->next=head;                                   //ѭ��������β����
    return head;
}
void Print(List* L)                                 //��ӡ����ʽ
{
	List* p=L->next;
	printf("\n");
	printf("��������ʽΪ:");
	while(p!=L)
	{
		printf("%lfx^%d",p->coef,p->exp);
		if(p->next->coef>0)
		printf("+");
		p=p->next;
	}
	printf("\n");
}
List* Sort(List* L)									//�������ʽ��������
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
List* Add(List* L1,List* L2)				        //����ʽ��Ӻ���,������ص�L1��(������ҵ1�кϲ���������õ�������ʡ�ռ���ٽڵ��������� 
{
    List *p,*q,*pr,*qr;
    float x;
    p=L1->next;
    q=L2->next;
    pr=L1;                                          //��ʼ�� 
    while((p!=L1)&&(q!=L2))                         //ѭ��ֱ��L1,��L2������ĩβ 
    {
        if(p->exp>q->exp)                           //��L2���뵽L1�У�ָ����ȵ���ϲ������ 
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
    if(q!=L2)                                       //L2ʣ�ಿ�ֲ��뵽L1 
    {
        qr=q;
        while(qr->next!=L2)
            qr=qr->next;
        pr->next=q;
        qr->next=L1;
    }
    return L1;	
}
List* Mult(List* L1,List* L2)						//����ʽ��˺���
{
    List *p,*q,*temp,*m,*n,*l;             		 //p,qָ��L1,L2�ڵ㣬temp�˷�������������mָ��temp�Ľڵ㣬n��temp����½ڵ㣬l�˻�������� 
    int exp;                                     //����ָ��
    float coef;                                  //ϵ�� 
    l=(List *)malloc(sizeof(List)); 			 //Ϊ�������ĳ˻�����l����ͷ�ڵ�
    l->coef=0;
    l->next=l;               					 //ѭ������βָ��ͷ 
    p=L1->next;              					 //ͷ�ڵ�δ����ʵ����������ݣ����� 
    while(p!=L1)           						 //L1������L2�������
    {
       temp=(List *)malloc(sizeof(List));   	 //���ڲ���ͷ�ڵ�Ϊ��������׼�� ��L1��ÿһ����L2�и�����˹���һ������
       temp->next=NULL;                          //�ÿ�����
       m=temp;                                   //mָ��ָ��temp�ڵ㶨λ 
       q=L2->next;                               //��ʼ��qָ�� 
        while(q!=L2)
        {
            n=(List *)malloc(sizeof(List)); 	 //�����½ڵ�n
            exp=p->exp+q->exp;     				 //ָ����� 
            coef=p->coef*q->coef;    			 //ϵ�����
            n->coef=coef;        				 //�½ڵ�ϵ����ֵ 
            n->exp=exp;           				 //�½ڵ�ָ����ֵ 
            m->next=n;           				 //����½ڵ� 
            m=m->next;         					 //����ָ��m�������´�����½ڵ� 
            q=q->next;         					 //ָ��L2��һ�� 
        }
        m->next=temp;                            //ѭ������tempβָ��ͷ�ڵ� 
        Add(l,temp);							 //temp�ӵ�l�� 
        p=p->next;              				 //ָ��L1��һ��
        free(temp);                             
    }
    return l;
}
List* Minus(List*L1,List* L2) 						//����ʽ�������,������ص�L1��(L1-L2)
{
	List* p;                                        //L1-L2�൱�ڽ�L2ϵ��*-1����� 
	p=L2->next;
	while(p->next!=L2->next)
	{
		p->coef=p->coef*(-1);
		p=p->next;
	}
	L1=Add(L1,L2); 
	return L1;
}
List* Div(List*L1,List* L2)                         //����ʽ��������(L1/L2)--��Ļ 
{
	List *p,*q,*temp,*m,*n,*l,*s,*s1;            //p,qָ��L1,L2�ڵ㣬temp���������д���˷��������mָ��l�Ľڵ㣬n��l����½ڵ㣬l�����������,s->s1����ÿ�γ������ 
    int exp;                                     //����ָ��
    float coef;                                  //ϵ�� 
    l=(List *)malloc(sizeof(List)); 			 //���������
    l->coef=0;
    l->next=l;             					     //ѭ������βָ��ͷ 
	s=(List *)malloc(sizeof(List)); 	         //�м�������s->s1
	s1=(List *)malloc(sizeof(List)); 
	s->next=s1;
	s1->next=s;  
	m=l;            					         
	p=L1->next;									 //ͷ�ڵ�δ����ʵ����������ݣ�����
	q=L2->next; 
    while(p->exp>=q->exp)           						 //L1������L2�������
    { 
        n=(List *)malloc(sizeof(List)); 	 //�����½ڵ�n
        exp=p->exp-q->exp;     				 //ָ����� 
        coef=p->coef/q->coef;    			 //ϵ����� 
        n->coef=coef;        				 //�½ڵ�ϵ����ֵ 
        n->exp=exp;           				 //�½ڵ�ָ����ֵ 
        m->next=n;           				 //����½ڵ� 
        m=m->next;         					 //����ָ��m�������´�����½ڵ�
		m->next=l; 
        s1->coef=coef;        				 //�½ڵ�ϵ����ֵ 
        s1->exp=exp;           				 //�½ڵ�ָ����ֵ 
        temp=Mult(s,L2);
        L1=Minus(L1,temp);
        p=L1->next;
		free(temp);                   
    }
    printf("��ʽ��");
	Print(l); 
    printf("�����"); 
    Print(L1);
	
}
List* Dif(List* L,int k)                       		//����ʽk�׵���
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
double Value(List* L,double x)                      //x�������ʽ��ֵ 
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
List* Read(char s[])								//�����ı��ļ��еĶ���ʽ(�����ʽ ϵ��1x^ָ��1 ϵ��2x^ָ��2 ʡ����������Ӻţ�����֮���пո� 
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
void Write(List* L,FILE* fp)                        //������д�����ı��ļ�ĩβ 
{
	List* p=L->next;
	fprintf(fp,"\n");
	fprintf(fp,"��������ʽΪ:");
	while(p!=L)
	{
		fprintf(fp,"%lfx^%d",p->coef,p->exp);
		if(p->next->coef>0)
		fprintf(fp,"+");
		p=p->next;
	}
	fprintf(fp,"\n");
}
List* fDiv(List*L1,List* L2,FILE* fp)               //����ʽ��������(L1/L2)--�ļ� 
{
	List *p,*q,*temp,*m,*n,*l,*s,*s1;            //p,qָ��L1,L2�ڵ㣬temp���������д���˷��������mָ��l�Ľڵ㣬n��l����½ڵ㣬l�����������,s->s1����ÿ�γ������ 
    int exp;                                     //����ָ��
    float coef;                                  //ϵ�� 
    l=(List *)malloc(sizeof(List)); 			 //���������
    l->coef=0;
    l->next=l;             					     //ѭ������βָ��ͷ 
	s=(List *)malloc(sizeof(List)); 	         //�м�������s->s1
	s1=(List *)malloc(sizeof(List)); 
	s->next=s1;
	s1->next=s;  
	m=l;            					         
	p=L1->next;									 //ͷ�ڵ�δ����ʵ����������ݣ�����
	q=L2->next; 
    while(p->exp>=q->exp)           						 //L1������L2�������
    { 
        n=(List *)malloc(sizeof(List)); 	 //�����½ڵ�n
        exp=p->exp-q->exp;     				 //ָ����� 
        coef=p->coef/q->coef;    			 //ϵ����� 
        n->coef=coef;        				 //�½ڵ�ϵ����ֵ 
        n->exp=exp;           				 //�½ڵ�ָ����ֵ 
        m->next=n;           				 //����½ڵ� 
        m=m->next;         					 //����ָ��m�������´�����½ڵ�
		m->next=l; 
        s1->coef=coef;        				 //�½ڵ�ϵ����ֵ 
        s1->exp=exp;           				 //�½ڵ�ָ����ֵ 
        temp=Mult(s,L2);
        L1=Minus(L1,temp);
        p=L1->next;
		free(temp);                   
    }
    fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","a");
	fprintf(fp,"��ʽΪ:");
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
    fprintf(fp,"����Ϊ"); 
    while(p!=L1)
	{
		fprintf(fp,"%lfx^%d",p->coef,p->exp);
		if(p->next->coef>0)
		fprintf(fp,"+");
		p=p->next;
	}
	fclose(fp);
}
void Menu1()                                        //�˵�-��Ļ 
{
	List *L1,*L2;
	int flag,k;
	double x;
	printf("1.�����������ʽ���������������\n");
	printf("2.����ʽ�ӷ�\n");
	printf("3.����ʽ����\n");
	printf("4.����ʽ�˷�\n");
	printf("5.����ʽ����\n");
	printf("6.����ʽk�׵�����\n");
	printf("7.����ʽx=x0����ֵ\n");
	printf("ѡ����"); 
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
			printf("�������󵼽���k��");
			scanf("%d",&k);
			L1=Dif(L1,k);
			Print(L1);
			break;
		case 7:
			L1=Creat();
			L1=Sort(L1);
			printf("������x0��ֵ:");
			scanf("%lf",&x);
			x=Value(L1,x);
			printf("\n");
			printf("����ʽ��ֵΪ%lf",x);
			break;
		default:
		    exit(0);			
	}
}
void Menu2()										//�˵�-�ļ� 
{
	List *L1,*L2;
	char s[maxlength];
	int flag,k;
	double x;
	FILE* fp;
	printf("1.�����������ʽ���������������\n");
	printf("2.����ʽ�ӷ�\n");
	printf("3.����ʽ����\n");
	printf("4.����ʽ�˷�\n");
	printf("5.����ʽ����\n");
	printf("6.����ʽk�׵�����\n");
	printf("7.����ʽx=x0����ֵ\n");
	printf("ѡ����"); 
	scanf("%d",&flag);
	switch(flag)
	{
		case 1:
			fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1);
			fclose(fp);
			fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","a");
			Write(L1,fp);
			fclose(fp);
			break;
		case 2:
			fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1); 
			fgets(s,maxlength,fp);
			L2=Read(s);
			L2=Sort(L2);
			fclose(fp);
			fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","a");
			L1=Add(L1,L2);
			Write(L1,fp);
			fclose(fp);
			break;
		case 3:
			fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1); 
			fgets(s,maxlength,fp);
			L2=Read(s);
			L2=Sort(L2);
			fclose(fp);
			fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","a");
			L1=Minus(L1,L2);
			Write(L1,fp);
			fclose(fp);
			break;
		case 4:
		    fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1); 
			fgets(s,maxlength,fp);
			L2=Read(s);
			L2=Sort(L2);
			fclose(fp);
			fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","a");
			L1=Mult(L1,L2);
			Write(L1,fp);
			fclose(fp);
			break;
		case 5:
		   	fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","r");
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
			fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1); 
			fgets(s,maxlength,fp);
			fclose(fp);
			sscanf(s,"%d",&k);
			L1=Dif(L1,k);
			fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","a");
			Write(L1,fp);
			fclose(fp);
			break;
		case 7:
			fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","r");
			fgets(s,maxlength,fp);
			L1=Read(s);
			L1=Sort(L1); 
			fgets(s,maxlength,fp);
			sscanf(s,"%lf",&x);
			x=Value(L1,x);
			fclose(fp);
			fp=fopen("C:\\Users\\dell\\Desktop\\����ʽ.txt","a");
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
	printf("1.��Ļ�������	2.�ļ��������"); 
	scanf("%d",&flag);
	if(flag==1)
	Menu1();
	if(flag==2)
	Menu2();
}













