/*1551445 ͯ���� �������ѧ�뼼��1��*/
#include"90-b5-adv.h"

bigint::bigint()
{
	sign = P;//��ʼ��Ϊ+
	len = 1;
	content = "0";
}
bigint::bigint(const string str)
{
	if (str[0] == '-')
	{
		sign = N;
		len = str.length() - 1;
		content.append(str, 1, len);//��str�еڶ�λ��ʼ�����ݽӵ�content
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

/*ֻ��Ҫ����������֮��ļӺͼ�����������������������-��������ת���� ������+��������
                                        //    ������+��������ת���� ������-��������
										//	  ������1+������2��ת���� ������2-������1
											  ������1-������2��ת���� ������2-������1
											  ������-��������ת���� ��-1��������+������
										//	  ������1+������2��ת���� ��-1��������+������*/
bigint bigint::operator+(bigint &b)
{
	/*�Ƚ�����ϣ��ж��Ƿ���Ҫת��*/
	if (b.sign == N && sign==P)
	{
		bigint tmpB = b;
		tmpB.sign = P;//ת���������͵���Ӧ�ļ�/��������
		return ((*this) - tmpB);
	}
	else if (sign == N && b.sign == P)
	{
		bigint tmpB = *this;
		tmpB.sign = P;
		return (b - tmpB);
	}

	/*��������������������������Ӵ���*/
	bigint result;
	unsigned int lenMin = (len < b.len) ? len : b.len;
	unsigned int lenMax = (len > b.len) ? len : b.len;
	result.len = lenMax + 1;;//������Ӻ͵�λ������ �ϴ�����λ����һλ

	result.content.resize(result.len + 1);//content��СΪlen+1
	(result.content)[result.len] = '\0';

	/*��ָ�����������ʽ��Ч�ʸ���*/
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
		*pr= tmpResult % 10+'0';//intת�ַ�
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
		result.content.assign(result.content, 1, lenMax);//�ѵ�һλȥ��
		result.len--;
	}
	if (sign == N&&b.sign == N)
		result.sign = N;
	return result;
}

bigint bigint::operator-(bigint &b)
{
	/*�Ƚ�����ϣ��ж��Ƿ���Ҫת��*/
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

	/*�����������������������ļ�����*/
	bigint result;
	char *p1, *p2;/*p1ָ�򱻼���(�ϴ�)��p2ָ���������С��   ��ע��������-����=��*/
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


	/*�жϽ����������������-�����е�ֻ��˫����˫������������ֱ����a>b�Լ�b>a���֣�
	����result��ʼ��signΪP�����ֻ��Ҫ����signΪN�����*/

	if (sign == N&&b.sign == N)
	{
		if (p1 != &((b.content)[b.len-1]))//a����
			result.sign = N;
	}
	else
		if (p1 == &((b.content)[b.len-1]))//b����
			result.sign = N;

	result.len = lenMax;//���������λ�����Ϊ���߽ϳ�������λ��
	result.content.resize(result.len + 1);//content��СΪlen+1
	(result.content)[result.len] = '\0';

	/*��ָ�����������ʽ��Ч�ʸ���*/
	char *pr = &((result.content)[result.len - 1]);
	unsigned int i = 0, borrow = 0,zeroNum=0;
	int tmpResult = 0;//�������з�����int����
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
			tmpResult = *p1-'0' - borrow;//С��'0'
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
	/*�����������ڽ��ǰ�涼Ϊ0�������Ҫ���⴮0ȥ��*/
	pr++;
	while (*pr == '0'&&zeroNum<lenMax)
	{
		zeroNum++;
		pr++;
	}
	result.content.assign(result.content, zeroNum, lenMax-zeroNum);//�ѵ�һλȥ��
	result.len-=zeroNum;
	return result;
}

bigint bigint::operator*(bigint &b)
{
	bigint result;

	/*ȷ������λ*/
	if (sign != b.sign)
		result.sign = N;

	/*ȷ������*/
	result.len = len + b.len;//�������λ�����Ϊ����λ��֮��
	result.content.resize(result.len + 1);//��һλ�洢β��
	result.content.assign(result.len,'0');//������ݵ�������'0'���
	result.content[result.len] = '\0';
	

	char* pa = &(content[len - 1]);
	char* pb = &((b.content)[b.len - 1]);
	char* pr = &((result.content)[result.len - 1]);
	char* pTmp = pr,*pTmp2=pr,*pbTmp=pb;
	int carry = 0;//��λ
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
	/*ȷ������λ*/
	if (sign != b.sign)
		result.sign = N;
	
	/*��������������㷨*/
	if (len < b.len || len == b.len && content<=b.content)
	{
		result.len = 1;
		result.content = "0";
		if (content == b.content && len==b.len)
			result.content = "1";
		return result;
	}
	
	result.len = len - b.len + 1;//ȷ���̵���󳤶�
	result.content.assign(result.len, '0');//��result��Ϊ0��
	bigint tmpA = *this;//�ڼ��Ĺ����л�ı䣬�����Ҫһ������
	tmpA.sign = P;//����������ǰ���������ģ�����������������
	bigint tmpResult;//�м�ֵ
	
	if (len == b.len)
	{
		int count = 0;
		while (tmpA.len >b.len || tmpA.len == b.len&&tmpA.content > b.content)
		{
			if (b.sign == P)
				tmpA = tmpA - b;//���ܵ�����-����Ϊ�����ǲ�ȷ���ģ���Ҫ��������
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
	int numZeroAdd = len - b.len - 1;//�����0�ĸ���
	while (tmpA.len>b.len||tmpA.len==b.len&&tmpA.content>b.content)
	{
		tmpResult.content.resize(numZeroAdd + 3);
		tmpResult.len = numZeroAdd + 2;
		tmpResult.content.assign(tmpResult.len, '0');
		tmpB = b;
		tmpB.content.append(numZeroAdd--, '0');
		tmpB.len = tmpB.content.length();
		if (tmpB > tmpA)//���߶������ģ�����ֱ�ӱȽ�
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
	/*ȷ������λ*/
	if (sign != b.sign)
		result.sign = N;

	int tmpSign = sign, tmpSignB = b.sign;//��*this��b�ķ���λ�ȴ�����
	sign = P;
	b.sign = P;
	/*��������������㷨*/
	if (b>(*this))
	{
		result.len = len;
		result.content = content;
		result.sign = tmpSign;
		return result;
	}

	result.len = len - b.len + 1;//ȷ���̵���󳤶�
	result.content.assign(result.len, '0');//��result��Ϊ0��
	bigint tmpA = *this;//�ڼ��Ĺ����л�ı䣬�����Ҫһ������

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
		sign = tmpSign;//����λ��ԭ
		return result;
	}
	bigint tmpB = b;
	int numZeroAdd = len - b.len - 1;//�����0�ĸ���
	int i = 0;
	while (tmpA>=b)
	{
		tmpB = b;
		tmpB.content.append(numZeroAdd--, '0');
		tmpB.len = tmpB.content.length();
		if (tmpB > tmpA)//���߶������ģ�����ֱ�ӱȽ�
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
	char *p = &(content[len - 1]);//ָ�����һλ
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
	char *p = &(content[len - 1]);//ָ�����һλ
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
	char *p = &(content[len - 1]);//ָ�����һλ
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
	char *p = &(content[len - 1]);//ָ�����һλ
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
bigint bigint :: operator+()//����
{
	return *this;
}
bigint bigint :: operator-()//����
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