#pragma once
/*1551445 ͯ���� �������ѧ�뼼��1��*/
#include<iostream>
#include<string>
using namespace std;
#define P 1//positive ����
#define N 0//negative f����
class bigint
{
private:
	char sign;//����
	unsigned int len;//λ�� strlen(content)
	string content;//�洢����,������sign
public:
	bigint();//��ʼ����sign=P,len=2,���sign
	bigint(const string str);//��ʼ��
	bigint operator+(bigint &b);
	bigint operator-(bigint &b);
	bigint operator*(bigint &b);
	bigint operator/(bigint &b);
	bigint operator%(bigint &b);
	bigint operator[](int i);
	bigint operator+();//����
	bigint operator-();//����
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
