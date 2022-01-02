
#ifndef __STUDENT_H__
#define __STUDENT_H__


#include<string>

#define NAMESIZE 20
using namespace std;

struct Student
{
	int num;              //学生学号
	char name[NAMESIZE];  //学生名字
	int score;            //学生成绩
	void operator =(Student &student1);
	friend bool operator >(Student &student1,Student &student2);  
	friend bool operator <(Student &student1,Student &student2);
	friend bool operator ==(Student &student1,Student &student2);
	friend ostream& operator <<(ostream &,Student &);
	friend istream& operator >>(istream &,Student &);
	
};

/*************************************
函数：重载运算符'>'
功能：比较学生学号的大小
参数：Student结构体的引用student1、student2.
返回值：true或false
**************************************/
bool operator >(Student &student1,Student &student2)
{
	if(student1.num > student2.num)
		return true;
	else return false;
}

/*************************************
函数：重载运算符'<'
功能：比较学生学号的大小
参数：Student结构体的引用student1、student2.
返回值：true或false
**************************************/
bool operator <(Student &student1,Student &student2)
{
	if(student1.num < student2.num)
		return true;
	else return false;
}

/*************************************
函数：重载运算符'=='
功能：判断学生学号是否等于
参数：Student结构体的引用student1、student2.
返回值：true或false
**************************************/
bool operator ==(Student &student1,Student &student2)
{
	if(student1.num == student2.num)
		return true;
	else return false;
}


void Student::operator =(Student &student1)
{
	num=student1.num;
	strncpy(name,student1.name,20);
	score=student1.score;
}


ostream& operator <<(ostream& out,Student& student)
{
	out<<"("<<student.num<<","<<student.name<<","<<student.score<<")";
	return out;
}


istream& operator >>(istream& in,Student& student)
{
	in>>student.num>>student.name>>student.score;
	return in;
}

#endif  /*__STUDENT_H__*/
