#include<iostream>
#include<fstream>
#include<queue>
#include<stack>
#define max 100
using namespace std;
bool visited[max];					//�ж��Ƿ���ʹ��ڵ� 
typedef struct Matrix				//�ڽӾ���Ĵ洢�ṹ 
{
   int vertex[max];					//�ڽӾ���Ķ�������
   int edge[max][max];				//�ڽӾ���ı�ֵ 
   int n,e;							//�ڽӾ���Ķ���ͱߵĸ��� 
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
void FileCreateGraph(Matrix *G)		//���ļ������ڽӾ��� 
{
    fstream in;
    in.open("C:\\Users\\dell\\Desktop\\ͼ.txt");
    int i,j,k,w;
    in>>G->n>>G->e;					//���붥�����n�ͱߵĸ���e��
    for(i=0;i<G->n;i++)
	{
    	G->vertex[i]=i;
    } 
    for(i=0;i<G->n;i++)
    for(j=0;j<G->n;j++)
   		G->edge[i][j]=0;			//��ʼ���ڽӾ��� 
    for(k=0;k<G->e;k++)
	{
	    in>>i>>j>>w;
	    G->edge[i][j]=w;			//�����(i,j)��Ȩ��w 
	    G->edge[j][i]=w;
    }
    in.close();
}
void PrintMatrix(Matrix *G)	    	//��ӡ�ڽӾ���
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
void FileCreateList(List *G)		//���ļ������ڽӱ�
{
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
         Edgenode* q=new Edgenode;
         q->subscript =i;q->cost =weight; 
         q->next =G->vlist[j].firstedge;
         G->vlist[j].firstedge =q;
      }
      in.close();
}
void PrintList(List *G)				//��ӡ�ڽӱ� 
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
void MtoL(Matrix *G,List *L)		//���ڽӾ���Gת��Ϊ�ڽӱ�T 
{							
     L->n=G->n ;					//��ʼ���ڽӱ� 
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
              p->subscript=G->vertex[k];	//���㸳ֵ 
              p->cost =G->edge[j][k];  		//��Ȩ�ظ�ֵ 
              p->next =L->vlist[j].firstedge;
              L->vlist[j].firstedge=p;
          }  
      }
    }  
}
void LtoM(Matrix *G,List *L)		//���ڽӱ�ת��Ϊ�ڽӾ���
{
    Edgenode *p;
    G->n =L->n;						//��ʼ���ڽӾ���
    G->e =L->e ;
    int i,j;
    for(i=0;i<G->n;i++)
	{
        for( j=0;j<G->n;j++)
	    {
           G->edge[i][j]=0;			//��ʼ���ڽӾ��� 
        }
    }
    for(int k=0;k<G->n;k++)
	{
        p=L->vlist[k].firstedge ;
        while(p!=NULL)
		{
           G->edge[k][p->subscript]=p->cost;//����Ȩ�ظ�ֵ 
           p=p->next ;
        }
    }
}
void M_DFSX(Matrix *G,int x)		//һ����ͨ��֧����ȵݹ� (ͨ���ڽӾ���)
{
    visited[x]=true;
    cout<<G->vertex[x]<<" ";
    for(int j=0;j<G->n;j++)
	{
       if(visited[j]!=true&&G->edge[x][j]!=0)
          M_DFSX(G,G->vertex[j]);
    }
}
void M_ReDFS(Matrix *G)			    //�ڽӾ�����ȵݹ��㷨 
{    
     for(int i=0;i<G->n;i++)
	 {
         visited[i]=false;			//��ÿ���ڵ���Ϊδ���ʹ� 
     }
     int count=1;					//ɭ�ָ��� 
     for(int i=0;i<G->n;i++)
	 {
       if(visited[i]!=true)
	   {
         cout<<"ɭ��"<<count++<<":"; 
         M_DFSX(G,i);
         cout<<endl;
       }  
     }
}
void M_DFS(Matrix *G)				//�ڽӾ�����ȷǵݹ��㷨
{ 
    for(int l=0;l<G->n;l++)			//��ÿ���ڵ���Ϊδ���ʹ� 
       visited[l]=false;
    stack<int>s;
    int count=1;					//ɭ�ָ��� 
    for(int j=0;j<G->n;j++)
	{
       if(visited[j]!=true)
	   {
	       cout<<"ɭ��"<<count++<<":";
	       visited[j]=true;
	       s.push(j);
	       cout<<G->vertex[j]<<" ";
	       while(!s.empty())	   //ջ�ǿ�ʱ��ջ��Ԫ�ص�δ���ʹ����ڽӵ���ջ������δ���ʵ��ڽӵ� 
		   {					   //��ջ��Ԫ�ص�ջ��ѭ�����ϲ���ֱ��ջ�� 
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
void L_DFSX(List *G,int x)			//һ����ͨ��֧��ȵݹ��㷨(�ڽӱ�) 
{ 
    Edgenode *p;
    visited[x]=true;				//���Ϊ���ʹ� 
    cout<<G->vlist[x].subscript<<" ";
    p=G->vlist[x].firstedge;
    while(p!=NULL)
	{
	    if(visited[p->subscript]!=true)
	    L_DFSX(G,p->subscript);
	    p=p->next;
    }
}
void L_ReDFS(List *G)		   		//�ڽӱ���ȵݹ��㷨 
{
    for(int i=0;i<G->n;i++)
	{
        visited[i]=false;
    }
    int count=1;
    for(int i=0;i<G->n;i++)			//����ÿһ���ڵ� 
	{
       if(!visited[i])
	   {
         cout<<"ɭ��"<<count++<<":"; 
         L_DFSX(G,i);
         cout<<endl;
       }  
    }
}
void L_DFS(List *G)					//�ڽӱ���ȷǵݹ��㷨 
{
	stack<int>s;
    Edgenode *p;
    for(int j=0;j<G->n;j++)
    visited[j]=false; 
    int count=1;					//ɭ����Ŀ
    for(int i=0;i<G->n;i++)			//����ÿ���ڵ� 
	{
         if(visited[i]!=true)
		 {
            cout<<"ɭ��"<<count<<":"; 
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
		                 cout<<G->vlist[p->subscript].subscript<<" ";//����ýڵ� 
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
void M_WFS(Matrix *G)				//�ڽӾ��������ȱ��� 
{     	
    for(int j=0;j<G->n;j++)
       visited[j]=false;
    queue<int>s;
    int count=1;
    for(int i=0;i<G->n;i++)			//��������Ƚ��ȳ���ͨ�����в���ʵ�֣����ʶ���Ԫ�ز����� 
	{								//������Ԫ�ص�δ�����ڽӵ���� 
       if(visited[i]!=true)
	   {
	   		cout<<"ɭ��"<<count++<<":"; 
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
void L_WFS(List *G)					//�ڽӱ������ȱ��� 
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
        cout<<"ɭ��"<<count++<<":"; 
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
    int x=0;//�����жϵ�ǰ������ͼ���ڽӾ������ڽӱ�0�����ڽӾ���1�����ڽӱ� 
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"0.�˳�                                                          |"<<endl;
    cout<<"1.ͨ�����ļ����봴��һ������ͼ���ڽӾ���                        |"<<endl;
    cout<<"2.ͨ�����ļ����봴��һ������ͼ���ڽӱ�                          |"<<endl;
    cout<<"3.��ʾ�ڽӾ���                                                  |"<<endl;
    cout<<"4.��ʾ�ڽӱ�                                                    |"<<endl;
    cout<<"5.���ڽӾ���ת��Ϊ�ڽӱ���ʾ                                  |"<<endl;
    cout<<"6.���ڽӱ�ת��Ϊ�ڽӾ�����ʾ                                  |"<<endl;
    cout<<"7.������ȵݹ��������ͼ                                        |"<<endl;
    cout<<"8.������ȷǵݹ��������ͼ                                      |"<<endl;
    cout<<"9.������ȱ�������ͼ                                            |"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl; 
    Matrix g;					//��������ͼ ���ڽӾ��� 
    List l;						//��������ͼ���ڽӱ� 
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
       		cout<<"�ڽӾ���Ϊ��"<<endl; 
       		PrintMatrix(&g);
       		cout<<"ת��Ϊ�ڽӱ��Ϊ��"<<endl ;
      		MtoL(&g,&l1);
     		PrintList(&l1);
     		break;
    	case 6:
      		Matrix g2;
     		cout<<"�ڽӱ�Ϊ��"<<endl; 
      		PrintList(&l);
      		cout<<"ת��Ϊ�ڽӾ����Ϊ��"<<endl ;
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
	cout<<"0.�˳�                                                          |"<<endl;
    cout<<"1.ͨ�����ļ����봴��һ������ͼ���ڽӾ���                        |"<<endl;
    cout<<"2.ͨ�����ļ����봴��һ������ͼ���ڽӱ�                          |"<<endl;
    cout<<"3.��ʾ�ڽӾ���                                                  |"<<endl;
    cout<<"4.��ʾ�ڽӱ�                                                    |"<<endl;
    cout<<"5.���ڽӾ���ת��Ϊ�ڽӱ���ʾ                                  |"<<endl;
    cout<<"6.���ڽӱ�ת��Ϊ�ڽӾ�����ʾ                                  |"<<endl;
    cout<<"7.������ȵݹ��������ͼ                                        |"<<endl;
    cout<<"8.������ȷǵݹ��������ͼ                                      |"<<endl;
    cout<<"9.������ȱ�������ͼ                                            |"<<endl;
 	cout<<"-----------------------------------------------------------------"<<endl; 
 if(x==0)
  cout<<"��ǰ����ͼΪ�ڽӾ����ʾ�����������ʾѡ����ȷ�Ĳ�����"<<endl;
 else
   cout<<"��ǰ����ͼΪ�ڽӱ��ʾ�����������ʾѡ����ȷ�Ĳ�����"<<endl;
 if(n!=0)
  cin>>n;
 } 
} 
int main()
{
	Menu();
}

