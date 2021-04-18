#include<stdio.h>
#include<stdlib.h>
#define maxlength 100
typedef struct STACK                //定义字符栈的结构体变量 （用来转化中缀表达式） 
{
	char symbol[maxlength];
	int top;	
}Stack;
typedef struct stack                //定义整型栈的结构体变量 （用来计算后缀表达式） 
{
	int symbol[maxlength];
	int top;	
}stack;
void Add(char x,Stack* p)           //新元素入栈  (字符栈） 
{
	p->top++;
	p->symbol[p->top]=x;
};
void add(char x,stack* p)           //新元素入栈 （整型栈） 
{
	p->top++;
	p->symbol[p->top]=x;
};
void Delete(Stack* p)               //栈顶元素出栈 (字符栈）
{
	p->symbol[p->top]=0;
	p->top--;
}
void deletes(stack* p)               //栈顶元素出栈 (整型栈）
{
	p->symbol[p->top]=0;
	p->top--;
}

void PrintStack(Stack* s)           //从栈底开始打印栈中元素 (字符栈） 
{
	for(int i=1;i<=s->top;i++)
	{
		printf("%c",s->symbol[i]);
	}
	printf("\n");
}
void Printstack(stack* s)           //从栈底开始打印栈中元素（整型栈） 
{
	for(int i=1;i<=s->top;i++)
	{
		printf("%d ",s->symbol[i]);
	}
	printf("\n");
}
void Print(Stack* s1,Stack* s2)    //打印两个栈的状态 
{
	printf("s1:");
	PrintStack(s1);
	printf("s2:");
	PrintStack(s2);
}
int Compare(char i,Stack* p)        //比较栈顶元素与读入字符的优先级，返回0或1用来判断接下来执行的操作 
                                    //1重复弹栈直到栈顶元素优先级低于读入字符或栈空，0直接入栈 
{
	if((p->top==0)||(p->symbol[p->top]=='(')) //栈空或栈顶为左括号，直接入栈 
	return 0;
	if(((i=='+')||(i=='-'))  //读入字符+，-，栈顶也为+，-，返回1 
	  &&((p->symbol[p->top]=='+')||(p->symbol[p->top]=='-')))
	return 1;
	if(((i=='*')||(i=='/'))  //读入字符*，/，栈顶为+，-，返回0
	  &&((p->symbol[p->top]=='+')||(p->symbol[p->top]=='-')))
	return 0;  
	if(((i=='*')||(i=='/'))  //读入字符*，/，栈顶也为*，/，返回1 
	  &&((p->symbol[p->top]=='*')||(p->symbol[p->top]=='/')))
    return 1;  
	if(((i=='+')||(i=='-'))  //读入字符+，-，栈顶为*，/，返回1 
	  &&((p->symbol[p->top]=='*')||(p->symbol[p->top]=='/')))  
	return 1;
	if(i=='(')               //读入字符为左括号，直接入栈 ，返回0 
	return 0;
}
Stack* Transform(Stack* s1,Stack* s2,char str[])          /*求后缀表达式算法*/ 
{
	for(int i=0;str[i]!='\0';i++)
		{
			if(str[i]=='#')                         //读入起始结束符跳过 
			{
			}else
			if(str[i]>='0'&&str[i]<='9')            //读入字符为数字直接入栈s1 
			{
			    Add(str[i],s1);
 				Print(s1,s2);
			}
			else if(str[i]!=')')                    //读入字符为非右括号的运算符 
			{
				if(str[i]!='(')
				Add(' ',s1);                       //检测到运算符时令空格入栈s1，分隔数字与运算符 
				while(Compare(str[i],s2))          //重复弹出s2栈顶元素压入s1，直到Compare函数返回值为0,读入字符入栈 
				{
					Add(s2->symbol[s2->top],s1);  
					Delete(s2);
			 		Print(s1,s2);
				}
				Add(str[i],s2);
				Print(s1,s2);
			}
		else                                       //运算符为右括号时的处理方法:重复弹出s2栈顶元素压入s1直到遇到左括号 
		{
			Add(' ',s1);                          //检测到运算符时令空格入栈s1，分隔数字与运算符
			while(s2->symbol[s2->top]!='(')
			{
				Add(s2->symbol[s2->top],s1);
				Delete(s2);
				Print(s1,s2);
			}
			Delete(s2);                         //弹出s2中的左括号 
			Print(s1,s2);
		} 
    	}
		for(int j=s2->top;j>=1;j--)               //将s2中剩余元素弹出，压入s1 
		{
			Add(s2->symbol[j],s1);
			Delete(s2); 
			Print(s1,s2);
		}
		printf("后缀表达式为：");                //打印后缀表达式 
		PrintStack(s1);
		return s1;
}
void Calculate(Stack* s1)                                 /*由后缀表达式求值算法*/
{
			stack s; s.top=0;                                   //运算使用的栈s
		char STR[maxlength];  				                    //临时字符串数组STR，保存中间字符转换为整型变量 
		for(int i=1;i<=s1->top;i++)
		{
			if(s1->symbol[i]==' ')
			{                                                   //读入字符为空格时可直接跳过，无影响 
			}
			else if(s1->symbol[i]>='0'&&s1->symbol[i]<='9')       //读入字符为数字,转化为整数后入栈s1 
			{
				for(int k=0;k<=maxlength;k++)                   //初始化字符串STR 
				STR[k]='\0';
				for(int j=0;s1->symbol[i]!=' ';j++)              //读入到连续的数字字符时，存储到临时字符串数组 
				{                                               //转为后缀表达式时，数字与符号间必有空格符分隔，故可作此判断 
					STR[j]=s1->symbol[i];                           
					i++;
				}
				add(atoi(STR),&s);                              //使用atoi函数将s1栈中后缀表达式里的数字字符转化为整型数入栈
				printf("s:");
			    Printstack(&s);
				printf("\n");	                            
			}else
			{
				switch(s1->symbol[i])                            //读入运算符时，弹出s栈顶两个元素，运算后再压入栈s 
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
		printf("最后结果为：");
		Printstack(&s); 
}
int main()
{
		FILE* fp=fopen("C:\\Users\\dell\\Desktop\\中缀表达式.txt","r");
		char str[maxlength];                        //字符串str储存文件读入的表达式 
		fgets(str,maxlength,fp);
		Stack s1;  s1.top=0;        				//s1储存后缀表达式 
		Stack s2;  s2.top=0;        				//s2中间存储 	                                            
		Transform(&s1,&s2,str);                     //表达式转换
		Calculate(&s1);		                        //求值 
}










