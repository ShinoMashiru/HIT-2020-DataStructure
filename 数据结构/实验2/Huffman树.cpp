#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct node 
{
	float weight;						//Ȩ��
 	int lchild;							//�����
 	int rchild;							//�Ҷ���
 	int parent;							//����  
}node;     								//��̬�������� 
void Min(node T[],int k,int* s1,int* s2)     //ѡ��T�����ǰk���ڵ���,����Ȩ����С�Ľڵ�,�±귵��s1,s2 
{
	int min=1000000,temp=0;                  //min��ʼֵѡ��һ����������Ȩֵ�Ĵ���,֮��Ƚ�ʱ��ʼ��������ִ���  tempΪ��ʱ���� 
  	for(int i=0;i<=k;i++)					
	{
  	   if(T[i].parent==-1)					 //���ڵ��޸��ڵ�,����Ա�ѡ��,���򲻽���ѡ���ж� 
		 {
    	    if(min>T[i].weight)              //�Ƚ��ҳ�Ȩֵ��С�Ľڵ� 
			{
     		 	min=T[i].weight;
    		    temp=i;
            }
   	     }
    }
 	*s1=temp;                                //����s1������С�ڵ���±� 
 	min=100000;								 //���³�ʼ������,������һ�ֱȽ� 
 	temp=0;
  	for(int j=0;j<=k;j++)                    
	{
   	   if((T[j].parent==-1)&&(j!=*s1))		 //�ж�ʱ�ų�s1,���õ�ʣ��Ȩֵ��С�ڵ���±� 
	   {
   	      if(min>T[j].weight)
		  {
     		  min=T[j].weight;
      		  temp=j;
    	  }
  	   }
    }
  	*s2=temp;  								 //����s2���±�,s1,s2����Ȩֵ��С�����ڵ���±� 
}
void CreatTree(node T[],float frequency[],int n) //����Huffman��,TΪHuffman������,frequencyΪƵ������,nΪҶ�ڵ��� 
{ 
 	if(n<=1)
  	    return ;
  	int i;
 	for(i=0;i<n;i++)					  	     //��ʼ��Huffman����n��Ҷ�ڵ�,����Ȩֵ 
	{
  	    T[i].weight=frequency[i];
        T[i].lchild=-1;
 	    T[i].rchild=-1;
  	    T[i].parent=-1;
 	}
	for(;i<n*2-1;i++)						   	 //��ʼ��Huffman���ķ�Ҷ�ڵ�(��Ҷ�ڵ�n-1�����ڵ㹲2*n-1��) 
	{ 
  	   T[i].weight=0;
 	   T[i].lchild=-1;
  	   T[i].rchild=-1;
 	   T[i].parent=-1;
 	} 
 	for(i=n;i<n*2-1;i++)						 
	{
 	   int s1=0,s2=0;							 //s1,s2ָ��Ȩ����С����Ҷ�ڵ��±� 
 	   Min(T,i-1,&s1,&s2);			 	         //ѡ��Ȩ����С������Ҷ�ڵ� 
 	   T[s1].parent=i;
       T[s2].parent=i;							 //T[i]��Ϊ�µ�"Ҷ�ڵ�" 
       T[i].lchild=s1;								
  	   T[i].rchild=s2;  
  	   T[i].weight=T[s1].weight+T[s2].weight;
 	}
}
void Code(node T[],char* HT[],int n)			     	//��ÿ��Ҷ�ڵ���б��� 
{
  	char code[n];								//��ʱ����ÿ���ڵ�Ĺ��������� 
  	code[n-1]='\0';                             //code��'\0'��β���ַ�����ʽ���� 
  	int leaf,current,father;					//��Ҷ������Ѱ·����leaf�����������ǰ�ݼ� 
  	for(int i=0;i<2*n-1;i++) 						//currentΪ��ǰ�ڵ㣬fatherΪ���ڵ� 
	{
  	   leaf=n-1;								
   	   current=i;
   	   father=T[i].parent;							
   	   while(father!=-1)						//ѭ��ֱ�����ڵ�Ϊ�� 
	   {
   	 	 if(T[father].lchild==current)			//��ǰ�ڵ�Ϊ����������ǰλ����0 
		 {
     		 code[--leaf]='0';
    	 }else                                  //��ǰ�ڵ�Ϊ����������ǰλ����1 
		 {
     	     code[--leaf]='1';
    	 }
   	     current=father;                        //��������Ѱ· 
   	     father=T[father].parent;				
   	   } 
   	   HT[i]=(char*)malloc((n-leaf)*sizeof(char)); //Ϊ�ڵ�i�ı������洢�ռ䴢��Huffman���� 
   	   strcpy(HT[i],&code[leaf]);                  //��code�е�01�����ַ�����start��ʼ��'\0'���������Ƶ�HT[i]�ڵ� 
  	} 
}
void Compress(char* HT[],char character[])				//��Ӣ���ļ�ѹ��Ϊ�����������ļ�,HTΪHuffman�����飬characterΪ�ַ���������
{
	 FILE* fp=fopen("C:\\Users\\dell\\Desktop\\Ӣ���ı�.txt","r");//��Ӣ���ļ� 
	 FILE* np=fopen("C:\\Users\\dell\\Desktop\\�����ı�.txt","a"); //��Ҫѹ���Ĺ����������ļ� 
	 char a[100000];
	 fgets(a,100001,fp);//����Ӣ���ļ������� 
	 fclose(fp) ;//�ر��ļ� 
	 int len1=strlen(a);//
 	 int len2=strlen(character);
	 for(int i=0;i<len1;i++)
	 {
 	    for(int j=0;j<len2;j++)
		{
   			if(character[j]==a[i])
			{
    			fputs(HT[j],np);                //��ÿ���ַ��Ĺ������������뵽�����������ļ��� 
        	}
 	    }
	 }
 	fclose(np) ; //�ر��ļ� 
}
void Decode(node T[],char character[],char a[],char result[],int n)//���� TΪHuffman��,aΪHuffman�����ַ���,nΪҶ�ڵ����, 
{																   //resultΪ�ַ�����,characterΪ�ַ��������� 
	 int p=2*n-2;//���ڵ� 
	 int i=0;//ָʾ���ĵ�i���ַ� 
	 int j=0;//������ĵ�j���ַ� 
	 int len = strlen(a); 
	 while(i<len)
	 {
 	    if(a[i]=='0')                   //����
		{
  	         p=T[p].lchild;
 	    }
  	    if(a[i]=='1')
		{
 	         p=T[p].rchild;
 	    }  
	  	if(p<n)
	  	{									
 		 	result[j]=character[p];		   //��ʱΪҶ�ڵ�
 	  	 	j++;
 		    p=2*n-2;//����ָ����ڵ� 
 	  	}
	   i++;
     }
 	result[j]='\0';
}
void Defile(node T[],char character[],int n)			//�����ļ�����Ĺ������������ΪӢ���ļ�
{											 
	 FILE* np=fopen("C:\\Users\\dell\\Desktop\\��ѹ�ı�.txt","r");//�򿪱����ļ� 
	 FILE* mp=fopen("C:\\Users\\dell\\Desktop\\�����ı�.txt","a");//��Ҫд����������ļ�  
	 char a[100000];
	 fgets(a,100001,np);
	 fclose(np);
	 char result[100000];
	 Decode(T,character,a,result,n);
	 fputs(result,mp);
	 //cout<<"�����������ļ��е�����Ϊ:"<<endl;
     //cout<<a<<endl;
	 //cout<<"��ѹΪӢ���ļ��������Ϊ��"<<endl;
	 //cout<<c<<endl;
	 fclose(mp);
}
int Press()												//�������ļ�ѹ��
{
	FILE* fp=fopen("C:\\Users\\dell\\Desktop\\�����ı�.txt","r");//�򿪱����ļ� 
	FILE* np=fopen("C:\\Users\\dell\\Desktop\\ѹ���ı�.txt","a"); //��Ҫѹ���Ĺ����������ļ� 
	char a[10000];char b[10000];
	fgets(a,10001,fp);//���������ļ������� 
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
 	fclose(np) ; //�ر��ļ� 
 	return length%6;
}
void Depress(int n)                                     //��ѹ�� 
{
	FILE* fp=fopen("C:\\Users\\dell\\Desktop\\ѹ���ı�.txt","r");//��ѹ���ļ� 
	FILE* np=fopen("C:\\Users\\dell\\Desktop\\��ѹ�ı�.txt","a"); //��Ҫ��ѹ���Ĺ����������ļ� 
	char a[10000];char b[10000];char zero='0';
	fgets(a,10001,fp);//����ѹ���ļ������� 
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
 	fclose(np) ; //�ر��ļ� 
}
void Initi(node T[],char str_read[],int amount[],char character[],int* N,int* M,int character_amount[],float frequency[],char* HT[])
{
 	 FILE* fp;
	 fp=fopen("C:\\Users\\dell\\Desktop\\Ӣ���ı�.txt","r");
 	 if(fp==NULL)							//�ж��Ƿ�ɹ����ļ� 
	 {
 	     printf("error!");
	 }else
	 {
  		 fgets(str_read,100001,fp);		//���ļ�����10000���ַ� 
	 }
 	 printf("���ļ�������ַ�����Ϊ��%d",strlen(str_read));
	 int length_read=strlen(str_read);      //�ַ���str_read �ĳ���length_read 
	 for(int i=0;i<length_read;i++)
	 {
		int m=int(str_read[i]);             //mΪ��ǰ�ַ���ASCII��
  		amount[m]++;						//��ǰ�ַ���Ӧ����m��Ԫ�أ�����+1 
	 }
	 int character_count=0;					//��¼�ַ������� 
	 for(int i=0;i<length_read;i++)
	 {
 	     if(amount[i]!=0)
		  {
    	     character[character_count]=char(i);//��ASCII��ת��Ϊ�ַ��������ַ������� 
    	     character_count++;
   		  }
 	 }
 	 *N=character_count;*M=character_count*2-1;
	 printf("�ļ��еĲ�ͬ���ַ�����Ϊ��%d",character_count);
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
	 printf("\n�ַ�\t\tƵ��\t\tȨ��\t\t"); 
	 for(int i=0;i<strlen(character);i++)
	 {
	     frequency[i]=(float(character_amount[i]))/length_read;
 	     printf("\n%c\t\t%d\t\t%f\t\t",character[i],character_amount[i],frequency[i]);
 	 }
	 frequency[strlen(character)]=0; 
	 fclose(fp) ;
	 CreatTree(T,frequency,*N);//������������
	 Code(T,HT,*N);//�Թ����������б��� 
	 printf("\n�ַ�\t\tHuffman����\t\t"); 
	 for(int i=0;i<*N;i++)
	 {
	 	printf("\n%c\t\t%s\t\t",character[i],HT[i]);//��ӡHuffman���� 
	 }
	 float sum=0;
	 for(int i=0;i<*N;i++)
	 {
	 	sum+=strlen(HT[i])*T[i].weight;//����ƽ�����볤��sum 
	 }
	 printf("\nѹ����Ϊ:%f",sum/(log(*N)/log(2)+1));
	 printf("\nѹ����Ϊ:%f",sum/7);
}
int Compare()                                           //�ȽϽ���ǰ���ļ��Ƿ���ͬ 
{
	FILE* fp=fopen("C:\\Users\\dell\\Desktop\\Ӣ���ı�.txt","r");//��Ӣ���ļ� 
	FILE* np=fopen("C:\\Users\\dell\\Desktop\\�����ı�.txt","r"); //�򿪽�����ļ� 
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
     printf("0.�˳�                              \n");
     printf("1.��Ӣ���ļ�����ѹ��Ϊ�����������ļ�\n");
	 printf("2.�������������ļ���ѹΪӢ���ļ�    \n");
	 printf("3.�жϽ������ļ��Ƿ���ԭ�ļ���ͬ  \n");
 	 printf("------------------------------------\n");
	 scanf("%d",&n);
	 while(n!=0)
	 {
 	    switch(n)
		{
 	 	case 1:
   		   Compress(HT,character);//��Ӣ���ļ�ѹ��Ϊ�����������ļ� 
  		   break;
  		case 2:
  		   k=Press();
  		   Depress(k);	
  	       Defile(T,character,N);//�����ļ�����Ĺ����������ѹΪӢ���ļ� 
  		   break;
  		case 3:
  		   if(Compare())
  		   printf("\nѹ��������ļ���ԭ�ļ���ͬ��\n"); 
  		   else
  		   printf("\nѹ��������ļ���ԭ�ļ���ͬ��\n");
		   break;   
  		case 0:
 		   n=0;
  	 	   break;
  	    default:
  		   break;  
 		}
	 	printf("------------------------------------\n");
     	printf("0.�˳�                              \n");
     	printf("1.��Ӣ���ļ�����ѹ��Ϊ�����������ļ�\n");
	 	printf("2.�������������ļ���ѹΪӢ���ļ�    \n");
	 	printf("3.�жϽ������ļ��Ƿ���ԭ�ļ���ͬ  \n");
 		printf("------------------------------------\n");
	 	scanf("%d",&n);
	 }
}
int main()
{
	 node T[1000];							//�������������� 
 	 char str_read[10000];					//��ȡ�ļ��е��ַ������浽�ַ�������str_read
	 int amount[1000]={0};                  //amount���鴢��ÿ���ַ����ִ���  
	 char character[1000];					//�ı���ͬ������ַ� 
	 int N,M; 							    //NΪ��������Ҷ�ڵ������MΪ�ڵ���� N=character_count M=2*N-1
	 int character_amount[1000];			//�ַ����ֵ�Ƶ�� 
	 float frequency[1000];					//frequency���鴢���ַ�Ƶ��
	 char* HT[1000];						//����Huffman���� 
 	 Initi(T,str_read,amount,character,&N,&M,character_amount,frequency,HT);
 	 Menu(T,character,HT,N);
}
//printf("1");
