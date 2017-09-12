/*1551445 童佳燕 计算机科学与技术1班*/
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
	
	cout << "大数运算测试用例数据以及结果：" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	cout << "测试大数构造：" << endl << endl;
	bigint a, b = "12346578989896898388383838";
	cout << "【无参构造a】,\n规则：无参构造初始化为0，因此输出a应为0，实际输出为：a=" << a << endl;;
	cout << "【有参数构造b】,\n应该输出 b=\"12346578989896898388383838\",\n实际输出为:b=" << b << endl;

	cout << "【加减数据测试项[95万-100万位大数]，一组数据：】" << endl;
	bigint c, d;
	cin >> c >> d;
	cout << endl << endl;

	cout << "【测试大数相加】：" << endl;
	cout << "【c+d=】" << c + d << endl;

	cout << "【测试大数相减】: " << endl;
	cout << "【c-d=】" << c - d << endl;
	cout << "【d-c=】" << d - c << endl;

	cout << "【测试正号运算符】：" << endl;
	cout << "【+c=】" << +c << endl;
	cout << "【测试负号运算符】：" << endl;
	cout << "【-d=】" << -d << endl;

	cout << "【测试赋值运算符】：" << endl;
	bigint e, f;
	e = c;
	f = (e = d);
	cout << "【e=c,则e=】" << e << endl;
	cout << "【f=(e=d),则f=】" << f << endl;

	cout << "【测试++/--运算符】：" << endl;
	cout << "【c++ =】" << (c++) << endl;
	cout << "【c-- =】" << (c--) << endl;
	cout << "【++c =】" << (++c) << endl;
	cout << "【--c =】" << (--c) << endl;

	cout << "【测试比较运算符:】 " << endl;
	cout << "如果c>d, 则返回1,实际返回：" << (c > d) << endl;
	cout << "如果c>=d,则返回1,实际返回：" << (c >= d) << endl;
	cout << "如果c<d, 则返回1,实际返回：" << (c < d) << endl;
	cout << "如果c<=d,则返回1,实际返回：" << (c <= d) << endl;
	cout << "如果c==d,则返回1,实际返回：" << (c == d) << endl;
	cout << "如果c!=d,则返回1,实际返回：" << (c != d) << endl;

	cout << endl << endl;

	

	cout << "【乘除模以及赋值数据测试项[1900-2000位大数，三组数据]：】" << endl;
	for (int i = 0; i < 3; i++)
	{
		LARGE_INTEGER tick, fc_begin, fc_end;
		QueryPerformanceFrequency(&tick);
		QueryPerformanceCounter(&fc_begin);

		cout << "【数据组" << i + 1 << "】：" << endl;
		bigint g, h;
		cin >> g >> h;

		cout << "【测试大数相乘】：" << endl;
		cout << "【g*h=】" << g*h << endl;

		QueryPerformanceCounter(&fc_end);
		cout << "时钟频率：" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
		cout << "时钟计数：" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
		cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "秒" << endl;

		cout << "【测试大数相除】: " << endl;
		cout << "【g/h=】" << g / h << endl;

		QueryPerformanceCounter(&fc_end);
		cout << "时钟频率：" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
		cout << "时钟计数：" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
		cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "秒" << endl;

		cout << "【测试大数取模】：" << endl;
		cout << "【g%h=】" << g%h << endl;
		QueryPerformanceCounter(&fc_end);
		cout << "时钟频率：" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
		cout << "时钟计数：" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
		cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "秒" << endl;
		
		cout << "【数据组" << i + 1 << "测试完成】";
		cout << endl << endl;
	}

	cout << "【测试数组】:" << endl;
	bigint k[5];
	for (int i = 0; i < 5; i++)
		cin >> k[i];

	for (int i = 0; i < 5; i++)
	{
		k[i] ++;
		cout << k[i] << endl;
	}
	
	cout << "【测试函数调用】：" << endl;
	cout <<"【average(a+b)=】" <<average(a, b) << endl;
	
	cout << "【测试完成】" << endl;
	return 0;
}