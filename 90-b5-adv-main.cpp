/*1551445 ͯ���� �������ѧ�뼼��1��*/
#include<iostream>
#include<Windows.h>
#include<iomanip>
#include"90-b5-adv.h"
using namespace std;

bigint average(bigint &a, bigint &b)
{
	return (a + b) / bigint("2");
}


int main()
{
	
	cout << "��������������������Լ������" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	cout << "���Դ������죺" << endl << endl;
	bigint a, b = "12346578989896898388383838";
	cout << "���޲ι���a��,\n�����޲ι����ʼ��Ϊ0��������aӦΪ0��ʵ�����Ϊ��a=" << a << endl;;
	cout << "���в�������b��,\nӦ����� b=\"12346578989896898388383838\",\nʵ�����Ϊ:b=" << b << endl;

	cout << "���Ӽ����ݲ�����[95��-100��λ����]��һ�����ݣ���" << endl;
	bigint c, d;
	cin >> c >> d;
	cout << endl << endl;

	cout << "�����Դ�����ӡ���" << endl;
	cout << "��c+d=��" << c + d << endl;

	cout << "�����Դ��������: " << endl;
	cout << "��c-d=��" << c - d << endl;
	cout << "��d-c=��" << d - c << endl;

	cout << "�������������������" << endl;
	cout << "��+c=��" << +c << endl;
	cout << "�����Ը������������" << endl;
	cout << "��-d=��" << -d << endl;

	cout << "�����Ը�ֵ���������" << endl;
	bigint e, f;
	e = c;
	f = (e = d);
	cout << "��e=c,��e=��" << e << endl;
	cout << "��f=(e=d),��f=��" << f << endl;

	cout << "������++/--���������" << endl;
	cout << "��c++ =��" << (c++) << endl;
	cout << "��c-- =��" << (c--) << endl;
	cout << "��++c =��" << (++c) << endl;
	cout << "��--c =��" << (--c) << endl;

	cout << "�����ԱȽ������:�� " << endl;
	cout << "���c>d, �򷵻�1,ʵ�ʷ��أ�" << (c > d) << endl;
	cout << "���c>=d,�򷵻�1,ʵ�ʷ��أ�" << (c >= d) << endl;
	cout << "���c<d, �򷵻�1,ʵ�ʷ��أ�" << (c < d) << endl;
	cout << "���c<=d,�򷵻�1,ʵ�ʷ��أ�" << (c <= d) << endl;
	cout << "���c==d,�򷵻�1,ʵ�ʷ��أ�" << (c == d) << endl;
	cout << "���c!=d,�򷵻�1,ʵ�ʷ��أ�" << (c != d) << endl;

	cout << endl << endl;

	

	cout << "���˳�ģ�Լ���ֵ���ݲ�����[1900-2000λ��������������]����" << endl;
	for (int i = 0; i < 3; i++)
	{
		LARGE_INTEGER tick, fc_begin, fc_end;
		QueryPerformanceFrequency(&tick);
		QueryPerformanceCounter(&fc_begin);

		cout << "��������" << i + 1 << "����" << endl;
		bigint g, h;
		cin >> g >> h;

		cout << "�����Դ�����ˡ���" << endl;
		cout << "��g*h=��" << g*h << endl;

		QueryPerformanceCounter(&fc_end);
		cout << "ʱ��Ƶ�ʣ�" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
		cout << "ʱ�Ӽ�����" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
		cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��" << endl;

		cout << "�����Դ��������: " << endl;
		cout << "��g/h=��" << g / h << endl;

		QueryPerformanceCounter(&fc_end);
		cout << "ʱ��Ƶ�ʣ�" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
		cout << "ʱ�Ӽ�����" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
		cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��" << endl;

		cout << "�����Դ���ȡģ����" << endl;
		cout << "��g%h=��" << g%h << endl;
		QueryPerformanceCounter(&fc_end);
		cout << "ʱ��Ƶ�ʣ�" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
		cout << "ʱ�Ӽ�����" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
		cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��" << endl;
		
		cout << "��������" << i + 1 << "������ɡ�";
		cout << endl << endl;
	}

	cout << "���������顿:" << endl;
	bigint k[5];
	for (int i = 0; i < 5; i++)
		cin >> k[i];

	for (int i = 0; i < 5; i++)
	{
		k[i] ++;
		cout << k[i] << endl;
	}
	
	cout << "�����Ժ������á���" << endl;
	cout <<"��average(a+b)=��" <<average(a, b) << endl;
	
	cout << "��������ɡ�" << endl;
	return 0;
}