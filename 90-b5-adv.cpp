/*1551445 童佳燕 计算机科学与技术1班*/
#include"90-b5-adv.h"

bigint::bigint()
{
	sign = P;//初始化为+
	len = 1;
	content = "0";
}
bigint::bigint(const string str)
{
	if (str[0] == '-')
	{
		sign = N;
		len = str.length() - 1;
		content.append(str, 1, len);//将str中第二位开始的数据接到content
	}
	else if (str[0] == '+')
	{
		sign = P;
		len = str.length() - 1;
		content.append(str, 1, len);
	}
	else
	{
		sign = P;
		len = str.length();
		content = str;
	}
}

/*只需要处理正整数之间的加和减，遇到负数，比如正整数-负整数，转换成 正整数+正整数；
                                        //    正整数+负整数，转换成 正整数-正整数；
										//	  负整数1+正整数2，转换成 正整数2-正整数1
											  负整数1-负整数2，转换成 正整数2-正整数1
											  负整数-正整数，转换成 （-1）正整数+正整数
										//	  负整数1+负整数2，转换成 （-1）正整数+正整数*/
bigint bigint::operator+(bigint &b)
{
	/*先进行诊断，判断是否需要转诊*/
	if (b.sign == N && sign==P)
	{
		bigint tmpB = b;
		tmpB.sign = P;//转成正整数送到对应的加/减运算中
		return ((*this) - tmpB);
	}
	else if (sign == N && b.sign == P)
	{
		bigint tmpB = *this;
		tmpB.sign = P;
		return (b - tmpB);
	}

	/*两个负整数或两个正整数的相加处理*/
	bigint result;
	unsigned int lenMin = (len < b.len) ? len : b.len;
	unsigned int lenMax = (len > b.len) ? len : b.len;
	result.len = lenMax + 1;;//两数相加和的位数最多比 较大数的位数多一位

	result.content.resize(result.len + 1);//content大小为len+1
	(result.content)[result.len] = '\0';

	/*用指针比用数组形式找效率更高*/
	char *pr = &((result.content)[result.len - 1]);
	char *pa = &(content[len-1]);
	char *pb = &((b.content)[b.len-1]);
	unsigned int i = 0,carry=0,tmpResult=0;

	while (i < lenMax)
	{
		if (i < lenMin)
			tmpResult = carry + (*pa - '0') + (*pb - '0');
		else if(lenMin==len)
			tmpResult = carry + (*pb - '0');
		else
			tmpResult = carry + (*pa - '0');
		*pr= tmpResult % 10+'0';//int转字符
		carry = tmpResult / 10;
		pr--;
		if (i < len)
			pa--;
		if (i < b.len)
			pb--;
		i++;
	}
	*pr = carry + '0';
	if (carry == 0)
	{
		result.content.assign(result.content, 1, lenMax);//把第一位去掉
		result.len--;
	}
	if (sign == N&&b.sign == N)
		result.sign = N;
	return result;
}

