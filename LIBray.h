
#ifndef __LIBRAY_H__
#define __LIBRAY_H__


#include<string>

#define NAMESIZE 50
using namespace std;

struct LiBray
{
	int num;              //图书编号
	char name[NAMESIZE];  //图书名字
	char Autor_name[NAMESIZE];  //图书作者
	int Book_Price;            //图书价格
	char Time;                 //图书购买时间

	void operator =(LiBray &Book1);
	friend bool operator >(LiBray &Book1,LiBray &Book2);  
	friend bool operator <(LiBray &Book1,LiBray &Book2);
	friend bool operator ==(LiBray &Book1,LiBray &Book2);
	friend ostream& operator <<(ostream &,LiBray &);
	friend istream& operator >>(istream &,LiBray &);
	
};

/*************************************
函数：重载运算符'>'
功能：比较图书编号的大小
参数：LiBray结构体的引用Book1、Book2.
返回值：true或false
**************************************/
bool operator >(LiBray &Book1,LiBray &Book2)
{

	if(Book1.num > Book2.num)
		return true;
	else return false;
}

/*************************************
函数：重载运算符'<'
功能：比较图书编号的大小
参数：LiBray结构体的引用Book1、Book2.
返回值：true或false
**************************************/
bool operator <(LiBray &Book1,LiBray &Book2)
{
	if(Book1.num < Book2.num)
		return true;
	else return false;
}

/*************************************
函数：重载运算符'=='
功能：判断图书学号是否等于
参数：LiBray结构体的引用Book1、Book2.
返回值：true或false
**************************************/
bool operator ==(LiBray &Book1,LiBray &Book2)
{
	if(Book1.num == Book2.num)
		return true;
	else return false;
}


void LiBray::operator =(LiBray &Book1)
{
	num= Book1.num;
	strncpy_s(name,Book1.name,20);
	Book_Price = Book1.Book_Price;
}


ostream& operator <<(ostream& out,LiBray& Book)
{
	out<<"("<<Book.num<<","<<Book.name<<","<<Book.Book_Price<<")";
	return out;
}


istream& operator >>(istream& in,LiBray& Book)
{
	in>>Book.num>>Book.name>>Book.Book_Price;
	return in;
}

#endif  /*__LIBRAY_H__*/
