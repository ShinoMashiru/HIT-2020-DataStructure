#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
struct AVLNode{
 	int data;
 	AVLNode *left,*right;
 	int height;//节点的高度 
};
int l;//全局变量l，记录旋转状态 
AVLNode *t;//AVL树
int max(int a,int b){
 return a>b? a :b ;
}
int hight(AVLNode *r){
 return r?r->height :-1; 
}
AVLNode *RRrotation(AVLNode *r){//RR旋,r是失衡的节点
    AVLNode *p=r->left ;//p是失衡节点的左儿子
    r->left =p->right ;//让失衡节点的左儿子指向失衡节点的左儿子的右儿子
    p->right =r;//失衡节点的右儿子指向失衡节点
    r->height=max(hight(r->left),hight(r->right))+1;//更新失衡节点的高度
    p->height=max(hight(p->left),hight(p->right))+1;//更新失衡节点左儿子的高度
    return p;//返回的是失衡节点的左儿子
}
AVLNode *LLrotation(AVLNode *r){//LL旋 ,r为失衡节点
	 AVLNode *p=r->right ;//p为失衡节点的右儿子
	 r->right =p->left ;//让失衡节点的右儿子指向失衡节点的右儿子的左儿子
	 p->left =r;//失衡节点的右儿子的左儿子指向失衡节点
	 r->height =max(hight(r->left ),hight(r->right ))+1;//更新失衡节点的高度
	 p->height =max(hight(p->left ),hight(p->right ))+1;//更新失衡节点的右儿子的高度
	 return p;//返回的是失衡节点的右儿子
}
AVLNode *LRrotation(AVLNode *r){//LR旋转，r为失衡的节点
    r->left =LLrotation(r->left );//把失衡节点的左儿子看成新的失衡节点去调用lrotation函数
    return RRrotation(r);   //再调用rrotation函数
}
AVLNode *RLrotation(AVLNode *r){//RL旋转，r为失衡的节点
	 r->right =RRrotation(r->right );//把失衡节点的右儿子看成新的失衡节点去调用rlotation函数
	 return LLrotation(r); //再调用lrotation函数
}
void rotate(){//输出旋转的类型 
    if(l==1){
       cout<<"进行了LL旋转"<<endl; 
     }
    else if(l==2){
      cout<<"进行了RR旋转"<<endl;
    }
    else if(l==3){
     cout<<"进行了LR旋转"<<endl;
    }
    else if(l==4){
      cout<<"进行了RL旋转"<<endl;
      }
    else if(l==0){
     cout<<"未进行旋转"<<endl;
    } 
 }
void Print(AVLNode *r){// 广义表打印 
    if(r){
       cout<<r->data ;
       cout<<"(";
    if(r->left){
       Print(r->left );
     }
    else{
       cout<<"#"; 
     }
    cout<<",";
    if(r->right){
       Print(r->right );
     }
    else{
      cout<<"#";
     }
    cout<<")"; 
    }
   else{
      cout<<"#"; 
    }     
  }