bigint bigint::operator-(bigint &b)
{
	/*先进行诊断，判断是否需要转诊*/
	if (b.sign == N && sign == P)
	{
		bigint tmpB = b;
		tmpB.sign = P;
		return((*this)+ tmpB);
	}
	else if (sign == N && b.sign == P)
	{
		bigint tmpB = b;
		tmpB.sign = N;
		return((*this)+ tmpB);
	}

	/*两个负整数或两个正整数的减处理*/
	bigint result;
	char *p1, *p2;/*p1指向被减数(较大)，p2指向减数（较小）   备注：被减数-减数=差*/
	unsigned int lenMin = 0, lenMax = 0;
	if (len < b.len)
	{
		lenMin = len;
		lenMax = b.len;
		p1 = &((b.content)[b.len - 1]);
		p2 = &(content[len - 1]);
	}
	else if (len >b.len)
	{
		lenMin = b.len;
		lenMax = len;
		p1 = &(content[len - 1]);
		p2 = &((b.content)[b.len - 1]);
	}
	else
	{
		lenMax = lenMin = len;
		if (content > b.content)
		{
			p1 = &(content[len - 1]);
			p2 = &((b.content)[b.len - 1]);
		}
		else
		{
			p1 = &((b.content)[b.len - 1]);
			p2 = &(content[len - 1]);
		}
	}


	/*判断结果的正负，还留在-函数中的只有双正或双负两种情况，分别存在a>b以及b>a两种，
	由于result初始化sign为P，因此只需要设置sign为N的情况*/

	if (sign == N&&b.sign == N)
	{
		if (p1 != &((b.content)[b.len-1]))//a更大
			result.sign = N;
	}
	else
		if (p1 == &((b.content)[b.len-1]))//b更大
			result.sign = N;

	result.len = lenMax;//两数相减的位数最多为两者较长的数的位数
	result.content.resize(result.len + 1);//content大小为len+1
	(result.content)[result.len] = '\0';

	/*用指针比用数组形式找效率更高*/
	char *pr = &((result.content)[result.len - 1]);
	unsigned int i = 0, borrow = 0,zeroNum=0;
	int tmpResult = 0;//必须用有符号型int！！
	while (i < lenMax)
	{
		if (i < lenMin)
		{
			tmpResult = *p1-*p2 - borrow;
			p1--;
			p2--;
		}
		else
		{
			tmpResult = *p1-'0' - borrow;//小心'0'
			p1--;
		}
		if (tmpResult < 0)
		{
			tmpResult += 10;
			borrow = 1;
		}
		else
			borrow = 0;
		*pr = tmpResult + '0';
		pr--;
		i++;
	}
	/*两数相减会存在结果前面都为0的情况，要把这串0去掉*/
	pr++;
	while (*pr == '0'&&zeroNum<lenMax)
	{
		zeroNum++;
		pr++;
	}
	result.content.assign(result.content, zeroNum, lenMax-zeroNum);//把第一位去掉
	result.len-=zeroNum;
	return result;
}

bigint bigint::operator*(bigint &b)
{
	bigint result;

	/*确定符号位*/
	if (sign != b.sign)
		result.sign = N;

	/*确定长度*/
	result.len = len + b.len;//两者相乘位数最多为两者位数之和
	result.content.resize(result.len + 1);//多一位存储尾零
	result.content.assign(result.len,'0');//存放数据的区域用'0'填充
	result.content[result.len] = '\0';
	

	char* pa = &(content[len - 1]);
	char* pb = &((b.content)[b.len - 1]);
	char* pr = &((result.content)[result.len - 1]);
	char* pTmp = pr,*pTmp2=pr,*pbTmp=pb;
	int carry = 0;//进位
	unsigned int tmpResult = 0;
	for (unsigned int i = 0; i < len; i++)
	{
		pr = pTmp;
		pb = pbTmp;
		for (unsigned int j = 0; j < b.len; j++)
		{
			tmpResult = (*pa - '0')*(*pb - '0') + carry;
			(*pr) += (tmpResult % 10);
			pTmp2 = pr;
			while ((*pr) > 9 + '0')
			{
				*pr = (*pr-'0') % 10+'0';
				pr--;
				(*pr)++;
			}
			pr = pTmp2;
			carry = tmpResult / 10;
			pb--;
			pr--;
		}
		(*pr) += carry;
		while ((*pr) > 9 + '0')
		{
			*pr = (*pr - '0') % 10 + '0';
			pr--;
			(*pr)++;
		}
		pTmp--;
		pa--;
	}
	if (result.content[0] == '0')
	{
		result.content.assign(result.content, 1, result.len - 1);
		result.len--;
	}
	return result;
}

