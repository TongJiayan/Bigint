#pragma once
/*1551445 童佳燕 计算机科学与技术1班*/
#include<iostream>
#include<string>
using namespace std;
#define P 1//positive 正数
#define N 0//negative f负数
class bigint
{
private:
	char sign;//正负
	unsigned int len;//位数 strlen(content)
	string content;//存储内容,不包括sign
public:
	bigint();//初始化，sign=P,len=2,存放sign
	bigint(const string str);//初始化
	bigint operator+(bigint &b);
	bigint operator-(bigint &b);
	bigint operator*(bigint &b);
	bigint operator/(bigint &b);
	bigint operator%(bigint &b);
	bigint operator[](int i);
	bigint operator+();//正号
	bigint operator-();//负号
	bigint operator+=(bigint &b);
	bigint operator-=(bigint &b);
	bigint operator++();
	bigint operator++(int);
	bigint operator--();
	bigint operator--(int);
	bool operator>(const bigint &b);
	bool operator>=(const bigint &b);
	bool operator<(const bigint &b);
	bool operator<=(const bigint &b);
	bool operator==(const bigint &b);
	bool operator!=(const bigint &b);
	friend ostream& operator<<(ostream& out, bigint& b);
	friend istream& operator >> (istream& in, bigint& a);
};
istream& operator >> (istream& in, bigint& a);
ostream& operator<<(ostream& out, bigint& b);
