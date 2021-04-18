#include<iostream>
#include<string.h>
#include<fstream>
#include<stack>
#include<queue>
#include<iomanip>
#include<stdlib.h>
#include<cstdio>
using namespace std;
const int MIN=99999;
#define max 200
int D[max];//��Ŵ�Դ�㵽������������·������ 
bool S[max];//�ж�ÿ�������Ƿ��Ѿ�������·�� 
int P[max];//��¼ÿ�����·����ĳ���ڵ��ǰһ���ڵ�ı�� 
int D2[max][max];//���������������֮������·������ 
int P2[max][max];//���������������֮������·����� 
struct qbase{	//���ȼ����У�����Ȩֵ��СԪ�� 
        int key,value;
        bool operator < (const qbase &other) const
        {
            return value>other.value;
        }
    };
typedef struct{ //�ڽӾ��󴢴�ͼ 
 int vertex[max];//�ڽӾ���Ķ�������
 int edge[max][max];//�ڽӾ���ı�ֵ 
 int n,e;//�ڽӾ���Ķ���ͱߵĸ��� 
}Matrix;
typedef struct Edgenode				//�߱�ڵ�
{								 
  int subscript;					//�����±�
  int cost;					 		//���������ڽӵıߵ�Ȩ��
  Edgenode *next;					//ָ����һ�߱�ڵ��ָ�� 
}Edgenode; 
typedef struct Vertex				//�����ڵ�
{									
   int subscript;					//�����±� 
   bool visit;						//��ǽڵ��Ƿ񱻷��ʹ� 
   Edgenode *firstedge;				//������ͷָ�� 
}Vertex;
typedef struct List					//ͼ���ڽӱ� 
{
    Vertex vlist[max];				//�������� 
    int n,e;						//��������ͱߵĸ��� 
}List;
void FileCreateList(List *G){		//���ļ������ڽӱ� 
      fstream in;
      in.open("C:\\Users\\dell\\Desktop\\ͼ.txt");
      int i,k,j;
      int weight;
      in>>G->n >>G->e ; 
      for(i=0;i<G->n;i++)
	  {
         G->vlist[i].subscript=i;
         G->vlist[i].firstedge=NULL;//��ʼ���ڽӱ� 
	  }
      for(k=0;k<G->e;k++)
	  {
         in>>i>>j>>weight;
         Edgenode* p=new Edgenode;
         p->subscript =j;p->cost =weight; 
	     p->next=G->vlist[i].firstedge;
         G->vlist[i].firstedge =p;
      }
      in.close();
}
void PrintMatrix(Matrix *t){//��ӡ�ڽӾ������Ϣ 
 for(int i=0;i<t->n ;i++)
 {
  	cout<<"\t"<<i; 
 }
 cout<<endl;
 for(int i=0;i<t->n ;i++)
 {
  	cout<<i<<"\t";
  	for(int j=0;j<t->n ;j++)
  	{	
   		if(t->edge[i][j]==99999)
   		{
    		cout<<"��\t";
   		}else
    	cout<<t->edge[i][j]<<"\t";
  	}
  cout<<endl;
 }
}
void File_Creat(Matrix *G){//���ļ���ʽ����ͼ�Ķ���ͱ�
 cout<<"���ļ���������ͼ���ڽӾ���Ϊ��"<<endl<<endl;
 int i,j,k,w;
 fstream in;
 in.open("C:\\Users\\dell\\Desktop\\ͼ.txt"); 
 in>>G->n>>G->e;//���붥������ͱߵĸ�����
 for(i=0;i<G->n;i++)
 {
  	G->vertex[i]=i;
 } 
 for(i=0;i<G->n ;i++)
  for(j=0;j<G->n ;j++)
    if(i!=j)
     G->edge[i][j]=MIN;//��ʼ���ڽӾ��� 
    else
     G->edge[i][j]=0;
 for(k=0;k<G->e;k++)
 {
  	in>>i>>j>>w;
  	G->edge[i][j]=w;//�����(i,j)��Ȩ��w 
 }
 in.close();
 PrintMatrix(G);
 cout<<endl<<endl;
}
int mincost(Matrix C){ //���㵱ǰ���·�����±�w 
 int tmp= MIN;
 int w=1;
 for(int i=1;i<C.n ;i++)
 {
  	if(S[i]!=true&&D[i]<tmp)
  	{
   		tmp=D[i];
   		w=i;
  	}
 }
 return w;
} 
void Dijkstra(Matrix C){//��Դ��0��ÿ����������·�� 
 for(int i=0;i<C.n ;i++)
 {
  	D[i]=C.edge[0][i];
 }
 for(int i=0;i<C.n;i++)
 {
  	P[i]=0;
  	S[i]=false;
 }
 S[0]=true;
 for(int i=1;i<C.n;i++)
 {
  	int w=mincost(C);
  	S[w]=true;
 	for(int v=1;v<C.n;v++)
 	{
   		if(S[v]!=true)
   		{
    		int sum=D[w]+C.edge[w][v];
    		if(sum<D[v])   
			{
				D[v]=sum;  P[v]=w;
			}
   		}
 	}  
 } 
}
void PrintDijkstra(Matrix G){//���Դ��0��ÿ����������·�����Ⱥ����·��
 for(int i=1;i<G.n;i++)
 {
  	if(D[i]!=MIN)
	{
   		cout<<"0---"<<i<<"��̳���Ϊ    "<<D[i]<<endl; 
   		stack<int>s;
   		s.push(i);
   		int x=P[i];
   		while(x!=0)
   		{
    		s.push(x);
    		x=P[x];
   		} 
   		s.push(0);
   		cout<<"0---"<<i<<"·��Ϊ�� "; 
    	while(!s.empty() )
		{
      		cout<<s.top() <<"-";
     		s.pop() ;
    	}
   		cout<<endl;
 	}else
   		cout<<"0��"<<i<<"��·��"<<endl;
  
 }	
}
void HeapDijkstra(List L){//���ȼ������Ż������·�� 
 for(int i=0;i<L.n ;i++)
 {
  	D[i]=MIN;
 }
 for(int i=0;i<L.n;i++)
 {
  	P[i]=0;
  	S[i]=false;
 }
 D[0]=0;
 priority_queue<qbase>q;
 q.push((qbase){0,0});
 while(!q.empty())
 {
  	qbase h=q.top();q.pop();
    int h_k=h.key,h_v=h.value;
    if(S[h_k]) continue;
    S[h_k]=true;
  	for(Edgenode *p=L.vlist[h_k].firstedge;p!=NULL;p=p->next)
	{
   		if(S[p->subscript]!=true)
   		{
    		int sum=D[h_k]+p->cost;
    		if(sum<D[p->subscript])   
			{
				D[p->subscript]=sum; P[p->subscript]=h_k;
				q.push((qbase){p->subscript,D[p->subscript]});
			}
   		}	
 	}  
 }
}
void Floyd(Matrix G){ //Floyd�㷨 
 //��ʼ�� 
 for(int i=0;i<G.n;i++)
 {
  	for(int j=0;j<G.n ;j++)
  	{
   		D2[i][j]=G.edge[i][j];
   		if(D2[i][j]!=99999)
    	P2[i][j]=-1;
   		else
    	P2[i][j]=-2;
  	}
 } 
 for( int k=0;k<G.n;k++)
 {
  	for(int i=0;i<G.n;i++)
  	{
   		for(int j=0;j<G.n ;j++)
   		{
    		if(D2[i][k]+D2[k][j]<D2[i][j])
			{	
     			D2[i][j]=D2[i][k]+D2[k][j];//���¶���֮����̾��� 
     			P2[i][j]=k;//��¼���·�������Ķ��� 
   			}
  		}
 	} 
 } 
} 
void Floyd_Road(Matrix G,int e,int n){//������������������·�� 
// int n,e;
// cout<<"������������Ҫ�����������֮������·�����ȼ������·��"<<endl;
// cin>>e>>n;
 if(P2[e][n]==-2) 
  cout<<e<<"��"<<n<<"֮��û��·��"<<endl;
 else if(P2[e][n]==-1)
 {
  cout<<e<<"-"<<n<<" ";
 } 
 else
 {
  Floyd_Road(G,e,P2[e][n]);
  Floyd_Road(G,P2[e][n],n);
 }
}
void FloydPrint(Matrix G){//��ӡÿ��������֮�����̳��� 
 cout<<"ÿ������֮������·���������£�"<<endl; 
 for(int i=0;i<G.n;i++)
 {
  	cout<<"\t"<<i;
 }
 cout<<endl;
 for(int i=0;i<G.n;i++)
 {
   	cout<<i<<"\t";
  	for(int j=0;j<G.n ;j++)
  	{
   		if(D2[i][j]!=99999)
    	cout<<D2[i][j]<<"\t";
   		else 
    	cout<<"��"<<"\t";
   	}
  	cout<<endl;
 }
}
void FloydPrint1(Matrix G){//���ж���֮������·������̳���
 FloydPrint(G); 
 for(int i=0;i<G.n;i++)
 {
  	for(int j=0;j<G.n ;j++)
  	{
  		cout<<i<<"-"<<j<<":";
   		Floyd_Road(G,i,j);
   		cout<<endl;
   	}
  	
 }
} 
void Floyd_Printf(Matrix G){//��ӡ�������ڵ�����·�� 
 cout<<"��������Ҫ���ĳ��������֮������·��"<<endl;
 int e,n;
 cin>>e>>n;
 if(D2[e][n]!=99999)
 cout<<"����������֮������·��Ϊ"<<endl; 
 Floyd_Road( G, e, n);
 cout<<endl;
 if(D2[e][n]!=99999)
 cout<<"����������֮�����̾���Ϊ��"<<D2[e][n]<<endl;  
}
void FloydPrint2(Matrix G){//�ҵ�ͼ��ÿ������v��ĳ��ָ������c���·�� 
 cout<<"������ĳ��ָ���Ķ��㣨0-"<<G.n-1<<")"<<endl;
 int e; 
 cin>>e;
 cout<<"���ⶥ�㵽����"<<e<<"�����·��Ϊ��"<<endl;
 for(int j=0;j<G.n;j++)
 {
  if(D2[j][e]!=99999)
   cout<<j<<"-"<<e<<":   "<<D2[j][e]<<endl; 
  else
   cout<<j<<"-"<<e<<":   "<<"��"<<endl; 
   Floyd_Road(G,j,e);
   cout<<endl;
 }
}
void Menu(){//���ƺ��� 
 Matrix G;
 List L;
 int n=0;
 cout<<"--------------------------------------------------------------------------|"<<endl;
 cout<<"1.�ļ���������ͼ���ڽӾ���               				  |"<<endl;
 cout<<"2.��Դ���·��Dijkstra�㷨�����Դ�㼰�䵽������������·�����Ⱥ����·��|"<<endl;
 cout<<"3.���öѽṹ��ʵ�ֵ����ȼ����У����Ľ��Ż�Dijkstra�㷨                    |"<<endl; 
 cout<<"4.Floyd-Warshall�㷨������������������֮������·������̳���            |"<<endl;
 cout<<"5.������������֮������·������̳���                                    |"<<endl;
 cout<<"6.�ҵ�ͼ��ÿ������v��ĳ��ָ������c���·��                                |"<<endl; 
 cout<<"0.�˳�                                                                    |"<<endl;
 cout<<"--------------------------------------------------------------------------|"<<endl;
 cin>>n;
 while(n){
   switch(n){
    case 1:
     File_Creat(&G);
     break;
    case 2:
     Dijkstra(G);
     PrintDijkstra(G);
     break;
    case 3:
     FileCreateList(&L);
     HeapDijkstra(L);
     PrintDijkstra(G);        
     break;
    case 4:
     Floyd(G);
     FloydPrint1(G);
     break;
    case 5:
     Floyd(G);
	 Floyd_Printf(G);
	 break;	
    case 6:
     Floyd(G);
     FloydPrint2(G);
     break;
    default:
     n=0;
     break; 
   }
   if(n!=0)
   {
    	cout<<"--------------------------------------------------------------------------|"<<endl;
 		cout<<"1.�ļ���������ͼ���ڽӾ���               				  |"<<endl;
 		cout<<"2.��Դ���·��Dijkstra�㷨�����Դ�㼰�䵽������������·�����Ⱥ����·��|"<<endl;
 		cout<<"3.���öѽṹ��ʵ�ֵ����ȼ����У����Ľ��Ż�Dijkstra�㷨                    |"<<endl; 
 		cout<<"4.Floyd-Warshall�㷨������������������֮������·������̳���            |"<<endl;
 		cout<<"5.������������֮������·������̳���                                    |"<<endl;
 		cout<<"6.�ҵ�ͼ��ÿ������v��ĳ��ָ������c���·��                                |"<<endl; 
 		cout<<"0.�˳�                                                                    |"<<endl;
 		cout<<"--------------------------------------------------------------------------|"<<endl;
    	cin>>n;
   }  
 } 
}
int main(){ 
 Menu();
} 
