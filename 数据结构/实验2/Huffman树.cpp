#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct node 
{
	float weight;						//权重
 	int lchild;							//左儿子
 	int rchild;							//右儿子
 	int parent;							//父亲  
}node;     								//静态三叉链表 
void Min(node T[],int k,int* s1,int* s2)     //选出T数组的前k个节点中,两个权重最小的节点,下标返回s1,s2 
{
	int min=1000000,temp=0;                  //min初始值选择一个大于所有权值的大数,之后比较时初始化不会出现错误  temp为临时变量 
  	for(int i=0;i<=k;i++)					
	{
  	   if(T[i].parent==-1)					 //若节点无父节点,则可以被选择,否则不进入选择判断 
		 {
    	    if(min>T[i].weight)              //比较找出权值最小的节点 
			{
     		 	min=T[i].weight;
    		    temp=i;
            }
   	     }
    }
 	*s1=temp;                                //变量s1返回最小节点的下表 
 	min=100000;								 //重新初始化变量,进行下一轮比较 
 	temp=0;
  	for(int j=0;j<=k;j++)                    
	{
   	   if((T[j].parent==-1)&&(j!=*s1))		 //判断时排除s1,即得到剩下权值最小节点的下标 
	   {
   	      if(min>T[j].weight)
		  {
     		  min=T[j].weight;
      		  temp=j;
    	  }
  	   }
    }
  	*s2=temp;  								 //返回s2的下标,s1,s2即是权值最小两个节点的下标 
}
void CreatTree(node T[],float frequency[],int n) //构造Huffman树,T为Huffman树数组,frequency为频率数组,n为叶节点数 
{ 
 	if(n<=1)
  	    return ;
  	int i;
 	for(i=0;i<n;i++)					  	     //初始化Huffman树的n个叶节点,赋予权值 
	{
  	    T[i].weight=frequency[i];
        T[i].lchild=-1;
 	    T[i].rchild=-1;
  	    T[i].parent=-1;
 	}
	for(;i<n*2-1;i++)						   	 //初始化Huffman树的非叶节点(非叶节点n-1个，节点共2*n-1个) 
	{ 
  	   T[i].weight=0;
 	   T[i].lchild=-1;
  	   T[i].rchild=-1;
 	   T[i].parent=-1;
 	} 
 	for(i=n;i<n*2-1;i++)						 
	{
 	   int s1=0,s2=0;							 //s1,s2指向权重最小两个叶节点下标 
 	   Min(T,i-1,&s1,&s2);			 	         //选出权重最小的两个叶节点 
 	   T[s1].parent=i;
       T[s2].parent=i;							 //T[i]成为新的"叶节点" 
       T[i].lchild=s1;								
  	   T[i].rchild=s2;  
  	   T[i].weight=T[s1].weight+T[s2].weight;
 	}
}
void Code(node T[],char* HT[],int n)			     	//对每个叶节点进行编码 
{
  	char code[n];								//临时保存每个节点的哈夫曼编码 
  	code[n-1]='\0';                             //code以'\0'结尾，字符串形式调用 
  	int leaf,current,father;					//从叶结点向根寻路，故leaf从数组最后向前递减 
  	for(int i=0;i<2*n-1;i++) 						//current为当前节点，father为父节点 
	{
  	   leaf=n-1;								
   	   current=i;
   	   father=T[i].parent;							
   	   while(father!=-1)						//循环直到父节点为根 
	   {
   	 	 if(T[father].lchild==current)			//当前节点为左子树，当前位编码0 
		 {
     		 code[--leaf]='0';
    	 }else                                  //当前节点为右子树，当前位编码1 
		 {
     	     code[--leaf]='1';
    	 }
   	     current=father;                        //继续向上寻路 
   	     father=T[father].parent;				
   	   } 
   	   HT[i]=(char*)malloc((n-leaf)*sizeof(char)); //为节点i的编码分配存储空间储存Huffman编码 
   	   strcpy(HT[i],&code[leaf]);                  //将code中的01编码字符串（start开始到'\0'结束）复制到HT[i]节点 
  	} 
}
void Compress(char* HT[],char character[])				//将英文文件压缩为哈夫曼编码文件,HT为Huffman码数组，character为字符种类数组
{
	 FILE* fp=fopen("C:\\Users\\dell\\Desktop\\英文文本.txt","r");//打开英文文件 
	 FILE* np=fopen("C:\\Users\\dell\\Desktop\\编码文本.txt","a"); //打开要压缩的哈夫曼编码文件 
	 char a[100000];
	 fgets(a,100001,fp);//读出英文文件的内容 
	 fclose(fp) ;//关闭文件 
	 int len1=strlen(a);//
 	 int len2=strlen(character);
	 for(int i=0;i<len1;i++)
	 {
 	    for(int j=0;j<len2;j++)
		{
   			if(character[j]==a[i])
			{
    			fputs(HT[j],np);                //将每个字符的哈夫曼编码输入到哈夫曼编码文件中 
        	}
 	    }
	 }
 	fclose(np) ; //关闭文件 
}
void Decode(node T[],char character[],char a[],char result[],int n)//解码 T为Huffman树,a为Huffman编码字符串,n为叶节点个数, 
{																   //result为字符数组,character为字符种类数组 
	 int p=2*n-2;//根节点 
	 int i=0;//指示串的第i个字符 
	 int j=0;//解码出的第j个字符 
	 int len = strlen(a); 
	 while(i<len)
	 {
 	    if(a[i]=='0')                   //解码
		{
  	         p=T[p].lchild;
 	    }
  	    if(a[i]=='1')
		{
 	         p=T[p].rchild;
 	    }  
	  	if(p<n)
	  	{									
 		 	result[j]=character[p];		   //此时为叶节点
 	  	 	j++;
 		    p=2*n-2;//重新指向根节点 
 	  	}
	   i++;
     }
 	result[j]='\0';
}
void Defile(node T[],char character[],int n)			//将从文件读入的哈夫曼编码解码为英文文件
{											 
	 FILE* np=fopen("C:\\Users\\dell\\Desktop\\解压文本.txt","r");//打开编码文件 
	 FILE* mp=fopen("C:\\Users\\dell\\Desktop\\解码文本.txt","a");//打开要写入解码结果的文件  
	 char a[100000];
	 fgets(a,100001,np);
	 fclose(np);
	 char result[100000];
	 Decode(T,character,a,result,n);
	 fputs(result,mp);
	 //cout<<"哈夫曼编码文件中的内容为:"<<endl;
     //cout<<a<<endl;
	 //cout<<"解压为英文文件后的内容为："<<endl;
	 //cout<<c<<endl;
	 fclose(mp);
}
int Press()												//将编码文件压缩
{
	FILE* fp=fopen("C:\\Users\\dell\\Desktop\\编码文本.txt","r");//打开编码文件 
	FILE* np=fopen("C:\\Users\\dell\\Desktop\\压缩文本.txt","a"); //打开要压缩的哈夫曼编码文件 
	char a[10000];char b[10000];
	fgets(a,10001,fp);//读出编码文件的内容 
	int i=0;int sum=0;int length=strlen(a);
	char zero='0';
	for(i=0;i<length/6;i++)
	{
		sum=0;
		for(int j=0;j<6;j++)
		{
			sum=sum+((int)a[6*i+j]-(int)zero)*pow(2,6-j-1);
		}
		b[i]=(char)(sum+32); 
	}
	if(6*i<length)
	{
		sum=0;
		for(int j=0;j<length%6;j++)
		{
			sum=sum+((int)a[6*i+j]-(int)zero)*pow(2,6-1-j);
		}
		b[i]=(char)(sum+32); 
		i++;
	}
	b[i]='\0';
	fputs(b,np);
	fclose(fp);
 	fclose(np) ; //关闭文件 
 	return length%6;
}
void Depress(int n)                                     //解压缩 
{
	FILE* fp=fopen("C:\\Users\\dell\\Desktop\\压缩文本.txt","r");//打开压缩文件 
	FILE* np=fopen("C:\\Users\\dell\\Desktop\\解压文本.txt","a"); //打开要解压缩的哈夫曼编码文件 
	char a[10000];char b[10000];char zero='0';
	fgets(a,10001,fp);//读入压缩文件的内容 
	int i=0;int result;int length=strlen(a);
	for(i=0;i<length;i++)
	{
		result=(int)a[i]-32;
		for(int j=0;j<6;j++)
		{
			b[6*i+6-1-j]=(char)(result%2+(int)zero);
			result=result/2;
		}
	}
	b[6*i-6+n]='\0';
	fputs(b,np);
	fclose(fp);
 	fclose(np) ; //关闭文件 
}
void Initi(node T[],char str_read[],int amount[],char character[],int* N,int* M,int character_amount[],float frequency[],char* HT[])
{
 	 FILE* fp;
	 fp=fopen("C:\\Users\\dell\\Desktop\\英文文本.txt","r");
 	 if(fp==NULL)							//判断是否成功打开文件 
	 {
 	     printf("error!");
	 }else
	 {
  		 fgets(str_read,100001,fp);		//从文件读入10000个字符 
	 }
 	 printf("从文件读入的字符总数为：%d",strlen(str_read));
	 int length_read=strlen(str_read);      //字符串str_read 的长度length_read 
	 for(int i=0;i<length_read;i++)
	 {
		int m=int(str_read[i]);             //m为当前字符的ASCII码
  		amount[m]++;						//当前字符对应数组m号元素，计数+1 
	 }
	 int character_count=0;					//记录字符种类数 
	 for(int i=0;i<length_read;i++)
	 {
 	     if(amount[i]!=0)
		  {
    	     character[character_count]=char(i);//将ASCII码转化为字符保存在字符数组中 
    	     character_count++;
   		  }
 	 }
 	 *N=character_count;*M=character_count*2-1;
	 printf("文件中的不同的字符个数为：%d",character_count);
	 character_count=0;
	 for(int i=0;i<length_read;i++)
	 {
	     if(amount[i]!=0)
		 {
   			 character_amount[character_count]=amount[i];
  	         character_count++;
         }
 	 }
	 character_amount[character_count]=0;	
	 character[character_count]='\0'; 
	 printf("\n字符\t\t频数\t\t权重\t\t"); 
	 for(int i=0;i<strlen(character);i++)
	 {
	     frequency[i]=(float(character_amount[i]))/length_read;
 	     printf("\n%c\t\t%d\t\t%f\t\t",character[i],character_amount[i],frequency[i]);
 	 }
	 frequency[strlen(character)]=0; 
	 fclose(fp) ;
	 CreatTree(T,frequency,*N);//构建哈夫曼树
	 Code(T,HT,*N);//对哈夫曼树进行编码 
	 printf("\n字符\t\tHuffman编码\t\t"); 
	 for(int i=0;i<*N;i++)
	 {
	 	printf("\n%c\t\t%s\t\t",character[i],HT[i]);//打印Huffman编码 
	 }
	 float sum=0;
	 for(int i=0;i<*N;i++)
	 {
	 	sum+=strlen(HT[i])*T[i].weight;//计算平均编码长度sum 
	 }
	 printf("\n压缩率为:%f",sum/(log(*N)/log(2)+1));
	 printf("\n压缩率为:%f",sum/7);
}
int Compare()                                           //比较解码前后文件是否相同 
{
	FILE* fp=fopen("C:\\Users\\dell\\Desktop\\英文文本.txt","r");//打开英文文件 
	FILE* np=fopen("C:\\Users\\dell\\Desktop\\解码文本.txt","r"); //打开解码后文件 
	char a[10000];
	char b[10000];
	fgets(a,10001,fp);
	fgets(b,10001,np); 
	if(strcmp(a,b)==0)
	return 1;
	else
	return 0;
}
void Menu(node T[],char character[],char* HT[],int N)
{
	 int n=0;
	 int k;
     printf("\n----------------------------------\n");
     printf("0.退出                              \n");
     printf("1.将英文文件进行压缩为哈夫曼编码文件\n");
	 printf("2.将哈夫曼编码文件解压为英文文件    \n");
	 printf("3.判断解码后的文件是否与原文件相同  \n");
 	 printf("------------------------------------\n");
	 scanf("%d",&n);
	 while(n!=0)
	 {
 	    switch(n)
		{
 	 	case 1:
   		   Compress(HT,character);//将英文文件压缩为哈夫曼编码文件 
  		   break;
  		case 2:
  		   k=Press();
  		   Depress(k);	
  	       Defile(T,character,N);//将从文件读入的哈夫曼编码解压为英文文件 
  		   break;
  		case 3:
  		   if(Compare())
  		   printf("\n压缩解码后文件与原文件相同！\n"); 
  		   else
  		   printf("\n压缩解码后文件与原文件不同！\n");
		   break;   
  		case 0:
 		   n=0;
  	 	   break;
  	    default:
  		   break;  
 		}
	 	printf("------------------------------------\n");
     	printf("0.退出                              \n");
     	printf("1.将英文文件进行压缩为哈夫曼编码文件\n");
	 	printf("2.将哈夫曼编码文件解压为英文文件    \n");
	 	printf("3.判断解码后的文件是否与原文件相同  \n");
 		printf("------------------------------------\n");
	 	scanf("%d",&n);
	 }
}
int main()
{
	 node T[1000];							//数组用来创建树 
 	 char str_read[10000];					//读取文件中的字符，储存到字符串数组str_read
	 int amount[1000]={0};                  //amount数组储存每种字符出现次数  
	 char character[1000];					//文本不同种类的字符 
	 int N,M; 							    //N为哈夫曼树叶节点个数，M为节点个数 N=character_count M=2*N-1
	 int character_amount[1000];			//字符出现的频数 
	 float frequency[1000];					//frequency数组储存字符频率
	 char* HT[1000];						//储存Huffman编码 
 	 Initi(T,str_read,amount,character,&N,&M,character_amount,frequency,HT);
 	 Menu(T,character,HT,N);
}
//printf("1");
