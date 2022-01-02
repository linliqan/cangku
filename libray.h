/**
 ******************************************************************************
  文 件 名   : API.h
  版 本 号   : v1.0
  功能描述   : 用于操纵二叉排序树的函数
  函数列表   : void putnum(SBTreeNode<T>* p)   //输出结点p的数据
               void CompareEfficency()         //比较二叉排序树和数组的查找效率

******************************************************************************/



#ifndef __API_H__
#define __API_H__

#include<vector>
#include<time.h>
#include<cstdlib>
#include"SortBinTree.h"
#include"LiBray.h"


#define _API_MAXSIZE_ 100


//输出结点p的数据
template<class T>
void putnum(SBTreeNode<T>* p)
{
	cout<<p->data<<" ";
}


/*****************************************************************************
 函 数 名  : CompareEfficency
 功能描述  : 比较二叉排序树和数组的查找效率
 输入参数  : 无
 输出参数  : 查找所用时间
 返 回 值  : 无
*****************************************************************************/
void CompareEfficency()
{
	LiBray stu[_API_MAXSIZE_];                                                                  //定义一个大小为_API_MAXSIZE_类型为LiBray的数组stu
	char a[20]="HaiLiPo";
	int Book_Price1=90;
	vector<int> vec;                                                                         //定义一个元素类型为int的向量
	for(int i=1;i<=_API_MAXSIZE_;i++)                                                       //插入数据1~100
		vec.push_back(i);
	srand((unsigned)time(NULL));                                                             //以时间为种子，产生一个随机数
	for(int i=_API_MAXSIZE_;i>=1;i--)                                                       //从向量vec中随机取出一个数保存在数组stu中
	{
		int j=rand()%i;                                                                    //得到一个在0~i之间的整数
		int k=vec[j];                                                                     //取出向量vec的第j+1个数
		for(vector<int>::iterator Iter=vec.begin();Iter!=vec.end();Iter++)
		{
			if(*Iter==k)
			{
				Iter=vec.erase(Iter);                                                  //删除向量vec的第j+1个数
				break;
			}
		}
		stu[_API_MAXSIZE_ - i].num=k;                                                  //向量vec的第j+1个数作为数组stu的元素的学号
		strncpy_s(stu[_API_MAXSIZE_ -i].name,a,20); 
		stu[_API_MAXSIZE_ - i].Book_Price=Book_Price1;
	}

	SortBTree<LiBray> BST2;                //定义一个二叉排序树对象
	BST2.CreateSBT(stu,_API_MAXSIZE_);      //以数组stu创建二叉排序树BST2
	
	clock_t start1,finish1;                 //start1、finish1分别用于记录从二叉排序树中搜索前后的时间
	clock_t start2,finish2;                 //start2、finish2分别用于记录从数组中搜索前后的时间
	clock_t sum1=0,sum2=0;                  //分别用于记录两种搜索所用的时间段
	for(int i=0;i<1000000;i++)              //执行1000000次，使sum1、sum2尽量大
	{
		int Rand=rand()%100;                 //随机产生一个要搜索的元素
		LiBray Time=stu[Rand];               //图书购买时间Time为搜索元素

		start1=clock();
		BST2.Search(Time);                  //从二叉排序树中搜索元素图书购买时间Time
		finish1=clock();

		start2=clock();
		for(int i=0;i<_API_MAXSIZE_;i++)    //从数组中搜索元素图书购买时间Time
		{
			if(stu[i]==Time)
				break;
		}
		finish2=clock();
		sum1+=(finish1-start1);             //累加从二叉排序树中搜索的时间段
		sum2+=(finish2-start2);             //累加从数组中搜索的时间段
	}
	cout<<"查找1000000次"<<endl;
	cout<<"二叉排序树所用的时间为："<<sum1<<endl;
	cout<<"数组所用的时间为：      "<<sum2<<endl;
	
}




#endif /*__API_H__*/