AVLNode *Insert(AVLNode *r,int e){//插入节点e
   if(r==NULL){//插入节点
      r=new AVLNode;
      r->data =e;
      r->left =r->right =NULL;
      r->height =0;
      return r;
      l=0;
    }
   else if(r->data < e){//插入在右子树
      r->right =Insert(r->right ,e);//递归插入，已经将节点插入在右子树中
      //接着判断是否失衡
      if(hight(r->right)-hight(r->left)>=2){//插入节点后可能引起失衡
      if(hight(r->right->left)>hight(r->right->right))
       l=4;//单纯标记作用，rl旋转
      else{
         l=1;//l旋转 
      }
      //旋转
      r=(hight(r->right->left)>hight(r->right->right))?RLrotation(r):LLrotation(r); 
     }
   }
    else if(r->data > e){//插入在左子树
      r->left =Insert(r->left ,e);//递归插入，已经将节点插入在左子树中
      //接着判断是否失衡
      if(hight(r->left )-hight(r->right )>=2){//插入的节点可能引起失衡
      if(hight(r->left->left)>hight(r->left->right))
         l=2;//r旋转 
      else{
        l=3;//lr旋转 
      }
       r=(hight(r->left->left)>hight(r->left->right))? RRrotation(r):LRrotation(r) ;
     }
   }
   r->height=max(hight(r->left),hight(r->right))+1;//更新高度
     return r;
}
AVLNode *Delete(AVLNode *r,int e){//删除节点e
 	if(r==NULL)
  	   return r;
 	else if(r->data < e){
 	   r->right=Delete(r->right ,e);  //递归删除
	} 
	 else if(r->data > e){
	   r->left =Delete(r->left , e);  //递归删除
	}
	 else{//找到当前的删除值
 	    if(r->left && r->right ){
  	        AVLNode *p = r->right ;
  	        while(p->left ) p=p->left ;//找到待删除节点的右子树的最左节点
  	         r->data = p->data ; //拿右子树最小的节点顶替被删除的节点
   	  	 r->right =Delete(r->right ,p->data ); //调整
          }
	    else{
  	        AVLNode *p=(r->left )? r->left :r->right ;//直接继承
 	        delete(r);
 	       return p;
  	    }  
	}
	//调整
 	 if(hight(r->left )-hight(r->right )>=2){//删除节点可能引起失衡  
          if(hight(r->left->left)>hight(r->left->right))
         l=2;//r旋转 
       else{
           l=3;//lr旋转 
       }
        r=(hight(r->left->left)>hight(r->left->right))? RRrotation(r):LRrotation(r) ;
       }
        else if(hight(r->right)-hight(r->left)>=2){//插入节点后可能引起失衡
        if(hight(r->right->left)>hight(r->right->right)){ 
         l=4;//rl旋转 
   }
        else{
           l=1;//l旋转 
   }
          r=(hight(r->right->left)>hight(r->right->right))?RLrotation(r):LLrotation(r); 
 }
          r->height=max(hight(r->left),hight(r->right))+1;
}
AVLNode* Find(AVLNode *r,int e){//查找
 if(r==NULL)
  return r;
 else{
  if(r->data > e){
   Find(r->left ,e);
  }
  else if(r->data < e){
   Find(r->right ,e );
  }
  else{
   return r;
  }
 }
}
void Sort(AVLNode *r){//排序 
 if(r==NULL)
  return;
 else{
  Sort(r->left );
  cout<<r->data<<" ";
  Sort(r->right);
 }
} 
void AVL(){
 fstream in;
 in.open("C:\\Users\\dell\\Desktop\\AVL.txt");
 char op;
 int e;
 in>>op>>e;
 while(op!='#'){
  switch(op){
   case 'i':
     t=Insert(t,e);
     cout<<"插入后的二叉树为：";
     Print(t);
     rotate();
     l=0;
     break;
   case 'd':
     AVLNode *p2;
     p2=Find(t,e);
     if(p2==NULL)
      cout<<"想删除的节点不存在"<<endl;
     else{
      p2=Delete(t,e);
      cout<<"删除后的二叉树为：";
      Print(t);
      rotate();
      l=0;
     } 
     break;
   default:
     break;
  }
  in>>op>>e; 
 } 
 in.close();
}
void Menu()
{
	 int n=0;
	 AVLNode* a;
	 int e;
	 cout<<"-------------------------------------------------------|"<<endl;
	 cout<<"1.文件创建，插入，删除AVL树(文件中i表示插入，d表示删除)|"<<endl;
	 cout<<"2.查找                                                 |"<<endl;
	 cout<<"3.排序                                                 |"<<endl;  
	 cout<<"0.退出                                                 |"<<endl;
	 cout<<"-------------------------------------------------------|"<<endl;
	 cin>>n;
 while(n){
   switch(n){
    case 1:
    	AVL();
     break;
    case 2:
    	cout<<"请输入要查找的节点"<<endl;
    	cin>>e;
    	a=Find(t,e);
    	if(a==NULL)
    	{
    		cout<<"节点不存在"<<endl;
		}else
		{
			cout<<"节点地址为"<<a<<endl;
		}
     break;
    case 3:
    	cout<<"AVL树排序结果"<<endl;
		Sort(t);    
		cout<<endl;  
     break;
    default:
     n=0;
     break; 
   }
   if(n!=0)
   {
   	 cout<<"-------------------------------------------------------|"<<endl;
	 cout<<"1.文件创建，插入，删除AVL树(文件中i表示插入，d表示删除)|"<<endl;
	 cout<<"2.查找                                                 |"<<endl;
	 cout<<"3.排序                                                 |"<<endl;  
	 cout<<"0.退出                                                 |"<<endl;
	 cout<<"-------------------------------------------------------|"<<endl;
	 cin>>n;
   }
}
}
int main()
{
	Menu();
}
