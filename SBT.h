/**
  文 件 名   : SortBinTree.h
               **** 二叉排序树类SortBTree的公共成员函数：****
                bool CreateSBT(T *str,int n);                        //生成二叉排序树,
	            bool InputSBT(T &current);                           //插入二叉排序树
	            bool RemoveSBT(const T current)；                    //删除current结点
	            bool DeleteAll();                                    //删除整个二叉排序树
	            void Traverse(ostream& out)；                        //前序遍历输出
	            void LevelOrderPut(void (*visit)(SBTreeNode<T> *p)); //层次序遍历输出
	            void preOrder(void (*visit)(SBTreeNode<T> *p));      //前序非递归遍历
	            void inOrder(void (*visit)(SBTreeNode<T> *p));       //中序非递归遍历
	            void postOrder(void (*visit)(SBTreeNode<T> *p));     //后序非递归遍历
	            int GetSBTreeDepth()；                               //得到二叉排序树深度
	            void PrintSBTree()；                                 //竖着以树的形状输出二叉排序树
	            void PrintSBTree2();                                 //横着以树的形状输出二叉排序树
				bool Search(T x);                                    //搜索含数据x的元素

                *****二叉排序树类SortBTree的私有成员函数：****
                bool RemoveSBT(const T current,SBTreeNode<T> *&ptr); //删除current结点
                void Traverse(SBTreeNode<T> *subTree,ostream& out);  //前序遍历输出
	            int GetSBTreeDepth(SBTreeNode<T> *ptr);              //得到二叉排序树深度
	            void PrintSBTree(SBTreeNode<T> *ptr,int depth);      //竖着以树的形状输出二叉排序树
				bool Search(T x);                                    //搜索含数据x的元素
******************************************************************************/


#ifndef __SORTBINTREE_H__
#define __SORTBINTREE_H__


#include"LiBray.h"
#include<cstdlib>
#include<queue>
#include<stack>
#include<iomanip>

#define ArraySize 2048


//结点类定义
template<class T>
class SBTreeNode
{
public:
	T data;                  //数据域
	SBTreeNode<T> *left;     //左子女
	SBTreeNode<T> *right;    //右子女
};



//二叉排序树类定义
template<class T>
class SortBTree
{
public:
	SortBTree():root(NULL){}                             //构造函数
	~SortBTree(){ DeleteAll();}                          //析构函数

	bool CreateSBT(T *str,int n);                        //生成二叉排序树,
	bool InputSBT(T &current);                           //插入二叉排序树
	bool RemoveSBT(const T current)                      //删除current结点
	{
		if(root==NULL)
		{
			cout<<"二叉排序树为空！"<<endl;
			return false ;
		}
		if(RemoveSBT(current,root))
			return true;
		
		else return false;
	}
	bool DeleteAll();                                    //删除整个二叉排序树
	void Traverse(ostream& out)                          //前序遍历输出
	{
		if(root==NULL)
		{
			cout<<"二叉排序树为空！"<<endl;
			return ;
		}
		Traverse(root,out);
	}
	void LevelOrderPut(void (*visit)(SBTreeNode<T> *p)); //层次序遍历输出
	void preOrder(void (*visit)(SBTreeNode<T> *p));      //前序非递归遍历
	void inOrder(void (*visit)(SBTreeNode<T> *p));       //中序非递归遍历
	void postOrder(void (*visit)(SBTreeNode<T> *p));     //后序非递归遍历
	int GetSBTreeDepth()                                 //得到二叉排序树深度
	{
		return GetSBTreeDepth(root);
	}
	void PrintSBTree()                                   //竖着以树的形状输出二叉排序树
	{
		if(root==NULL)
		{
			cout<<"二叉树排序树为空！"<<endl;
			return ;
		}
		int depth=GetSBTreeDepth();
		PrintSBTree(root,depth);
	}
	void PrintSBTree2();                                 //横着以树的形状输出二叉排序树
	bool Search(T x);                                    //搜索含数据x的元素
private:
	SBTreeNode<T> * root;                                //指向根节点
	bool RemoveSBT(const T current,SBTreeNode<T> *&ptr); //删除current结点
    void Traverse(SBTreeNode<T> *subTree,ostream& out);  //前序遍历输出
	int GetSBTreeDepth(SBTreeNode<T> *ptr);              //得到二叉排序树深度
	void PrintSBTree(SBTreeNode<T> *ptr,int depth);      //竖着以树的形状输出二叉排序树
};



