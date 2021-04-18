#include<iostream>
#include<fstream>
#include<queue>
#include<stack>
#define max 100
using namespace std;
bool visited[max];					//判断是否访问过节点 
typedef struct Matrix				//邻接矩阵的存储结构 
{
   int vertex[max];					//邻接矩阵的顶点数组
   int edge[max][max];				//邻接矩阵的边值 
   int n,e;							//邻接矩阵的顶点和边的个数 
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
void FileCreateGraph(Matrix *G)		//从文件创建邻接矩阵 
{
    fstream in;
    in.open("C:\\Users\\dell\\Desktop\\图.txt");
    int i,j,k,w;
    in>>G->n>>G->e;					//输入顶点个数n和边的个数e；
    for(i=0;i<G->n;i++)
	{
    	G->vertex[i]=i;
    } 
    for(i=0;i<G->n;i++)
    for(j=0;j<G->n;j++)
   		G->edge[i][j]=0;			//初始化邻接矩阵 
    for(k=0;k<G->e;k++)
	{
	    in>>i>>j>>w;
	    G->edge[i][j]=w;			//输入边(i,j)和权重w 
	    G->edge[j][i]=w;
    }
    in.close();
}
void PrintMatrix(Matrix *G)	    	//打印邻接矩阵
{
   for(int i=0;i<G->n ;i++)
   {
      cout<<"\t"<<i; 
   }
   cout<<endl;
   for(int i=0;i<G->n ;i++)
   {
	   cout<<i<<"\t";
	   for(int j=0;j<G->n ;j++)
	   {
	       if(G->edge[i][j]==0)
		   {
	         cout<<"0\t";
	       }
	       else
	         cout<<G->edge[i][j]<<"\t";
	    }
	   cout<<endl;
   }
}
void FileCreateList(List *G)		//从文件创建邻接表
{
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
         Edgenode* q=new Edgenode;
         q->subscript =i;q->cost =weight; 
         q->next =G->vlist[j].firstedge;
         G->vlist[j].firstedge =q;
      }
      in.close();
}
void PrintList(List *G)				//打印邻接表 
{									
    for(int i=0;i<G->n ;i++)
	{
      cout<<i<<":\t";
      Edgenode *p;
      p=G->vlist[i].firstedge;
      while(p!=NULL)
	  {
        cout<<p->subscript<<"\t";
        p=p->next ;
      }
      cout<<endl;  
    } 
}
void MtoL(Matrix *G,List *L)		//将邻接矩阵G转化为邻接表T 
{							
     L->n=G->n ;					//初始化邻接表 
     L->e =G->e;					
     for(int i=0;i<G->n;i++ )
	 {								
        L->vlist[i].subscript =i;
        L->vlist[i].firstedge=NULL;
     }
     for(int j=0;j<G->n;j++)
	 {
        for(int k=0;k<G->n ;k++)
		{
          if(G->edge[j][k]!=0)
		  {
              Edgenode *p=new Edgenode;
              p->subscript=G->vertex[k];	//顶点赋值 
              p->cost =G->edge[j][k];  		//边权重赋值 
              p->next =L->vlist[j].firstedge;
              L->vlist[j].firstedge=p;
          }  
      }
    }  
}
void LtoM(Matrix *G,List *L)		//将邻接表转换为邻接矩阵
{
    Edgenode *p;
    G->n =L->n;						//初始化邻接矩阵
    G->e =L->e ;
    int i,j;
    for(i=0;i<G->n;i++)
	{
        for( j=0;j<G->n;j++)
	    {
           G->edge[i][j]=0;			//初始化邻接矩阵 
        }
    }
    for(int k=0;k<G->n;k++)
	{
        p=L->vlist[k].firstedge ;
        while(p!=NULL)
		{
           G->edge[k][p->subscript]=p->cost;//将边权重赋值 
           p=p->next ;
        }
    }
}
void M_DFSX(Matrix *G,int x)		//一个连通分支的深度递归 (通过邻接矩阵)
{
    visited[x]=true;
    cout<<G->vertex[x]<<" ";
    for(int j=0;j<G->n;j++)
	{
       if(visited[j]!=true&&G->edge[x][j]!=0)
          M_DFSX(G,G->vertex[j]);
    }
}
void M_ReDFS(Matrix *G)			    //邻接矩阵深度递归算法 
{    
     for(int i=0;i<G->n;i++)
	 {
         visited[i]=false;			//将每个节点标记为未访问过 
     }
     int count=1;					//森林个数 
     for(int i=0;i<G->n;i++)
	 {
       if(visited[i]!=true)
	   {
         cout<<"森林"<<count++<<":"; 
         M_DFSX(G,i);
         cout<<endl;
       }  
     }
}
void M_DFS(Matrix *G)				//邻接矩阵深度非递归算法
{ 
    for(int l=0;l<G->n;l++)			//将每个节点标记为未访问过 
       visited[l]=false;
    stack<int>s;
    int count=1;					//森林个数 
    for(int j=0;j<G->n;j++)
	{
       if(visited[j]!=true)
	   {
	       cout<<"森林"<<count++<<":";
	       visited[j]=true;
	       s.push(j);
	       cout<<G->vertex[j]<<" ";
	       while(!s.empty())	   //栈非空时将栈顶元素的未访问过的邻接点入栈，若无未访问的邻接点 
		   {					   //将栈顶元素弹栈。循环以上步骤直到栈空 
	       		int t = s.top();
	          	bool flag = false;
	          	for(int k=0;k<G->n ;k++)
			 	{
	           		if(G->edge[t][k]!=0)
			   		{
	             		if(visited[k]!=true)
				 		{
	               			visited[k]=true;
	               			cout<<G->vertex[k]<<" ";
	               			s.push(k);
	              		    flag = true;
	               			break ;
	             		}
	           		}
	         	}
	       		if (flag == false)
	        	s.pop();    
           }
           cout<<endl;
       } 
    }
} 
void L_DFSX(List *G,int x)			//一个连通分支深度递归算法(邻接表) 
{ 
    Edgenode *p;
    visited[x]=true;				//标记为访问过 
    cout<<G->vlist[x].subscript<<" ";
    p=G->vlist[x].firstedge;
    while(p!=NULL)
	{
	    if(visited[p->subscript]!=true)
	    L_DFSX(G,p->subscript);
	    p=p->next;
    }
}
void L_ReDFS(List *G)		   		//邻接表深度递归算法 
{
    for(int i=0;i<G->n;i++)
	{
        visited[i]=false;
    }
    int count=1;
    for(int i=0;i<G->n;i++)			//遍历每一个节点 
	{
       if(!visited[i])
	   {
         cout<<"森林"<<count++<<":"; 
         L_DFSX(G,i);
         cout<<endl;
       }  
    }
}
void L_DFS(List *G)					//邻接表深度非递归算法 
{
	stack<int>s;
    Edgenode *p;
    for(int j=0;j<G->n;j++)
    visited[j]=false; 
    int count=1;					//森林数目
    for(int i=0;i<G->n;i++)			//遍历每个节点 
	{
         if(visited[i]!=true)
		 {
            cout<<"森林"<<count<<":"; 
         	visited[i]=true;
         	s.push(i);
         	cout<<G->vlist[i].subscript<<" ";
         	p=G->vlist[i].firstedge;
         	while(!s.empty())
			{
	            p=G->vlist[s.top()].firstedge ;
	            bool flag = false;
	            while(p!=NULL)
				{
		             if(visited[p->subscript]!=true)
					 {
		                 visited[p->subscript]=true;
		                 cout<<G->vlist[p->subscript].subscript<<" ";//输出该节点 
		     		     s.push(p->subscript);  
		    		     p=G->vlist[p->subscript].firstedge;
		    		     flag = true;
		     		     break;
		            }else{p=p->next;}
	  	 		}
	   			if(flag == false)
	    	 	s.pop();
  		    } 
  		   cout<<endl;
  		   count++;
 		 }
 	}
}
void M_WFS(Matrix *G)				//邻接矩阵广度优先遍历 
{     	
    for(int j=0;j<G->n;j++)
       visited[j]=false;
    queue<int>s;
    int count=1;
    for(int i=0;i<G->n;i++)			//广度优先先进先出，通过队列操作实现，访问队首元素并出队 
	{								//将队首元素的未访问邻接点入队 
       if(visited[i]!=true)
	   {
	   		cout<<"森林"<<count++<<":"; 
	        visited[i]=true;
	        cout<<G->vertex[i]<<" ";
	        s.push(G->vertex[i]);
		    while(!s.empty())
			{
		        int k=s.front();
		        s.pop();
		        for(int j=0;j<G->n;j++)
				{
		          if(G->edge [k][j]!=0)
				  {
		             if(!visited[j])
					 {
		                visited[j]=true;
		                cout<<G->vertex[j]<<" ";
		                s.push(G->vertex[j]); 
		       		 }      
		      	  } 
		      	}
		    }
   			cout<<endl;
   		}   
  	}
}
void L_WFS(List *G)					//邻接表广度优先遍历 
{
    for(int j=0;j<G->n;j++)
      visited[j]=false;
    queue<int>s;
    Edgenode *p;
    int count=1;
    for(int i=0;i<G->n;i++)
	{
      if(!visited[i])
	  {
        cout<<"森林"<<count++<<":"; 
        visited[i]=true;
        cout<<G->vlist[i].subscript<<" ";
        s.push(G->vlist[i].subscript);
        while(!s.empty())
		{
           p=G->vlist[s.front()].firstedge;
           s.pop();
           while(p!=NULL)
		   {
             	if(visited[p->subscript]!=true)
			 	{
                	visited[p->subscript]=true;
          			cout<<G->vlist[p->subscript].subscript<<" ";
      		 		s.push(p->subscript); 
     		 	}
         	 	p=p->next;    
     	   } 
    	}
      	cout<<endl;
   	   } 
  	}
 }
