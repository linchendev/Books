//替换空格
//请实现一个函数，把字符串中的每个空格替换成"%20"
//例如输入"We are happy"，则输出"We%20are%20happy"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int getBlankNum(const char* str)
{
	int count = 0;
	int len = strlen(str);
	for(int i = 0; i < len; ++i)
	{
		if(str[i] == ' ')
			++ count;
	}
	return count;
}

//使用完成返回值后需要手动释放
char* MyReplaceBlank(const char* src)
{
	int srclen = strlen(src)+1;
	if(srclen == 0)
		return NULL;

	int blanknum = getBlankNum(src);
	if(blanknum == 0)
		return NULL;

	char* ret = new char[srclen+blanknum*2];
	const char* p1 = src+(srclen-1); //注意地址偏移和下标一样从0开始
	char* p2 = ret + (srclen + blanknum*2 - 1);

	for(int i = 0; i < srclen; ++i)
	{
		if(*p1 == ' ')
		{
			*p2-- = '0';
			*p2-- = '2';
			*p2-- = '%';
			--p1;
		}
		else
		{
			*p2 = *p1;
			--p2;
			--p1;
		}
	}

	return ret;
}

//书中源码
//length为字符数组string的总容量
//在原字符串数组进行操作，需要保证原字符串长度足够
void ReplaceBlank(char string[], int length)
{
	if(string == NULL || length <= 0)
		return;

	//originalLength为字符串string的实际长度
	int originalLength = 0;
	int numberOfBlank = 0;
	int i = 0;
	while(string[i] != '\0')
	{
		++originalLength;
		
		if(string[i] == ' ')
			++numberOfBlank;

		++i;
	}

	//newLength为把空格替换成'%20'之后的长度
	int newLength = originalLength + numberOfBlank * 2;
	if(newLength > length)
		return;

	int indexOfOriginal = originalLength;
	int indexOfNew = newLength;
	while(indexOfOriginal >= 0 && indexOfNew > indexOfOriginal)
	{
		if(string[indexOfOriginal] == ' ')	
		{
			string[indexOfNew--] = '0';
			string[indexOfNew--] = '2';
			string[indexOfNew--] = '%';
		}
		else
		{
			string[indexOfNew--] = string[indexOfOriginal];
		}

		--indexOfOriginal;
	}
}

int main()
{
	const char* src = "We  are happy";
	char* ret = MyReplaceBlank(src);
	printf("%s --> %s\n", src, ret);
	delete []ret;

	const int len = 20;
	char src1[len] = "We are happy";
	ReplaceBlank(src1, len);
	printf("%s\n", src1);
	return 0;
}