/*****************************************************************************
 函 数 名  : CreateSBT(公共函数)
 功能描述  : 生成二叉排序树
 输入参数  : 类型为T的字符串，和字符串的大小
 输出参数  : 无
 返 回 值  : true或false
*****************************************************************************/

template<class T>
bool SortBTree<T>::CreateSBT(T* str,int n)
{
	if(root!=NULL)                                                    //如何存在二叉树，生成失败
	{
		cout<<"已存在二叉排序树："<<endl;
		PrintSBTree2();                                               //横着以树的形状输出二叉排序树
		cout<<endl;
		return false;
	}
	SBTreeNode<T> *s=(SBTreeNode<T>*)malloc(sizeof(SBTreeNode<T>));   //分配存储空间
	if(s==NULL)                                                       //存储空间分配失败
	{
		cerr<<"存储空间分配错误！"<<endl;
		exit(1);
	}
	s->data=str[0];                                                   //以字符串str的第一个数据作为根结点
	s->left=NULL;
	s->right=NULL;
	root=s;
	for(int i=1;i<n;i++)                                              //其余数据依次插入
	{
		if(!InputSBT(str[i]))                                         //数据插入失败
		{
			cout<<"生成二叉排序树失败！"<<endl;
			if(!DeleteAll()) cout<<"删除残余二叉排序树失败！"<<endl;  //二叉排序树生成失败，删除先前插入的数据
			return false;
		}
	}
	return true;
}


/*****************************************************************************
 函 数 名  : InputSBT(公共函数)
 功能描述  : 把关键码为current的结点按照二叉排序树规则
            （左子树的数据总是大于根和右子树的数据）插入二叉排序树
 输入参数  : current  要插入的结点里的关键码
 输出参数  : 无
 返 回 值  : true或false
*****************************************************************************/

template<class T>
bool SortBTree<T>::InputSBT(T &current)  //插入二叉排序树
{
	SBTreeNode<T> *s=(SBTreeNode<T>*)malloc(sizeof(SBTreeNode<T>)); //分配存储空间
	if(s==NULL)                                                     //存储空间分配失败
	{
		cerr<<"存储空间分配错误！"<<endl;
		exit(1);
	}
	s->data=current;
	s->left=NULL;
	s->right=NULL;

	if(root==NULL)
	{
		root=s;
		return true;
	}
	SBTreeNode<T> *p=root;                                          //把根结点赋给指针p
	while(p!=NULL)                                                  //遍历二叉排序树，寻找合适点
	{
		if(p->data>current)                                         //当待插入数据current小于指针p指示的结点的数据时，遍历p的左子女
		{
			if(p->left==NULL)                                       //p无左子女，插入
			{
				p->left=s;
				return true;
			}
			else p=p->left;                                         //有左子女，进入
		}
		else if(p->data<current)                                    //当待插入数据current大于指针p指示的结点的数据时，遍历p的右子女
		{
			if(p->right==NULL)                                      //p无右子女，插入
			{
				p->right=s;
				return true;
			}
			else p=p->right;                                        //有右子女，进入
		}
		else                                                        //数据已存在
		{
			cout<<"数据已存在，插入失败"<<endl;
			return false;
		}
	}
	return false;
}


/*****************************************************************************
 函 数 名  : RemoveSBT(私有函数)
 功能描述  : 在以ptr为根的二叉排序树中删除含current的结点，若删除成功则新根通过ptr返回
 输入参数  : current  要删除的结点里的关键码
             ptr  根的引用
 输出参数  : 新根
 返 回 值  : true或false
*****************************************************************************/

template<class T>
bool SortBTree<T>::RemoveSBT(const T current,SBTreeNode<T> *&ptr)
{

	if(ptr!=NULL)
	{
	 
	    SBTreeNode<T> *temp;
		if(current<ptr->data)
		{
			if(RemoveSBT(current,ptr->left))                                        //在左子树中执行删除
				return true;
			else return false;
		}
		else if(current>ptr->data) 
		{
			if(RemoveSBT(current,ptr->right))                                      //在右子树中执行删除
				return true;
			else return false;
		}
		else if(ptr->left!=NULL && ptr->right!=NULL)                             //ptr指示的关键码为current的结点，它有两个子树
		{
			temp=ptr->right;                                                  //到右子树搜索中序下的第一个结点，用来替代ptr指示的结点
			while(temp->left!=NULL) temp=temp->left;
			ptr->data=temp->data;                                             //用该结点替代ptr指示的结点
			if(RemoveSBT(ptr->data,ptr->right))                                 //不可为RemoveSBT(ptr->data,temp);  删除该结点
				return true;
			else return false;
		}
		else                                                                    // ptr指示的关键码为current的结点，它只有一个或零个子树
		{
			temp=ptr;
			if(ptr->left==NULL) ptr=ptr->right;
			else ptr=ptr->left;
			delete temp;
			return true;
		}
	}
	else return false;
}