void Menu()
{
    int x=0;//用来判断当前的无向图是邻接矩阵还是邻接表，0代表邻接矩阵，1代表邻接表 
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"0.退出                                                          |"<<endl;
    cout<<"1.通过从文件读入创建一个无向图的邻接矩阵                        |"<<endl;
    cout<<"2.通过从文件读入创建一个无向图的邻接表                          |"<<endl;
    cout<<"3.显示邻接矩阵                                                  |"<<endl;
    cout<<"4.显示邻接表                                                    |"<<endl;
    cout<<"5.将邻接矩阵转化为邻接表并显示                                  |"<<endl;
    cout<<"6.将邻接表转化为邻接矩阵并显示                                  |"<<endl;
    cout<<"7.深度优先递归遍历无向图                                        |"<<endl;
    cout<<"8.深度优先非递归遍历无向图                                      |"<<endl;
    cout<<"9.广度优先遍历无向图                                            |"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl; 
    Matrix g;					//创建无向图 的邻接矩阵 
    List l;						//创建无向图的邻接表 
    int n;
    cin>>n;
    while(n)
	{
      switch(n){
        case 1:
        	FileCreateGraph(&g);
          	x=0;
         	break;
        case 2:
         	FileCreateList(&l);
         	x=1;
         	break;   
     	case 3:
       		PrintMatrix(&g);
       		x=0;
       		break;  
     	case 4:
       		PrintList(&l);
         	x=1;
        	break;  
    	case 5:
       		List l1;
       		cout<<"邻接矩阵为："<<endl; 
       		PrintMatrix(&g);
       		cout<<"转化为邻接表后为："<<endl ;
      		MtoL(&g,&l1);
     		PrintList(&l1);
     		break;
    	case 6:
      		Matrix g2;
     		cout<<"邻接表为："<<endl; 
      		PrintList(&l);
      		cout<<"转化为邻接矩阵后为："<<endl ;
      		LtoM(&g2,&l);
      		PrintMatrix(&g2);
      		break;
    	case 7:
    		if(x==1)
       		L_ReDFS(&l);
			else
       		M_ReDFS(&g);  
       		break;
     	case 8:
       		if(x==1)
        	L_DFS(&l); 
			else
         	M_DFS(&g); 
    		break;
    	case 9:
       		if(x==0)
           	M_WFS(&g);
     		else
         	L_WFS(&l); 
      		break;
     	default :
      		n=0;
     		break;                      
 }
 	cout<<"-----------------------------------------------------------------"<<endl;
	cout<<"0.退出                                                          |"<<endl;
    cout<<"1.通过从文件读入创建一个无向图的邻接矩阵                        |"<<endl;
    cout<<"2.通过从文件读入创建一个无向图的邻接表                          |"<<endl;
    cout<<"3.显示邻接矩阵                                                  |"<<endl;
    cout<<"4.显示邻接表                                                    |"<<endl;
    cout<<"5.将邻接矩阵转化为邻接表并显示                                  |"<<endl;
    cout<<"6.将邻接表转化为邻接矩阵并显示                                  |"<<endl;
    cout<<"7.深度优先递归遍历无向图                                        |"<<endl;
    cout<<"8.深度优先非递归遍历无向图                                      |"<<endl;
    cout<<"9.广度优先遍历无向图                                            |"<<endl;
 	cout<<"-----------------------------------------------------------------"<<endl; 
 if(x==0)
  cout<<"当前无向图为邻接矩阵表示法，请根据提示选择正确的操作："<<endl;
 else
   cout<<"当前无向图为邻接表表示法，请根据提示选择正确的操作："<<endl;
 if(n!=0)
  cin>>n;
 } 
} 
int main()
{
	Menu();
}