bigint bigint::operator/(bigint &b)
{
	bigint result;
	/*确定符号位*/
	if (sign != b.sign)
		result.sign = N;
	
	/*特殊情况处理，简化算法*/
	if (len < b.len || len == b.len && content<=b.content)
	{
		result.len = 1;
		result.content = "0";
		if (content == b.content && len==b.len)
			result.content = "1";
		return result;
	}
	
	result.len = len - b.len + 1;//确定商的最大长度
	result.content.assign(result.len, '0');//将result赋为0串
	bigint tmpA = *this;//在减的过程中会改变，因此需要一个替身
	tmpA.sign = P;//运算过程中是把正负隔离的，所以用正整数来算
	bigint tmpResult;//中间值
	
	if (len == b.len)
	{
		int count = 0;
		while (tmpA.len >b.len || tmpA.len == b.len&&tmpA.content > b.content)
		{
			if (b.sign == P)
				tmpA = tmpA - b;//不能单纯的-，因为正负是不确定的，需要分类讨论
			else
				tmpA = tmpA + b;
			tmpA.len = tmpA.content.length();
			count++;
		}
		
		result.content[0] = count+'0';
		return result;
	}
	
	bigint tmpB = b;
	tmpB.sign = P;
	int numZeroAdd = len - b.len - 1;//补充的0的个数
	while (tmpA.len>b.len||tmpA.len==b.len&&tmpA.content>b.content)
	{
		tmpResult.content.resize(numZeroAdd + 3);
		tmpResult.len = numZeroAdd + 2;
		tmpResult.content.assign(tmpResult.len, '0');
		tmpB = b;
		tmpB.content.append(numZeroAdd--, '0');
		tmpB.len = tmpB.content.length();
		if (tmpB > tmpA)//两者都是正的，可以直接比较
			continue;
		int count = 0;
		while (tmpA>=tmpB)
		{
			tmpA = tmpA - tmpB;
			tmpA.len = tmpA.content.length();
			count++;
		}
		tmpResult.content[1] = count % 10+'0';
		tmpResult.content[0] = count / 10+'0';
		result =result+ tmpResult;
	}
	if (result.content[0] == '0')
	{
		result.content.assign(result.content, 1, result.len - 1);
		result.len--;
	}
	return result;
}

bigint bigint::operator%(bigint &b)
{
	bigint result;
	/*确定符号位*/
	if (sign != b.sign)
		result.sign = N;

	int tmpSign = sign, tmpSignB = b.sign;//将*this，b的符号位先存下来
	sign = P;
	b.sign = P;
	/*特殊情况处理，简化算法*/
	if (b>(*this))
	{
		result.len = len;
		result.content = content;
		result.sign = tmpSign;
		return result;
	}

	result.len = len - b.len + 1;//确定商的最大长度
	result.content.assign(result.len, '0');//将result赋为0串
	bigint tmpA = *this;//在减的过程中会改变，因此需要一个替身

	if (len == b.len)
	{
		while (tmpA>=b)
		{
			tmpA = tmpA - b;
			tmpA.len = tmpA.content.length();
		}
		result.content = tmpA.content;
		result.len=tmpA.len;
		b.sign = tmpSignB;
		sign = tmpSign;//符号位复原
		return result;
	}
	bigint tmpB = b;
	int numZeroAdd = len - b.len - 1;//补充的0的个数
	int i = 0;
	while (tmpA>=b)
	{
		tmpB = b;
		tmpB.content.append(numZeroAdd--, '0');
		tmpB.len = tmpB.content.length();
		if (tmpB > tmpA)//两者都是正的，可以直接比较
			continue;
		while (tmpA >= tmpB)
		{
			tmpA = tmpA - tmpB;
			tmpA.len = tmpA.content.length();
		}
	}
	result.len = tmpA.len;
	result.content = tmpA.content;
	b.sign = tmpSignB;
	sign = tmpSign;
	return result;
}
bigint bigint::operator[](const int i)
{
	return *(this + i);
}