/*****************************************************************************
 函 数 名  : DeleteAll(公共函数)
 功能描述  : 用层次遍历算法删除二叉排序树所有结点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : true或false
*****************************************************************************/
template<class T>
bool SortBTree<T>::DeleteAll()
{
	if(root==NULL) return false;
	queue<SBTreeNode<T>*> Q;                      //创建一个类型为SBTreeNode<T>* 的队列Q
	SBTreeNode<T> *ptr=root;                      //根结点
	Q.push(ptr);                                  //根结点进入队列 
	while(!Q.empty())                             //队列不空
	{
		ptr=Q.front();                            //返回队列第一个元素
		Q.pop();                                  //删除队列第一个元素
		if(ptr->left!=NULL) Q.push(ptr->left);    //左子树不为空，进队
		if(ptr->right!=NULL) Q.push(ptr->right);  //右子树不为空，进队
		delete ptr;
		ptr=NULL;
	}
	root=NULL;                                    //把NULL赋给悬浮的根指针root
	return true;
}




/**************************，***************************************************
 函 数 名  : LevelOrderPut(公共函数)
 功能描述  : 从二叉排序树的根结点开始，自上向下，自左向右分层依次访问树中的各个结点,即层次遍历
 输入参数  : visit：函数指针
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
template<class T>
void SortBTree<T>::LevelOrderPut(void (*visit)(SBTreeNode<T> *p))
{
	if(root==NULL)
	{
		cout<<"二叉排序树为空！"<<endl;
		return ;
	}
	queue<SBTreeNode<T>*> Q;                                                                 //创建一个类型为SBTreeNode<T>* 的队列Q
	SBTreeNode<T> *ptr=root;                                                                 //根结点
	Q.push(ptr);                                                                            //根结点进入队列 
	while(!Q.empty())                                                                       //队列不空
	{
		ptr=Q.front();                                                                      //返回队列第一个元素
		Q.pop();                                                                            //删除队列第一个元素
		visit(ptr);                                                                         //调用函数visit
		if(ptr->left!=NULL) Q.push(ptr->left);                                              //左子树不为空，进队
		if(ptr->right!=NULL) Q.push(ptr->right);                                            //右子树不为空，进队
	}
}


/*****************************************************************************
 函 数 名  : Traverse(私有函数)
 功能描述  : 搜索并输出根为subTree的二叉排序树
 输入参数  : subTree：二叉排序树的结点
             out：输出流
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
template<class T>
void SortBTree<T>::Traverse(SBTreeNode<T> *subTree,ostream& out)
{
	if(subTree!=NULL)                     //subTree为空则返回，否则
	{
		out<<subTree->data<<" ";          //输出结点subTree的数据值
		Traverse(subTree->left,out);      //递归搜索并输出subTree的左子树
		Traverse(subTree->right,out);     //递归搜索并输出subTree的右子树
	}
}


/*****************************************************************************
 函 数 名  : preOrder(公共函数)
 功能描述  : 二叉排序树前序遍历的非递归算法
 输入参数  : visit：函数指针
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
template<class T>
void SortBTree<T>::preOrder(void (*visit)(SBTreeNode<T> *p))
{
	if(root!=NULL)
	{
		stack<SBTreeNode<T>*> S;                                            //栈S用于记录路径
		SBTreeNode<T> *ptr=root;                                           //ptr：遍历指针，从根结点开始
		S.push(ptr);                                                     //根结点进栈
	    while(!S.empty())                                                //栈不空
	    {
			ptr=S.top();                                                //返回栈顶元素
		    S.pop();                                                    //移除栈顶元素
		    visit(ptr);                                                 //访问栈顶元素
		    if(ptr->right!=NULL) S.push(ptr->right);                     //右子树进栈
		    if(ptr->left!=NULL) S.push(ptr->left);                     //左子树进栈
	    }
	}
	else cout<<"二叉排序树为空！"<<endl;
}


/*****************************************************************************
 函 数 名  : inOrder(公共函数)
 功能描述  : 二叉排序树中序遍历的非递归算法
 输入参数  : visit：函数指针
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
template<class T>
void SortBTree<T>::inOrder(void (*visit)(SBTreeNode<T> *p))
{
	if(root!=NULL)
	{
		stack<SBTreeNode<T> *> S;                                          //栈S用于记录路径
	    SBTreeNode<T> *ptr=root;                                          //ptr：遍历指针，从根结点开始
		do
		{
			while(ptr!=NULL)                                              //遍历指针末到最左下的结点，不空
			{
				S.push(ptr);                                               //该子树沿途结点进栈
				ptr=ptr->left;                                             //遍历指针进到左子树结点
			}
			if(!S.empty())                                               //栈不为空时退栈
			{
				ptr=S.top();                                           //返回栈顶元素
				S.pop();                                              //删除栈顶元素
				visit(ptr);                                          //访问栈顶元素
				ptr=ptr->right;                                       //遍历指针进入到右子树结点
			}
		}while(ptr!=NULL || !S.empty());
	}
	else cout<<"二叉排序树为空！"<<endl;
}


/*****************************************************************************
 函 数 名  : postOrder(公共函数)
 功能描述  : 二叉排序树后序遍历的非递归算法
 输入参数  : visit：函数指针
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
template<class T>
void SortBTree<T>::postOrder(void (*visit)(SBTreeNode<T> *p))
{
	if(root!=NULL)
	{
		stack<SBTreeNode<T>*> S;
		SBTreeNode<T> *ptr=root;
		SBTreeNode<T> *q;                                          //q指向当前结点的前一个已访问的结点
		int flag;
		do
		{
			while(ptr!=NULL)                                       //将ptr的所有左结点进栈
			{
				S.push(ptr);
				ptr=ptr->left;
			}
			q=NULL;
			flag=1;
			while(!S.empty() && flag)
			{
				ptr=S.top();                                      //取出当前的栈顶元素
				if(ptr->right==q)                                 //右子树不存在或已被访问，访问之
				{
					visit(ptr);                                  //访问结点p
					S.pop();                                     //删除栈顶元素
					q=ptr;                                       //q指向被访问的结点
				}
				else
				{
					ptr=ptr->right;                              //让ptr指向右子树
					flag=0;
				}
			}
		}while(!S.empty());
	}
	else cout<<"二叉排序树为空！"<<endl;
}


/*****************************************************************************
 函 数 名  : GetSBTreeDepth(私有函数)
 功能描述  : 计算二叉排序树的深度
 输入参数  : 
 输出参数  : 无
 返 回 值  : 二叉排序树的深度
*****************************************************************************/
template<class T>
int SortBTree<T>::GetSBTreeDepth(SBTreeNode<T> *ptr)
{
	if(ptr==NULL) return 0;              //ptr指示的结点为零，返回0
	int left,right,max;                  
	left=GetSBTreeDepth(ptr->left)+1;    //left储存ptr左子树的深度+1
	right=GetSBTreeDepth(ptr->right)+1;  //right储存ptr右子树的深度+1
	max=(left>right)?left:right;         //max储存两者的最大值
	return max;                          //返回当前结点的深度
}



