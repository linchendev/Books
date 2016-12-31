#include <iostream>
#include <string>
#include <map>
using namespace std;


//译文：写一个函数判断是否两个字符串为变位词。变位词就是两个字符串中的字符相同，只是位置不同
//思路一:遍历两个字符串的字符，使用map对字符进行统计
bool isAnagram(string str1, string str2)
{
	if(str1.length() != str2.length())
		return false;
	
	if(str1 == str2)
		return false;

	map<char,int> my_map;
	for(int i = 0; i < str1.length(); i++)
	{
		my_map[str1[i]] += 1;
		my_map[str2[i]] += -1;
	}

	for(map<char,int>::iterator it = my_map.begin(); it != my_map.end(); ++it)
	{
		if(it->second != 0)
			return false;
	}

	return true;
}

//思路二：对两个字符串进行排序,然后比较两个字符串是否相同
//直接使用sort或者写个快排
int Partition(char s[], int left, int right)
{
	int pivot = s[left];

	while(left < right)
	{
		while(left < right && s[right] > pivot)
			--right;
		s[left] = s[right];

		while(left < right && s[left] <= pivot)
			++left;
		s[right] = s[left];
	}

	s[left] = pivot;

	return left;
}

void QuickSort(char s[], int left, int right)
{
	if(left < right)
	{
		int i = Partition(s, left, right);
		QuickSort(s, left, i-1);
		QuickSort(s, i+1, right);
	}
}


bool isAnagram2(string str1, string str2)
{
	if(str1.length() != str2.length())
		return false;

	int len = str1.length();

	QuickSort(&str1[0], 0, len-1);
	QuickSort(&str2[0], 0, len-1);

	if(str1 == str2)
		return true;

	return false;
}

int main()
{
	string str1,str2;
	cin >> str1;
	cin >> str2;

	if(isAnagram2(str1,str2))
		cout << "They are Anagram words" << endl;
	else
		cout << "They are not Anagram words" << endl;
	
	return 0;
}