bigint bigint::operator++()//++a
{ 
	if (sign == N)
	{
		bigint result = *this;
		result.sign = P;
		result--;
		result.sign = N;
		*this = result;
		return result;
	}
	char *p = &(content[len - 1]);//指向最后一位
	(*p)++;
	while ((*p) > 9 + '0')
	{
		(*p) = (*p) % 10 + '0';
		p--;
		if (p < &(content[0]))
		{
			content.replace(1, len - 1, content);
			p++;
			(*p) = '0';
		}
		(*p)++;
	}
	bigint result = *this;
	return result;
}
bigint bigint::operator++(int)//a++
{
	if (sign == N)
	{
		bigint result = *this;
		sign = P;
		(*this)--;
		sign = N;
		return result;
	}
	bigint result = *this;
	char *p = &(content[len - 1]);//指向最后一位
	(*p)++;
	while ((*p) > 9 + '0')
	{
		(*p) = ((*p)-'0') % 10 + '0';
		p--;
		if (p < content)
		{
			content.replace(1, len - 1, content);
			p++;
			(*p) = '0';
		}
		(*p)++;
	}
	return result;
}

bigint bigint::operator--()//--a
{
	if (sign == N)
	{
		bigint result = *this;
		result.sign = P;
		result++;
		result.sign = N;
		*this = result;
		return result;
	}
	char *p = &(content[len - 1]);//指向最后一位
	(*p)--;
	while ((*p)< '0')
	{
		(*p) = (*p)+10;
		p--;
		(*p)--;
	}
	if (content[0] == '0')
	{
		content.assign(content, 0, len - 1);
		len--;
	}
	bigint result = *this;
	return result;
}
bigint bigint::operator--(int)//a++
{
	if (sign == N)
	{
		bigint result = *this;
		sign = P;
		(*this)++;
		sign = N;
		return result;
	}
	bigint result = *this;
	char *p = &(content[len - 1]);//指向最后一位
	(*p)--;
	while ((*p)< '0')
	{
		(*p) = (*p) + 10;
		p--;
		(*p)--;
	}
	if (content[0] == '0')
	{
		content.assign(content, 0, len - 1);
		len--;
	}
	return result;
}
bigint bigint::operator+=(bigint &b)
{
	*this = (*this) + b;
	return *this;
}
bigint bigint::operator-=(bigint &b)
{
	*this = (*this) - b;
	return *this;
}
bigint bigint :: operator+()//正号
{
	return *this;
}
bigint bigint :: operator-()//正号
{
	bigint result = (*this);
	result.sign = (!result.sign);
	return result;
}

bool bigint::operator>(const bigint &b)
{
	if (sign == P&&b.sign == N)
		return true;
	if (sign == N&&b.sign == P)
		return false;
	if (len > b.len || len == b.len && content > b.content)
		if (sign == P)
			return true;
	return false;
}
bool bigint::operator>=(const bigint &b)
{
	if ((*this) > b || len == b.len&&sign == b.sign&&content == b.content)
		return true;
	return false;
}
bool bigint::operator<(const bigint &b)
{
	if ((*this) > b || len == b.len&&sign == b.sign&&content == b.content)
		return false;
	return true;
}
bool bigint::operator<=(const bigint &b)
{
	if (sign == P&&b.sign == N)
		return false;
	if (sign == N&&b.sign == P)
		return true;
	if (len > b.len || len == b.len && content > b.content)
		if (sign == P)
			return false;
	return true;
}
bool bigint::operator==(const bigint &b)
{
	if (sign == b.sign&& len == b.len&&content == b.content)
		return true;
	return false;
}
bool bigint::operator!=(const bigint &b)
{
	if (sign == b.sign&& len == b.len&&content == b.content)
		return false;
	return true;
}

ostream& operator<<(ostream& out, bigint& b)
{
	if (b.sign == N)
		out << '-';
	out << b.content << endl;
	return out;
}
istream& operator >> (istream& in, bigint& a)
{
	string s;
	in >> s;
	a = s;
	return in;
}