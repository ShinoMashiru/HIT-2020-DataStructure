#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
struct AVLNode{
 	int data;
 	AVLNode *left,*right;
 	int height;//�ڵ�ĸ߶� 
};
int l;//ȫ�ֱ���l����¼��ת״̬ 
AVLNode *t;//AVL��
int max(int a,int b){
 return a>b? a :b ;
}
int hight(AVLNode *r){
 return r?r->height :-1; 
}
AVLNode *RRrotation(AVLNode *r){//RR��,r��ʧ��Ľڵ�
    AVLNode *p=r->left ;//p��ʧ��ڵ�������
    r->left =p->right ;//��ʧ��ڵ�������ָ��ʧ��ڵ������ӵ��Ҷ���
    p->right =r;//ʧ��ڵ���Ҷ���ָ��ʧ��ڵ�
    r->height=max(hight(r->left),hight(r->right))+1;//����ʧ��ڵ�ĸ߶�
    p->height=max(hight(p->left),hight(p->right))+1;//����ʧ��ڵ�����ӵĸ߶�
    return p;//���ص���ʧ��ڵ�������
}
AVLNode *LLrotation(AVLNode *r){//LL�� ,rΪʧ��ڵ�
	 AVLNode *p=r->right ;//pΪʧ��ڵ���Ҷ���
	 r->right =p->left ;//��ʧ��ڵ���Ҷ���ָ��ʧ��ڵ���Ҷ��ӵ������
	 p->left =r;//ʧ��ڵ���Ҷ��ӵ������ָ��ʧ��ڵ�
	 r->height =max(hight(r->left ),hight(r->right ))+1;//����ʧ��ڵ�ĸ߶�
	 p->height =max(hight(p->left ),hight(p->right ))+1;//����ʧ��ڵ���Ҷ��ӵĸ߶�
	 return p;//���ص���ʧ��ڵ���Ҷ���
}
AVLNode *LRrotation(AVLNode *r){//LR��ת��rΪʧ��Ľڵ�
    r->left =LLrotation(r->left );//��ʧ��ڵ������ӿ����µ�ʧ��ڵ�ȥ����lrotation����
    return RRrotation(r);   //�ٵ���rrotation����
}
AVLNode *RLrotation(AVLNode *r){//RL��ת��rΪʧ��Ľڵ�
	 r->right =RRrotation(r->right );//��ʧ��ڵ���Ҷ��ӿ����µ�ʧ��ڵ�ȥ����rlotation����
	 return LLrotation(r); //�ٵ���lrotation����
}
void rotate(){//�����ת������ 
    if(l==1){
       cout<<"������LL��ת"<<endl; 
     }
    else if(l==2){
      cout<<"������RR��ת"<<endl;
    }
    else if(l==3){
     cout<<"������LR��ת"<<endl;
    }
    else if(l==4){
      cout<<"������RL��ת"<<endl;
      }
    else if(l==0){
     cout<<"δ������ת"<<endl;
    } 
 }
