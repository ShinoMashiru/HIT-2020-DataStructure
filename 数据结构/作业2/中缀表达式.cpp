#include<stdio.h>
#include<stdlib.h>
#define maxlength 100
typedef struct STACK                //�����ַ�ջ�Ľṹ����� ������ת����׺���ʽ�� 
{
	char symbol[maxlength];
	int top;	
}Stack;
typedef struct stack                //��������ջ�Ľṹ����� �����������׺���ʽ�� 
{
	int symbol[maxlength];
	int top;	
}stack;
void Add(char x,Stack* p)           //��Ԫ����ջ  (�ַ�ջ�� 
{
	p->top++;
	p->symbol[p->top]=x;
};
void add(char x,stack* p)           //��Ԫ����ջ ������ջ�� 
{
	p->top++;
	p->symbol[p->top]=x;
};
void Delete(Stack* p)               //ջ��Ԫ�س�ջ (�ַ�ջ��
{
	p->symbol[p->top]=0;
	p->top--;
}
void deletes(stack* p)               //ջ��Ԫ�س�ջ (����ջ��
{
	p->symbol[p->top]=0;
	p->top--;
}

void PrintStack(Stack* s)           //��ջ�׿�ʼ��ӡջ��Ԫ�� (�ַ�ջ�� 
{
	for(int i=1;i<=s->top;i++)
	{
		printf("%c",s->symbol[i]);
	}
	printf("\n");
}
void Printstack(stack* s)           //��ջ�׿�ʼ��ӡջ��Ԫ�أ�����ջ�� 
{
	for(int i=1;i<=s->top;i++)
	{
		printf("%d ",s->symbol[i]);
	}
	printf("\n");
}
void Print(Stack* s1,Stack* s2)    //��ӡ����ջ��״̬ 
{
	printf("s1:");
	PrintStack(s1);
	printf("s2:");
	PrintStack(s2);
}
int Compare(char i,Stack* p)        //�Ƚ�ջ��Ԫ��������ַ������ȼ�������0��1�����жϽ�����ִ�еĲ��� 
                                    //1�ظ���ջֱ��ջ��Ԫ�����ȼ����ڶ����ַ���ջ�գ�0ֱ����ջ 
{
	if((p->top==0)||(p->symbol[p->top]=='(')) //ջ�ջ�ջ��Ϊ�����ţ�ֱ����ջ 
	return 0;
	if(((i=='+')||(i=='-'))  //�����ַ�+��-��ջ��ҲΪ+��-������1 
	  &&((p->symbol[p->top]=='+')||(p->symbol[p->top]=='-')))
	return 1;
	if(((i=='*')||(i=='/'))  //�����ַ�*��/��ջ��Ϊ+��-������0
	  &&((p->symbol[p->top]=='+')||(p->symbol[p->top]=='-')))
	return 0;  
	if(((i=='*')||(i=='/'))  //�����ַ�*��/��ջ��ҲΪ*��/������1 
	  &&((p->symbol[p->top]=='*')||(p->symbol[p->top]=='/')))
    return 1;  
	if(((i=='+')||(i=='-'))  //�����ַ�+��-��ջ��Ϊ*��/������1 
	  &&((p->symbol[p->top]=='*')||(p->symbol[p->top]=='/')))  
	return 1;
	if(i=='(')               //�����ַ�Ϊ�����ţ�ֱ����ջ ������0 
	return 0;
}
Stack* Transform(Stack* s1,Stack* s2,char str[])          /*���׺���ʽ�㷨*/ 
{
	for(int i=0;str[i]!='\0';i++)
		{
			if(str[i]=='#')                         //������ʼ���������� 
			{
			}else
			if(str[i]>='0'&&str[i]<='9')            //�����ַ�Ϊ����ֱ����ջs1 
			{
			    Add(str[i],s1);
 				Print(s1,s2);
			}
			else if(str[i]!=')')                    //�����ַ�Ϊ�������ŵ������ 
			{
				if(str[i]!='(')
				Add(' ',s1);                       //��⵽�����ʱ��ո���ջs1���ָ������������ 
				while(Compare(str[i],s2))          //�ظ�����s2ջ��Ԫ��ѹ��s1��ֱ��Compare��������ֵΪ0,�����ַ���ջ 
				{
					Add(s2->symbol[s2->top],s1);  
					Delete(s2);
			 		Print(s1,s2);
				}
				Add(str[i],s2);
				Print(s1,s2);
			}
		else                                       //�����Ϊ������ʱ�Ĵ�����:�ظ�����s2ջ��Ԫ��ѹ��s1ֱ������������ 
		{
			Add(' ',s1);                          //��⵽�����ʱ��ո���ջs1���ָ������������
			while(s2->symbol[s2->top]!='(')
			{
				Add(s2->symbol[s2->top],s1);
				Delete(s2);
				Print(s1,s2);
			}
			Delete(s2);                         //����s2�е������� 
			Print(s1,s2);
		} 
    	}
		for(int j=s2->top;j>=1;j--)               //��s2��ʣ��Ԫ�ص�����ѹ��s1 
		{
			Add(s2->symbol[j],s1);
			Delete(s2); 
			Print(s1,s2);
		}
		printf("��׺���ʽΪ��");                //��ӡ��׺���ʽ 
		PrintStack(s1);
		return s1;
}
void Calculate(Stack* s1)                                 /*�ɺ�׺���ʽ��ֵ�㷨*/
{
			stack s; s.top=0;                                   //����ʹ�õ�ջs
		char STR[maxlength];  				                    //��ʱ�ַ�������STR�������м��ַ�ת��Ϊ���ͱ��� 
		for(int i=1;i<=s1->top;i++)
		{
			if(s1->symbol[i]==' ')
			{                                                   //�����ַ�Ϊ�ո�ʱ��ֱ����������Ӱ�� 
			}
			else if(s1->symbol[i]>='0'&&s1->symbol[i]<='9')       //�����ַ�Ϊ����,ת��Ϊ��������ջs1 
			{
				for(int k=0;k<=maxlength;k++)                   //��ʼ���ַ���STR 
				STR[k]='\0';
				for(int j=0;s1->symbol[i]!=' ';j++)              //���뵽�����������ַ�ʱ���洢����ʱ�ַ������� 
				{                                               //תΪ��׺���ʽʱ����������ż���пո���ָ����ʿ������ж� 
					STR[j]=s1->symbol[i];                           
					i++;
				}
				add(atoi(STR),&s);                              //ʹ��atoi������s1ջ�к�׺���ʽ��������ַ�ת��Ϊ��������ջ
				printf("s:");
			    Printstack(&s);
				printf("\n");	                            
			}else
			{
				switch(s1->symbol[i])                            //���������ʱ������sջ������Ԫ�أ��������ѹ��ջs 
				{
				case'+':
					s.symbol[s.top-1]=s.symbol[s.top-1]+s.symbol[s.top];
					deletes(&s);
					break;
				case'-':
					s.symbol[s.top-1]=s.symbol[s.top-1]-s.symbol[s.top];
					deletes(&s);
					break;
				case'*':
					s.symbol[s.top-1]=s.symbol[s.top-1]*s.symbol[s.top];
					deletes(&s);
					break;
				case'/':
					s.symbol[s.top-1]=s.symbol[s.top-1]/s.symbol[s.top];
					deletes(&s);	
					break;
				}
				printf("s:");
			    Printstack(&s);
				printf("\n");		
			}	
		} 
		printf("�����Ϊ��");
		Printstack(&s); 
}
int main()
{
		FILE* fp=fopen("C:\\Users\\dell\\Desktop\\��׺���ʽ.txt","r");
		char str[maxlength];                        //�ַ���str�����ļ�����ı��ʽ 
		fgets(str,maxlength,fp);
		Stack s1;  s1.top=0;        				//s1�����׺���ʽ 
		Stack s2;  s2.top=0;        				//s2�м�洢 	                                            
		Transform(&s1,&s2,str);                     //���ʽת��
		Calculate(&s1);		                        //��ֵ 
}










