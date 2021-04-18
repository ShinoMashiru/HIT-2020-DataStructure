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
int D[max];//存放从源点到各个顶点的最短路径长度 
bool S[max];//判断每个顶点是否已经求出最短路径 
int P[max];//记录每个最短路径的某个节点的前一个节点的编号 
int D2[max][max];//存放任意两个顶点之间的最短路径长度 
int P2[max][max];//存放任意两个顶点之间的最短路径编号 
struct qbase{	//优先级队列，弹出权值较小元素 
        int key,value;
        bool operator < (const qbase &other) const
        {
            return value>other.value;
        }
    };
typedef struct{ //邻接矩阵储存图 
 int vertex[max];//邻接矩阵的顶点数组
 int edge[max][max];//邻接矩阵的边值 
 int n,e;//邻接矩阵的顶点和边的个数 
}Matrix;
typedef struct Edgenode				//边表节点
{								 
  int subscript;					//顶点下标
  int cost;					 		//和主顶点邻接的边的权重
  Edgenode *next;					//指向下一边表节点的指针 
}Edgenode; 
typedef struct Vertex				//顶点表节点
{									
   int subscript;					//顶点下标 
   bool visit;						//标记节点是否被访问过 
   Edgenode *firstedge;				//边链表头指针 
}Vertex;
typedef struct List					//图的邻接表 
{
    Vertex vlist[max];				//顶点数组 
    int n,e;						//顶点个数和边的个数 
}List;
void FileCreateList(List *G){		//从文件创建邻接表 
      fstream in;
      in.open("C:\\Users\\dell\\Desktop\\图.txt");
      int i,k,j;
      int weight;
      in>>G->n >>G->e ; 
      for(i=0;i<G->n;i++)
	  {
         G->vlist[i].subscript=i;
         G->vlist[i].firstedge=NULL;//初始化邻接表 
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
void PrintMatrix(Matrix *t){//打印邻接矩阵的信息 
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
    		cout<<"∞\t";
   		}else
    	cout<<t->edge[i][j]<<"\t";
  	}
  cout<<endl;
 }
}
void File_Creat(Matrix *G){//以文件形式输入图的顶点和边
 cout<<"从文件读入有向图的邻接矩阵为："<<endl<<endl;
 int i,j,k,w;
 fstream in;
 in.open("C:\\Users\\dell\\Desktop\\图.txt"); 
 in>>G->n>>G->e;//输入顶点个数和边的个数；
 for(i=0;i<G->n;i++)
 {
  	G->vertex[i]=i;
 } 
 for(i=0;i<G->n ;i++)
  for(j=0;j<G->n ;j++)
    if(i!=j)
     G->edge[i][j]=MIN;//初始化邻接矩阵 
    else
     G->edge[i][j]=0;
 for(k=0;k<G->e;k++)
 {
  	in>>i>>j>>w;
  	G->edge[i][j]=w;//输入边(i,j)和权重w 
 }
 in.close();
 PrintMatrix(G);
 cout<<endl<<endl;
}
int mincost(Matrix C){ //计算当前最短路径的下标w 
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
void Dijkstra(Matrix C){//求源点0到每个顶点的最短路径 
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
void PrintDijkstra(Matrix G){//输出源点0到每个顶点的最短路径长度和最短路径
 for(int i=1;i<G.n;i++)
 {
  	if(D[i]!=MIN)
	{
   		cout<<"0---"<<i<<"最短长度为    "<<D[i]<<endl; 
   		stack<int>s;
   		s.push(i);
   		int x=P[i];
   		while(x!=0)
   		{
    		s.push(x);
    		x=P[x];
   		} 
   		s.push(0);
   		cout<<"0---"<<i<<"路径为： "; 
    	while(!s.empty() )
		{
      		cout<<s.top() <<"-";
     		s.pop() ;
    	}
   		cout<<endl;
 	}else
   		cout<<"0到"<<i<<"无路径"<<endl;
  
 }	
}
void HeapDijkstra(List L){//优先级队列优化求最短路径 
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
void Floyd(Matrix G){ //Floyd算法 
 //初始化 
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
     			D2[i][j]=D2[i][k]+D2[k][j];//更新顶点之间最短距离 
     			P2[i][j]=k;//记录最短路径经过的顶点 
   			}
  		}
 	} 
 } 
} 
void Floyd_Road(Matrix G,int e,int n){//求任意两个顶点间最短路径 
// int n,e;
// cout<<"请输入任意需要求的两个顶点之间的最短路径长度及其最短路径"<<endl;
// cin>>e>>n;
 if(P2[e][n]==-2) 
  cout<<e<<"与"<<n<<"之间没有路径"<<endl;
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
void FloydPrint(Matrix G){//打印每两个顶点之间的最短长度 
 cout<<"每个顶点之间的最短路径长度如下："<<endl; 
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
    	cout<<"∞"<<"\t";
   	}
  	cout<<endl;
 }
}
void FloydPrint1(Matrix G){//所有顶点之间的最短路径和最短长度
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
void Floyd_Printf(Matrix G){//打印任意两节点间最短路径 
 cout<<"请输入需要求的某两个顶点之间的最短路径"<<endl;
 int e,n;
 cin>>e>>n;
 if(D2[e][n]!=99999)
 cout<<"这两个顶点之间的最短路径为"<<endl; 
 Floyd_Road( G, e, n);
 cout<<endl;
 if(D2[e][n]!=99999)
 cout<<"这两个顶点之间的最短距离为："<<D2[e][n]<<endl;  
}
void FloydPrint2(Matrix G){//找到图中每个顶点v到某个指定顶点c最短路径 
 cout<<"请输入某个指定的顶点（0-"<<G.n-1<<")"<<endl;
 int e; 
 cin>>e;
 cout<<"任意顶点到顶点"<<e<<"的最短路径为："<<endl;
 for(int j=0;j<G.n;j++)
 {
  if(D2[j][e]!=99999)
   cout<<j<<"-"<<e<<":   "<<D2[j][e]<<endl; 
  else
   cout<<j<<"-"<<e<<":   "<<"∞"<<endl; 
   Floyd_Road(G,j,e);
   cout<<endl;
 }
}
void Menu(){//控制函数 
 Matrix G;
 List L;
 int n=0;
 cout<<"--------------------------------------------------------------------------|"<<endl;
 cout<<"1.文件创建有向图的邻接矩阵               				  |"<<endl;
 cout<<"2.单源最短路径Dijkstra算法，输出源点及其到其他顶点的最短路径长度和最短路径|"<<endl;
 cout<<"3.利用堆结构（实现的优先级队列），改进优化Dijkstra算法                    |"<<endl; 
 cout<<"4.Floyd-Warshall算法。计算所有两个顶点之间的最短路径和最短长度            |"<<endl;
 cout<<"5.任意两个顶点之间的最短路径和最短长度                                    |"<<endl;
 cout<<"6.找到图中每个顶点v到某个指定顶点c最短路径                                |"<<endl; 
 cout<<"0.退出                                                                    |"<<endl;
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
 		cout<<"1.文件创建有向图的邻接矩阵               				  |"<<endl;
 		cout<<"2.单源最短路径Dijkstra算法，输出源点及其到其他顶点的最短路径长度和最短路径|"<<endl;
 		cout<<"3.利用堆结构（实现的优先级队列），改进优化Dijkstra算法                    |"<<endl; 
 		cout<<"4.Floyd-Warshall算法。计算所有两个顶点之间的最短路径和最短长度            |"<<endl;
 		cout<<"5.任意两个顶点之间的最短路径和最短长度                                    |"<<endl;
 		cout<<"6.找到图中每个顶点v到某个指定顶点c最短路径                                |"<<endl; 
 		cout<<"0.退出                                                                    |"<<endl;
 		cout<<"--------------------------------------------------------------------------|"<<endl;
    	cin>>n;
   }  
 } 
}
int main(){ 
 Menu();
} 