/*****************************************************************************
 函 数 名  : PrintSBTree(私有函数)
 功能描述  : 竖着以树的形状输出二叉排序树
 输入参数  : ptr: 结点类指针
             depth: 二叉排序树的深度
 输出参数  : 整个二叉排序树
 返 回 值  : 无
*****************************************************************************/
template<class T>
void SortBTree<T>::PrintSBTree(SBTreeNode<T> *ptr,int depth)
{
	if(ptr==NULL) 
	{
		return ;
	}
	int k;
	PrintSBTree(ptr->right,depth+1);                                                //先进入二叉排序树的最右结点
	for(k=0;k<depth;k++)                                                           //输出空格
		cout<<"    ";
	cout<<ptr->data<<endl;                                                        //输出结点数据
	PrintSBTree(ptr->left,depth+1);                                              //再进入左子女
}


/*****************************************************************************
 函 数 名  : PrintSBTree2
 功能描述  : 横着显示树形二叉排序树
 输入参数  : 无
 输出参数  : 整个二叉排序树
 返 回 值  : 无
*****************************************************************************/
template<class T>
void SortBTree<T>::PrintSBTree2()
{
	if(root!=NULL)
	{
		int depth=GetSBTreeDepth();                                         //二叉排序树深度
		int h=depth;

		int a[ArraySize];                                                //每一层除第一个结点外每个结点距离前一个结点的距离
	    int c[ArraySize];                                                  //存储各结点投影在X轴上的坐标
	    memset(a,0,sizeof(a));
	    for(int i=0;i<depth;i++)                                         //设置二叉树第i(从0开始)层最左的结点的坐标为2^(depth-i-1)
	    {                                                                 //其中depth为二叉树的深度(从1开始)
			a[(1L<<i)-1]=(1L<<(depth-i-1));
			c[(1L<<i)-1]=(1L<<(depth-i-1));
		    for(int j=(1L<<i);j<((1L<<(i+1))-1);j++) 
		    {
				a[j]=2*a[(1L<<i)-1];                                       //每一层除第一个结点外每个结点距离前一个结点的距离为第一个结点的两倍
				c[j]=c[j-1]+a[j];
		    }
		}
		

	    int b[ArraySize];                                                 //以满二叉树为标准，比较二叉排序树在对应的位置是否存在结点,存在时标为1，不存在时标为-1
		memset(b,0,sizeof(b));
		queue<SBTreeNode<T>*> Q;                                             //创建一个类型为SBTreeNode<T>* 的队列Q
	    SBTreeNode<T> *ptr=root;                                          //根结点
	    Q.push(ptr);                                                            //根结点进入队列
		b[0]=1;                                       
		for(int i=1;i<((1L<<depth)-1);)
		{
			if(b[i]==-1)
			{
				if((2*i+1)<((1L<<depth)-1))  b[2*i+1]=-1;
				if((2*i+2)<((1L<<depth)-1))  b[2*i+2]=-1;
			}
			else if(b[i]==0)
			{
				if(!Q.empty())
				{
					ptr=Q.front();
					Q.pop();
					if(ptr->left!=NULL) 
					{
						Q.push(ptr->left);
						b[i]=1;
					}
					else
					{
						b[i]=-1;
						if((2*i+1)<((1L<<depth)-1))  b[2*i+1]=-1;
				        if((2*i+2)<((1L<<depth)-1))  b[2*i+2]=-1;
					}
					if(ptr->right!=NULL)
					{
						Q.push(ptr->right);
						b[i+1]=1;
					}
					else
					{
						b[i+1]=-1;
						if((2*i+3)<((1L<<depth)-1))  b[2*i+3]=-1;
				        if((2*i+4)<((1L<<depth)-1))  b[2*i+4]=-1;
					}
				}
			}
			i=i+2;
		}
		

		queue<SBTreeNode<T>*> S;                                          //创建一个类型为SBTreeNode<T>* 的队列S
	    SBTreeNode<T> *q=root;                                          //根结点
	    S.push(q);                                                         //根结点进入队列 
		for(int i=0;i<((1L<<depth)-1);i++)
		{
			if(b[i]==1)
			{
				if(!S.empty())
				{
					q=S.front();
					S.pop();
					cout<<setfill(' ')<<setw(a[i]*2)<<q->data;
					if(q->left!=NULL) S.push(q->left);
					if(q->right!=NULL) S.push(q->right);
				}
			}
			else if(b[i]==-1)
			{
				cout<<setfill(' ')<<setw(a[i]*2)<<' ';
			}
			if(a[i]>a[i+1])                                              //当a[i]>a[i+1]时，换行
			{
				
				/**int flag2=2;
				for(int n=depth-h;n<(depth-1);n++)
				{
					int flag1=0;
					cout<<endl;
					for(int j=i/2;j<i+1;j++)
					{
						if( b[j]==1)
						{
							//flag1=0;                
							if(b[2*j+1]==1)
							{
								cout<<setfill(' ')<<setw(2*c[j]-flag2-flag1)<<'/';
								if(b[2*j+2]==1) 
								{
										cout<<setfill(' ')<<setw(2*flag2)<<'\\';
										flag1=2*c[j]+2;
								}
								else flag1=2*c[j]-flag2;	
							}
						}
					}
					flag2=flag2+2;
				}
				h--;**/
				cout<<endl;
			}
		}
		cout<<endl;
	}
	else
	{
		cout<<"二叉排序树为空！"<<endl;
		return ;
	}

}


/*****************************************************************************
 函 数 名  : Search
 功能描述  : 搜索含数据x的元素
 输入参数  : x：搜索的数据
 输出参数  : 无
 返 回 值  : true或false
*****************************************************************************/
template<class T>
bool SortBTree<T>::Search(T x)
{
	if(root!=NULL)
	{
		SBTreeNode<T> *p=root;
		while(p!=NULL)
		{
			if(x==p->data) return true;     //找到含数据x的结点
			else if(p->data>x) p=p->left;   //数据x比结点包含的数据小，p进入结点的左子树
			else p=p->right;                 //数据x比结点包含的数据大，p进入结点的右子树
		}
	}
	return false;
}

#endif /* __SORTBINTREE_H__ */