void Print(AVLNode *r){// ������ӡ 
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
AVLNode *Insert(AVLNode *r,int e){//����ڵ�e
   if(r==NULL){//����ڵ�
      r=new AVLNode;
      r->data =e;
      r->left =r->right =NULL;
      r->height =0;
      return r;
      l=0;
    }
   else if(r->data < e){//������������
      r->right =Insert(r->right ,e);//�ݹ���룬�Ѿ����ڵ��������������
      //�����ж��Ƿ�ʧ��
      if(hight(r->right)-hight(r->left)>=2){//����ڵ���������ʧ��
      if(hight(r->right->left)>hight(r->right->right))
       l=4;//����������ã�rl��ת
      else{
         l=1;//l��ת 
      }
      //��ת
      r=(hight(r->right->left)>hight(r->right->right))?RLrotation(r):LLrotation(r); 
     }
   }
    else if(r->data > e){//������������
      r->left =Insert(r->left ,e);//�ݹ���룬�Ѿ����ڵ��������������
      //�����ж��Ƿ�ʧ��
      if(hight(r->left )-hight(r->right )>=2){//����Ľڵ��������ʧ��
      if(hight(r->left->left)>hight(r->left->right))
         l=2;//r��ת 
      else{
        l=3;//lr��ת 
      }
       r=(hight(r->left->left)>hight(r->left->right))? RRrotation(r):LRrotation(r) ;
     }
   }
   r->height=max(hight(r->left),hight(r->right))+1;//���¸߶�
     return r;
}
AVLNode *Delete(AVLNode *r,int e){//ɾ���ڵ�e
 	if(r==NULL)
  	   return r;
 	else if(r->data < e){
 	   r->right=Delete(r->right ,e);  //�ݹ�ɾ��
	} 
	 else if(r->data > e){
	   r->left =Delete(r->left , e);  //�ݹ�ɾ��
	}
	 else{//�ҵ���ǰ��ɾ��ֵ
 	    if(r->left && r->right ){
  	        AVLNode *p = r->right ;
  	        while(p->left ) p=p->left ;//�ҵ���ɾ���ڵ��������������ڵ�
  	         r->data = p->data ; //����������С�Ľڵ㶥�汻ɾ���Ľڵ�
   	  	 r->right =Delete(r->right ,p->data ); //����
          }
	    else{
  	        AVLNode *p=(r->left )? r->left :r->right ;//ֱ�Ӽ̳�
 	        delete(r);
 	       return p;
  	    }  
	}
	//����
 	 if(hight(r->left )-hight(r->right )>=2){//ɾ���ڵ��������ʧ��  
          if(hight(r->left->left)>hight(r->left->right))
         l=2;//r��ת 
       else{
           l=3;//lr��ת 
       }
        r=(hight(r->left->left)>hight(r->left->right))? RRrotation(r):LRrotation(r) ;
       }
        else if(hight(r->right)-hight(r->left)>=2){//����ڵ���������ʧ��
        if(hight(r->right->left)>hight(r->right->right)){ 
         l=4;//rl��ת 
   }
        else{
           l=1;//l��ת 
   }
          r=(hight(r->right->left)>hight(r->right->right))?RLrotation(r):LLrotation(r); 
 }
          r->height=max(hight(r->left),hight(r->right))+1;
}
AVLNode* Find(AVLNode *r,int e){//����
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
void Sort(AVLNode *r){//���� 
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
     cout<<"�����Ķ�����Ϊ��";
     Print(t);
     rotate();
     l=0;
     break;
   case 'd':
     AVLNode *p2;
     p2=Find(t,e);
     if(p2==NULL)
      cout<<"��ɾ���Ľڵ㲻����"<<endl;
     else{
      p2=Delete(t,e);
      cout<<"ɾ����Ķ�����Ϊ��";
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
	 cout<<"1.�ļ����������룬ɾ��AVL��(�ļ���i��ʾ���룬d��ʾɾ��)|"<<endl;
	 cout<<"2.����                                                 |"<<endl;
	 cout<<"3.����                                                 |"<<endl;  
	 cout<<"0.�˳�                                                 |"<<endl;
	 cout<<"-------------------------------------------------------|"<<endl;
	 cin>>n;
 while(n){
   switch(n){
    case 1:
    	AVL();
     break;
    case 2:
    	cout<<"������Ҫ���ҵĽڵ�"<<endl;
    	cin>>e;
    	a=Find(t,e);
    	if(a==NULL)
    	{
    		cout<<"�ڵ㲻����"<<endl;
		}else
		{
			cout<<"�ڵ��ַΪ"<<a<<endl;
		}
     break;
    case 3:
    	cout<<"AVL��������"<<endl;
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
	 cout<<"1.�ļ����������룬ɾ��AVL��(�ļ���i��ʾ���룬d��ʾɾ��)|"<<endl;
	 cout<<"2.����                                                 |"<<endl;
	 cout<<"3.����                                                 |"<<endl;  
	 cout<<"0.�˳�                                                 |"<<endl;
	 cout<<"-------------------------------------------------------|"<<endl;
	 cin>>n;
   }
}
}
int main()
{
	Menu();
}
